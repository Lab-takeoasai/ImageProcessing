#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static char windowNameCapture[] = "Capture Window";

int main (int argc, char const *argv[])
{
	IplImage *objectImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	IplImage *backgroundImage = cvLoadImage("background.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	IplImage *maskImage = cvLoadImage("mask.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	CvSize size = cvGetSize(backgroundImage);
	IplImage *maskedImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	
	cvCopy(objectImage, backgroundImage, maskImage);
	
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	
	while (1) {
		int key = cvWaitKey(10);
		cvShowImage(windowNameCapture, backgroundImage);
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowNameCapture);
	return 0;
}