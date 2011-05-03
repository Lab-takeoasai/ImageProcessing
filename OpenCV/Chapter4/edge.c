#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static const char windowSobelXName[] = "Window Sobel X";
static const char windowSobelYName[] = "Window Sobel Y";
static const char windowLaplaceName[] = "Window Laplace";

static IplImage *objectImage;


void edgeDetection() {
	IplImage *temporaryImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_32F, 1);
	IplImage *sobelXImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	IplImage *sobelYImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	IplImage *laplaceImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	
	cvSobel(objectImage, temporaryImage, 1, 0, 3);
	cvConvertScaleAbs(temporaryImage, sobelXImage, 1, 0);
	cvSobel(objectImage, temporaryImage, 0, 1, 3);
	cvConvertScaleAbs(temporaryImage, sobelYImage, 1, 0);
	cvLaplace(objectImage, temporaryImage, 3);
	cvConvertScaleAbs(temporaryImage, laplaceImage, 1, 0);
	
//	cvSobel(objectImage, sobelYImage, 0, 1, 3);
//	cvLaplace(objectImage, laplaceImage, 3);
	
	cvShowImage(windowSobelXName, sobelXImage);
	cvShowImage(windowSobelYName, sobelYImage);
	cvShowImage(windowLaplaceName, laplaceImage);
	
	cvReleaseImage(&sobelXImage);
	cvReleaseImage(&sobelYImage);
	cvReleaseImage(&laplaceImage);
}

int main (int argc, char const *argv[])
{
	objectImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	
	cvNamedWindow(windowSobelXName, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(windowSobelYName, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(windowLaplaceName, CV_WINDOW_AUTOSIZE);

	while (1) {
		int key = cvWaitKey(10);
		
		edgeDetection();
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowSobelXName);
	cvDestroyWindow(windowSobelYName);
	cvDestroyWindow(windowLaplaceName);
	return 0;
}