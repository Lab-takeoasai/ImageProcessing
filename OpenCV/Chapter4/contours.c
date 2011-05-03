#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static const char windowName[] = "Window";
static const char trackbarName[] = "Threshold";
static int level = 128;

static IplImage *objectImage;
static IplImage *sourceImage;

static CvMemStorage *storage;

void findContours() {
	IplImage *destinationImage = cvCloneImage(sourceImage);
	IplImage *binaryImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	
	cvThreshold(objectImage, binaryImage, level, 255, CV_THRESH_BINARY);
	
	int LEVEL = 5;
	CvSeq *contours = NULL;
	CvScalar red = CV_RGB(255, 0, 0);
	cvFindContours(binaryImage, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0, 0));
	cvDrawContours(destinationImage, contours, red, red, LEVEL, 5, 1, cvPoint(0, 0));
	
	cvShowImage(windowName, destinationImage);
	
	
	cvReleaseImage(&binaryImage);
}

void on_change(int value) {
	findContours();
}

int main (int argc, char const *argv[])
{
	sourceImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	objectImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	storage = cvCreateMemStorage(0);
	
	cvNamedWindow(windowName, CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar(trackbarName, windowName, &level, 255, on_change);
	
	while (1) {
		int key = cvWaitKey(10);
		
		findContours();
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowName);
	return 0;
}