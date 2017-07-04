#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;

int main()
{
	cv::Mat frame;
	cv::VideoCapture cap(0);

	if(cap.isOpened() != true) {
        	return -1;
	}

	while(cap.read(frame)){   
		cv::Mat src = cv::Mat(frame);
		cv::imshow( "window",  src );
		cv::waitKey(30);
	}

	return 0;
}
