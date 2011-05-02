#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>


static char windowNameCapture[] = "Capture Window";
static char windowNameDifference[] = "Skin Window";

static IplImage *backgroundImage;

void captureSkinSetup() {
	backgroundImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(windowNameDifference, CV_WINDOW_AUTOSIZE);
}

void captureSkin(CvCapture *capture) {
	CvMoments moments;

	IplImage *frameImage = cvQueryFrame(capture);
	IplImage *frameTemporary = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
	IplImage *hsvImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
	IplImage *hueImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	IplImage *thresholdImage1 = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	IplImage *thresholdImage2 = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	IplImage *thresholdImage3 = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	IplImage *grayImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	IplImage *differenceImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	IplImage *skinImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	
	cvResize(frameImage, frameTemporary, CV_INTER_LINEAR);
	cvCvtColor(frameTemporary, grayImage, CV_BGR2GRAY);
	cvCvtColor(frameTemporary, hsvImage, CV_BGR2HSV);
	cvAbsDiff(grayImage, backgroundImage, differenceImage);
	
	cvSplit(hsvImage, hueImage, NULL, NULL,NULL);
	
	cvThreshold(hueImage, thresholdImage1,  0, 255, CV_THRESH_BINARY);
	cvThreshold(hueImage, thresholdImage2, 15, 255, CV_THRESH_BINARY_INV);
	cvAnd(thresholdImage1, thresholdImage2, thresholdImage3, NULL);
	cvAnd(thresholdImage3, differenceImage, skinImage, NULL);
	
	cvMoments(skinImage, &moments, 0);
	double m00 = cvGetSpatialMoment(&moments, 0, 0);
	double m10 = cvGetSpatialMoment(&moments, 1, 0);
	double m01 = cvGetSpatialMoment(&moments, 0, 1);
	
	cvCircle(frameTemporary, cvPoint(m10/m00, m01/m00), 30, CV_RGB(255, 0, 0), 5, 1, 0);
	
	cvShowImage(windowNameCapture, skinImage);
	cvShowImage(windowNameDifference, frameTemporary);
	
	cvReleaseImage(&frameTemporary);
	cvReleaseImage(&hsvImage);
	cvReleaseImage(&hueImage);
	cvReleaseImage(&thresholdImage1);
	cvReleaseImage(&thresholdImage2);
	cvReleaseImage(&thresholdImage3);
	cvReleaseImage(&grayImage);
	cvReleaseImage(&differenceImage);
	cvReleaseImage(&skinImage);
}

void captureSkinBackground(CvCapture *capture) {
	IplImage *frameTemporary = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
	cvResize(cvQueryFrame(capture), frameTemporary, CV_INTER_LINEAR);
	cvCvtColor(frameTemporary, backgroundImage, CV_BGR2GRAY);
	
}

void captureSkinDestroy() {
	cvReleaseImage(&backgroundImage);
	
	cvDestroyWindow(windowNameCapture);
	cvDestroyWindow(windowNameDifference);
}

