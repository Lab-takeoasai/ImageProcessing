#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static char windowNameCapture[] = "Capture Window";

int main (int argc, char const *argv[])
{
	CvCapture *capture = cvCreateCameraCapture(0);
	
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	
	while (1) {
		int key = cvWaitKey(10);
		IplImage *image = cvQueryFrame(capture);
		IplImage *rgbImage = cvCreateImage(cvSize(1024, 768), IPL_DEPTH_8U, 3);
		IplImage *hsvImage = cvCreateImage(cvSize(1024, 768), IPL_DEPTH_8U, 3);
		IplImage *hueImage = cvCreateImage(cvSize(1024, 768), IPL_DEPTH_8U, 1);
		IplImage *saturationImage = cvCreateImage(cvSize(1024, 768), IPL_DEPTH_8U, 1);
		IplImage *valueImage = cvCreateImage(cvSize(1024, 768), IPL_DEPTH_8U, 1);
		IplImage *mergeImage = cvCreateImage(cvSize(1024, 768), IPL_DEPTH_8U, 3);
		
		cvResize(image, rgbImage, CV_INTER_LINEAR);
		cvCvtColor(rgbImage, hsvImage, CV_BGR2HSV);
		cvSplit(hsvImage, hueImage, saturationImage, valueImage, NULL);
		
		cvSet(hueImage, cvRealScalar(22), NULL);
		cvSet(saturationImage, cvRealScalar(90), NULL);
		
		cvMerge(hueImage, saturationImage, valueImage, NULL, mergeImage);
		
		cvShowImage(windowNameCapture, mergeImage);
		
		cvReleaseImage(&rgbImage);
		cvReleaseImage(&hsvImage);
		cvReleaseImage(&hueImage);
		cvReleaseImage(&saturationImage);
		cvReleaseImage(&valueImage);
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowNameCapture);
	cvReleaseCapture(&capture);
	return 0;
}