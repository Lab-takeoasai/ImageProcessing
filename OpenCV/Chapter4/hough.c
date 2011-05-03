#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static const char windowCannyName[] = "Window Canny";
static const char windowHoughName[] = "Window Hough";

static const char trackbarCannyMinName[] = "Min";
static const char trackbarCannyMaxName[] = "Max";
static unsigned int cannyMin = 0;
static unsigned int cannyMax = 255;

static IplImage *objectImage;

IplImage *_canny(IplImage *image) {
	IplImage *cannyImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	
	cvCanny(image, cannyImage, cannyMin, cannyMax, 3);
	
	return cannyImage;
}

void cannyDetection() {
	IplImage *cannyImage = _canny(objectImage);
	
	cvShowImage(windowCannyName, cannyImage);
	
	cvReleaseImage(&cannyImage);
}

void changeCanny(int value) {
	cannyDetection();
}

void houghDetection() {
	IplImage *temporaryImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_32F, 1);
	IplImage *houghImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	IplImage *cannyImage = _canny(objectImage);
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *lines = NULL;
	
	lines = cvHoughLines2(cannyImage, storage, CV_HOUGH_PROBABILISTIC, 1, (CV_PI/180), 50, 50, 10);
	
	for ( int i = 0; i < lines->total; i++ ) {
		CvPoint *line = (CvPoint *)cvGetSeqElem(lines, i);
		cvLine(houghImage, line[0], line[1], CV_RGB(255,0,0), 1, 1, 0);
	}
	
	cvShowImage(windowHoughName, houghImage);
	
	cvReleaseImage(&houghImage);
}

int main (int argc, char const *argv[])
{
	objectImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	
	cvNamedWindow(windowCannyName, CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar(trackbarCannyMinName, windowCannyName, &cannyMin, 255, changeCanny);
	cvCreateTrackbar(trackbarCannyMaxName, windowCannyName, &cannyMax, 255, changeCanny);
	
	cvNamedWindow(windowHoughName, CV_WINDOW_AUTOSIZE);
	
	while (1) {
		int key = cvWaitKey(10);
		
		cannyDetection();
		houghDetection();
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowCannyName);
	cvDestroyWindow(windowHoughName);
	return 0;
}