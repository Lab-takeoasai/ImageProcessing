#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static const char windowNameCapture[] = "Capture Window";
static const char trackbarName[] = "Threshold";
static int level = 128;

static IplImage *objectImage;

void binarization() {
	IplImage *binaryImage = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	cvThreshold(objectImage, binaryImage, level, 255, CV_THRESH_BINARY);
	cvShowImage(windowNameCapture,binaryImage);
	cvReleaseImage(&binaryImage);
}

void on_change(int value) {
	binarization();
}

int main (int argc, char const *argv[])
{
	objectImage = cvLoadImage("object.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	
	cvNamedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar(trackbarName, windowNameCapture, &level, 255, on_change);
	
	while (1) {
		int key = cvWaitKey(10);
		
		binarization();
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowNameCapture);
	return 0;
}