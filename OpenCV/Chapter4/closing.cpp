#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

static int iterations = 10;

static char windowSource[] = "Source.  0";
static char windowDilated[] = "Dilated. 1";
static char windowClosing[] = "Closing. 2";

static cv::Mat image;

void changeIterations(int value, void *userData) {
	cv::Mat thresholdImage;
	cv::Mat dilatedImage;
	cv::Mat closingImage;
	
	cv:threshold(image, thresholdImage, 128.0, 255.0, CV_THRESH_BINARY);
	cv::dilate(thresholdImage, dilatedImage, cv::Mat(), cv::Point(-1, 1), iterations);
	cv::erode(dilatedImage, closingImage, cv::Mat(), cv::Point(-1, 1), iterations);
	
	cv::imshow(windowSource,image);
	cv::imshow(windowDilated,dilatedImage);
	cv::imshow(windowClosing,closingImage);
	
}

int main ( int argc, char** argv )
{	
	image = cv::imread("closing.bmp", 0);
	
	cv::namedWindow(windowSource, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(windowDilated, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(windowClosing, CV_WINDOW_AUTOSIZE);
	cv::createTrackbar("Iteration", windowSource, &iterations, 20, changeIterations, NULL);
	
	changeIterations(0, NULL);
	
	while ( 1 ) {
		int key = cv::waitKey(10);
		
		if( key == 'q' ) {
			break;
		}
	}
	
	return 0;
}