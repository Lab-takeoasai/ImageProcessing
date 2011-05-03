#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static char windowNameCapture[] = "Capture Window";

int main (int argc, char const *argv[])
{
	CvCapture *capture = cvCreateCameraCapture(0);
	IplImage *image = cvQueryFrame(capture);
	
	CvSize size = cvSize(image->width, image->height);
	IplImage *resultImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	
	while (1) {
		int key = cvWaitKey(10);
		image = cvQueryFrame(capture);
			
		for ( int y = 0; y < size.height; y++ ) {
			for ( int x = 0; x < size.width; x++ ) {
				CvScalar value = cvGet2D(image, y, x);
				value.val[0] = 100;
				value.val[1] = 100;
//				value.val[2];
				cvSet2D(resultImage, y, x, value);
			}
		}
		
		cvShowImage(windowNameCapture, resultImage);
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowNameCapture);
	cvReleaseCapture(&capture);
	return 0;
}