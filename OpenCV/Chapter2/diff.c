#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static char windowNameCapture[] = "Capture Window";
static char windowNameDifference[] = "Difference Window";

static IplImage *backgroundImage;

void captureDifferenceSetup() {
	backgroundImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
	
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(windowNameDifference, CV_WINDOW_AUTOSIZE);
}

void captureDifferenceBackground(CvCapture *capture) {
	cvResize(cvQueryFrame(capture), backgroundImage, CV_INTER_LINEAR);
}

void captureDifference(CvCapture *capture) {
	IplImage *differenceImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
	IplImage *tmpImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
	IplImage *frameImage = cvQueryFrame(capture);
	
	cvResize(frameImage, tmpImage, CV_INTER_LINEAR);
	cvAbsDiff(tmpImage, backgroundImage, differenceImage);
	cvShowImage(windowNameCapture, frameImage);
	cvShowImage(windowNameDifference, differenceImage);
	cvReleaseImage(&tmpImage);
		
	cvReleaseImage(&differenceImage);
}

void captureDifferenceDestroy() {
	cvReleaseImage(&backgroundImage);
	
	cvDestroyWindow(windowNameCapture);
	cvDestroyWindow(windowNameDifference);
}

