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
	
	CvPoint2D32f origin[3];
	CvPoint2D32f trans[3];
	origin[0] = cvPoint2D32f(0, 0);
	origin[1] = cvPoint2D32f(size.width, 0);
	origin[2] = cvPoint2D32f(0, size.height);
	trans[0] = cvPoint2D32f(300, 200);
	trans[1] = cvPoint2D32f(100, 50);
	trans[2] = cvPoint2D32f(230, 40);
	
	CvMat *affine = cvCreateMat(2, 3, CV_32FC1);
	cvGetAffineTransform(origin, trans, affine);
	
	cvWarpAffine(objectImage, destinationImage, affine, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
	
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