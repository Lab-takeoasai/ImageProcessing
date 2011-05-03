#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

double min(double a, double b) {
	return (a > b) ? b : a;
}

double max(double a, double b) {
	return (a > b) ? a : b;
}

static const char windowName[] = "Window";
static const char windowHistogramName[] = "Histogram";

static const char trackbarBrightnessName[] = "Brightness";
static const char trackbarContrastName[] = "Constrast";

static CvMat *lookUpTableMatrix;
static CvHistogram *_histogram;
static unsigned char lookUpTable[256];

static int _histogram_size = 128;
static int _brightness = 128;
static int _contrast = 128;


static IplImage *objectImage;
static IplImage *histogramImage;
static IplImage *destinationImage;


void histogram() {
	int brightness = _brightness - 127;
	int contrast = _contrast - 127;
	
	//	update lookup table
	if ( contrast > 0 ) {
		double delta = 127.0 * contrast / 100.0;
		double a = 255.0 / (255.0 - delta * 2);
		double b = a * (brightness - delta);
		for ( int i = 0; i < 256; i++ ) {
			lookUpTable[i] = (unsigned char)((int)min(max(cvRound(a*i+b), 0), 255));
		}
	} else {
		double delta = -128.0 * contrast / 100.0;
		double a = (256.0 - delta * 2) / 255.0;
		double b = a * (brightness - delta);
		for ( int i = 0; i < 256; i++ ) {
			lookUpTable[i] = (unsigned char)((int)min(max(cvRound(a*i+b), 0), 255));
		}
	}
	
	cvLUT(objectImage, destinationImage, lookUpTableMatrix);
	cvShowImage(windowName, destinationImage);
	
	float max_value;
	cvCalcHist(&destinationImage, _histogram, 0, NULL);
	cvGetMinMaxHistValue(_histogram, NULL, &max_value, NULL, NULL);
	cvConvertScale(_histogram->bins, _histogram->bins, cvGetSize(histogramImage).height / max_value, 0);
	
	cvSet(histogramImage, cvScalarAll(255), NULL);
	int bin_width = cvRound(cvGetSize(histogramImage).width / _histogram_size);
	
	for ( int i = 0; i < 128; i++ ) {
		cvRectangle(histogramImage,
					cvPoint(i*bin_width, cvGetSize(histogramImage).height),
					cvPoint((i+1)*bin_width, cvGetSize(histogramImage).height - cvRound(cvGetReal1D(_histogram->bins, i))),
					cvScalarAll(0),
					5,
					1,
					0);
	}
	
	cvShowImage(windowHistogramName, histogramImage);
}

void change(int value) {
	histogram();
}

int main (int argc, char const *argv[])
{
	objectImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	destinationImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	histogramImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	
	float range0[] = {0, 256};
	float *ranges[] = { range0 };
	_histogram = cvCreateHist(1, &_histogram_size, CV_HIST_ARRAY, ranges, 1);
	lookUpTableMatrix = cvCreateMatHeader(1, 256, CV_8UC1);
	cvSetData(lookUpTableMatrix, lookUpTable, 256);
	
	cvNamedWindow(windowName, CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar(trackbarContrastName, windowName, &_contrast, 255, change);
	cvCreateTrackbar(trackbarBrightnessName, windowName, &_brightness, 255, change);
	
	while (1) {
		int key = cvWaitKey(10);
		
		histogram();
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowName);
	return 0;
}