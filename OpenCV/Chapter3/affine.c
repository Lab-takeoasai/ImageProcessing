#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static char windowNameCapture[] = "Capture Window";

int main (int argc, char const *argv[])
{
	IplImage *objectImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	CvSize size = cvGetSize(objectImage);
	IplImage *destinationImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	
	CvPoint2D32f origin[4];
	CvPoint2D32f trans[4];
	origin[0] = cvPoint2D32f(0, 0);
	origin[1] = cvPoint2D32f(size.width, 0);
	origin[2] = cvPoint2D32f(0, size.height);
	origin[3] = cvPoint2D32f(size.width, size.height);
	trans[0] = cvPoint2D32f(400, 400);
	trans[1] = cvPoint2D32f(50, 50);
	trans[2] = cvPoint2D32f(130, 40);
	trans[3] = cvPoint2D32f(0, size.height);
	
	CvMat *perspective = cvCreateMat(3, 3, CV_32FC1);
	cvGetPerspectiveTransform(origin, trans, perspective);
	
	cvWarpAffine(objectImage, destinationImage, perspective, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
	
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	
	while (1) {
		int key = cvWaitKey(10);
		cvShowImage(windowNameCapture,destinationImage);
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowNameCapture);
	return 0;
}