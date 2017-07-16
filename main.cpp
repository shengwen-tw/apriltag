#include <sys/time.h>

#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

#include "AprilTags/TagDetector.h"
#include "AprilTags/Tag16h5.h"
#include "AprilTags/Tag25h7.h"
#include "AprilTags/Tag25h9.h"
#include "AprilTags/Tag36h9.h"
#include "AprilTags/Tag36h11.h"

using namespace cv;

int main()
{
	cv::Mat raw_image, grey_image;
	cv::VideoCapture video_capture(0);
	video_capture.set(CV_CAP_PROP_FPS, 120);

	AprilTags::TagCodes tag_code(AprilTags::tagCodes36h11);
	AprilTags::TagDetector tag_detector(tag_code);

	if(video_capture.isOpened() == false) {
		printf("Failed to open the camera!\n");
        	return 0;
	}

	float start, end;
	float duration, fps;

	//start timer
	start = getTickCount();

	while(video_capture.read(raw_image)) {
		//convert to grey image
		cv::cvtColor(raw_image, grey_image, CV_BGR2GRAY);

		//detect Apriltags
		vector<AprilTags::TagDetection> detections = tag_detector.extractTags(grey_image);		

		//stop timer
		end = getTickCount();

		//calcuate fps
		duration = (end - start) / getTickFrequency();
		fps = 1.0f / duration;
		start = end;

		for(int i = 0; i < (int)detections.size(); i++) {
			detections.at(i).draw(raw_image);
		}

		if(detections.size() > 0) {
			printf("[fps: %.2f] %ld tags.\n", fps, detections.size());
		} else {
			printf("[fps: %.2f] no tag was found.\n", fps);	
		}

		cv::imshow("window", raw_image);
		cv::waitKey(30);
	}

	return 0;
}
