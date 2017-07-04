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

	CvPoint p1, p2, p3, p4;
	CvPoint tag_center;

	while(video_capture.read(raw_image)) {
		//start timer
		start = getTickCount();

		//convert to grey image
		cv::cvtColor(raw_image, grey_image, CV_BGR2GRAY);

		//detect Apriltags
		vector<AprilTags::TagDetection> detections = tag_detector.extractTags(grey_image);		

		//stop timer
		end = getTickCount();

		//calcuate fps
		duration = (end - start) / getTickFrequency();
		fps = 1.0f / duration;

		if(detections.size() > 0) {
			p1.x = detections.at(0).p[0].first;
			p1.y = detections.at(0).p[0].second;

			p2.x = detections.at(0).p[1].first;
			p2.y = detections.at(0).p[1].second;

			p3.x = detections.at(0).p[2].first;
			p3.y = detections.at(0).p[2].second;

			p4.x = detections.at(0).p[3].first;
			p4.y = detections.at(0).p[3].second;

			tag_center.x = detections.at(0).cxy.first;
			tag_center.y = detections.at(0).cxy.second;

			cv::line(raw_image, p1, p2, Scalar(0, 255, 0), 2, CV_AA);
			cv::line(raw_image, p2, p3, Scalar(0, 0, 255), 2, CV_AA);
			cv::line(raw_image, p3, p4, Scalar(255, 0, 0), 2, CV_AA);
			cv::line(raw_image, p4, p1, Scalar(255, 0, 0), 2, CV_AA);

			cv::circle(raw_image, tag_center, 2, Scalar(0, 0, 255), 2, CV_AA, 0);

			printf("[fps: %.2f] tag detected, id = %d.\n", fps, detections.at(0).id);
		} else {
			printf("[fps: %.2f] no tag was found.\n", fps);	
		}

		cv::imshow("window", raw_image);
		cv::waitKey(30);
	}

	return 0;
}
