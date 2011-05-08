#include <cv.h>
#include <highgui.h>
#include "LabelingW.h"


static char windowName[] = "Labeling";

int main ( int argc, char** argv )
{
	cv::VideoCapture cap(0);
	
    cv::namedWindow(windowName,1);

    while ( 1 ) {
    	cv::Mat hsvImage;
        cv::Mat frame;
        cap >> frame;
		
		//	get Skin area
        cv::cvtColor(frame, hsvImage, CV_BGR2HSV);
		cv::GaussianBlur(hsvImage, hsvImage, cv::Size(7,7), 1.5, 1.5);
		cv::MatIterator_<cv::Vec3b> itr = hsvImage.begin<cv::Vec3b>();
		for ( ; itr != hsvImage.end<cv::Vec3b>(); ++itr ) {
			int h = (*itr)[0];
			int s = (*itr)[1];
			int v = (*itr)[2];
			if ( h <= 20 && s >= 51 ) {	// skin color
				(*itr)[0] = 255;
				(*itr)[1] = 255;
				(*itr)[2] = 255;
			} else {
				(*itr)[0] = 0;
				(*itr)[1] = 0;
				(*itr)[2] = 0;
			}
		}
		
		//	interpolate
		int iterations = 2;
		cv::dilate(hsvImage, hsvImage, cv::Mat(), cv::Point(-1, 1), iterations);
		cv::erode(hsvImage, hsvImage, cv::Mat(), cv::Point(-1, 1), iterations);
		
		//	Labeling
		int ignore_size = 1000;
		IplImage image = hsvImage;
		IplImage *labelImage = cvCloneImage(&image);
		Label *label = createLabeling();
		exec(label, &image, &image, true, ignore_size);
		if ( getNumOfResultRegions(label) > 0 ) {
			
			for ( int x = 0; x < image.width; x++ ) {
				for ( int y = 0; y < image.height; y++ ) {
					if ( cvGetReal2D(label, y, x) == 1 ) {
						cvSet2D(labelImage, y,x , CV_RGB(255,255,255));
					} else {
						cvSet2D(labelImage, y,x , CV_RGB(0,0,0));
					}
				}
			}
			
		}
       	cv::imshow(windowName, labelImage);
		
        if(cv::waitKey(30) >= 0) break;
    }

	return 0;
}