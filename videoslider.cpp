#include <stdlib>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int g_slider_position = 0;
cv::videoCapture cap = NULL;

void onTrackbarSlide(int pos){
	cv::setCaptureProperty(
	cap,
	CV_CAP_PROP_POS_FRAMES,
	pos
	);
}


int main(char argc, char** argv){
	
	cv::namedWindow("Slider", CV_WINDOW_AUTOSIZE);
	cap = cv::createFileCapture(argv[1]);
	int frames = (int)cv::getCaptureProperty(
							cap, 
							CV_CAP_PROP_FRAME_COUNT
							);
	if( frames!=0 ){
		cv::createTrackbar(
		"Position",
		"Slider",
		&g_slider_position,
		frames,
		onTrackbarSlide
		);
	cv::image im;
	while(1){
		im = cv::queryFrame( ca


 
} 
