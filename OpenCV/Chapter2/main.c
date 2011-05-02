#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <cxcore.h>

enum CaptureMode {
	CaptureModeDifference,
	CaptureModeSkin
};

int main (int argc, char const *argv[])
{
	int key;
	enum CaptureMode mode = CaptureModeDifference;
	CvCapture *capture = cvCreateCameraCapture(0);
	
	//	error handle
	if ( capture == NULL ) {
		printf("No Camera is detected.");
		exit(-1);
	}
	
	//	Initialize
	captureDifferenceSetup();
	
	//	Main loop
	while (1) {
		key = cvWaitKey(10);
		
		switch ( mode ) {
			case CaptureModeDifference:
				captureDifference(capture);
				break;
			case CaptureModeSkin:
				captureSkin(capture);
				break;
		}
		
		if ( key == 'q' ) {
			break;
		} else if ( key == 's' ) {
			cvSaveImage("saved.bmp", cvQueryFrame(capture), 0);
		} else if ( key == 'c' ) {
			switch ( mode ) {
				case CaptureModeDifference:
					captureDifferenceDestroy();
					captureSkinSetup();
					break;
				case CaptureModeSkin:
					captureSkinDestroy();
					captureDifferenceSetup();
					break;
			}
			mode = (CaptureModeSkin == mode) ? CaptureModeDifference : CaptureModeSkin;
		} else if ( key == 'b' ) {
			switch ( mode ) {
				case CaptureModeDifference:
					captureDifferenceBackground(capture);
					break;
				case CaptureModeSkin:
					captureSkinBackground(capture);
					break;
			}
		}
	}
	
	cvReleaseCapture(&capture);
	
	return 0;
}
