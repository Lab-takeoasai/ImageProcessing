#include <cv.h>
#include <stdio.h>
#include <highgui.h>

int main (int argc, char const *argv[])
{
	int key;
	IplImage *frameImage;
	CvCapture *capture = cvCreateCameraCapture(0);
	static char windowNameCapture[] = "Capture Window";
	
	//	error handle
	if ( capture == NULL ) {
		printf("No Camera is detected.");
		exit(-1);
	}
	
	//	create window
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	
	//	Main loop
	while (1) {
		frameImage = cvQueryFrame(capture);
		
		cvShowImage(windowNameCapture, frameImage);
		
		key = cvWaitKey(10);
		if ( key == 'q' ) {
			break;
		} else if ( key == 's' ) {
			cvSaveImage("saved.bmp", frameImage, 0);
		}
	}
	
	cvReleaseCapture(&capture);
	
	cvDestroyWindow(windowNameCapture);
	
	return 0;
}

