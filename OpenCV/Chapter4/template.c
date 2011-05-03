#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

static const char windowName[] = "Window";
static const char trackbarName[] = "Threshold";
static int level = 128;

static IplImage *objectImage;
static IplImage *sourceImage;
static IplImage *templateImage;



void templateMatching() {
	IplImage *image = cvCloneImage(sourceImage);
	IplImage *binaryObject = cvCreateImage(cvGetSize(objectImage), IPL_DEPTH_8U, 1);
	IplImage *binaryTemplate = cvCreateImage(cvGetSize(templateImage), IPL_DEPTH_8U, 1);
	IplImage *differenceMapImage = cvCreateImage(cvSize(objectImage->width-templateImage->width+1, objectImage->height-templateImage->height+1), IPL_DEPTH_32F, 1);
	CvPoint minLocation;
	
	cvThreshold(objectImage, binaryObject, level, 255, CV_THRESH_BINARY);
	cvThreshold(templateImage, binaryTemplate, level, 255, CV_THRESH_BINARY);
	
	cvMatchTemplate(binaryObject, binaryTemplate, differenceMapImage, CV_TM_SQDIFF);
	cvMinMaxLoc(differenceMapImage, NULL, NULL, &minLocation, NULL, NULL);
	
	cvRectangle(image, minLocation, cvPoint(minLocation.x+templateImage->width, minLocation.y+templateImage->height), CV_RGB(255,0,0), 3, 1, 0);
	
	cvShowImage(windowName, image);
}

void on_change(int value) {
	templateMatching();
}

int main (int argc, char const *argv[])
{
	sourceImage = cvLoadImage("source.bmp", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	objectImage = cvLoadImage("source.bmp", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	templateImage = cvLoadImage("template.bmp", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	
	cvNamedWindow(windowName, CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar(trackbarName, windowName, &level, 255, on_change);
	
	while (1) {
		int key = cvWaitKey(10);
		
		templateMatching();
		
		if ( key == 'q' ) {
			break;
		}
	}
	cvDestroyWindow(windowName);
	return 0;
}