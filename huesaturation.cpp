#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <vector>

void detectHScolor(const cv::Mat& image,		// input image 
	double minHue, double maxHue,	// Hue interval 
	double minSat, double maxSat,	// saturation interval
	cv::Mat& mask) {				// output mask

	// convert into HSV space
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);

	// split the 3 channels into 3 images
	std::vector<cv::Mat> channels;
	cv::split(hsv, channels);
	// channels[0] is the Hue
	// channels[1] is the Saturation
	// channels[2] is the Value

	// Hue masking
	cv::Mat mask1; // under maxHue
	cv::threshold(channels[0], mask1, maxHue, 255, cv::THRESH_BINARY_INV);
	cv::Mat mask2; // over minHue
	cv::threshold(channels[0], mask2, minHue, 255, cv::THRESH_BINARY);

	cv::Mat hueMask; // hue mask
	if (minHue < maxHue)
		hueMask = mask1 & mask2;
	else // if interval crosses the zero-degree axis
		hueMask = mask1 | mask2;

	// Saturation masking
	// under maxSat
	cv::threshold(channels[1], mask1, maxSat, 255, cv::THRESH_BINARY_INV);
	// over minSat
	cv::threshold(channels[1], mask2, minSat, 255, cv::THRESH_BINARY);

	cv::Mat satMask; // saturation mask
	satMask = mask1 & mask2;

	// combined mask
	mask = hueMask&satMask;
}

int main()
{
	// read the image
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg");
	if (!image.data)
		return 0; 

	// show original image
	cv::namedWindow("Original image");
	cv::imshow("Original image",image);
	cv::waitKey(0);

	// convert into HSV space
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);

	// split the 3 channels into 3 images
	std::vector<cv::Mat> channels;
	cv::split(hsv,channels);
	// channels[0] is the Hue
	// channels[1] is the Saturation
	// channels[2] is the Value

	// display value
	cv::namedWindow("Value");
	cv::imshow("Value",channels[2]);
	cv::waitKey(0);
	
	// display saturation
	cv::namedWindow("Saturation");
	cv::imshow("Saturation",channels[1]);
	cv::waitKey(0);
	
	// display hue
	cv::namedWindow("Hue");
	cv::imshow("Hue",channels[0]);
	cv::waitKey(0);
	
	// image with fixed value
	cv::Mat newImage;
	cv::Mat tmp(channels[2].clone());
	// Value channel will be 255 for all pixels
	channels[2]= 255;  
	// merge back the channels
	cv::merge(channels,hsv);
	// re-convert to BGR
	cv::cvtColor(hsv,newImage,CV_HSV2BGR);

	cv::namedWindow("Fixed Value Image");
	cv::imshow("Fixed Value Image",newImage);
	cv::waitKey(0);
	
	// image with fixed saturation
	channels[1]= 255;
	channels[2]= tmp;
	cv::merge(channels,hsv);
	cv::cvtColor(hsv,newImage,CV_HSV2BGR);

	cv::namedWindow("Fixed saturation");
	cv::imshow("Fixed saturation",newImage);
	cv::waitKey(0);

	// image with fixed value and fixed saturation
	channels[1]= 255;
	channels[2]= 255;
	cv::merge(channels,hsv);
	cv::cvtColor(hsv,newImage,CV_HSV2BGR);

	cv::namedWindow("Fixed saturation/value");
	cv::imshow("Fixed saturation/value",newImage);
	cv::waitKey(0);
	
	// Testing skin detection

	// read the image
	image= cv::imread("/home/bernard/pics/E5.jpg");
	if (!image.data)
		return 0; 

	// show original image
	cv::namedWindow("Original image");
	cv::imshow("Original image",image);
	cv::waitKey(0);
	
	// detect skin tone
	cv::Mat mask;
	detectHScolor(image, 
		160, 10, // hue from 320 degrees to 20 degrees 
		25, 166, // saturation from ~0.1 to 0.65
		mask);

	// show masked image
	cv::Mat detected(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	image.copyTo(detected, mask);
	cv::imshow("Detection result",detected);
	cv::waitKey(0);
	
	// A test comparing luminance and brightness

	// create linear intensity image
	cv::Mat linear(100,256,CV_8U);
	for (int i=0; i<256; i++) {

		linear.col(i)= i;
	}

	// create a Lab image
	linear.copyTo(channels[0]);
	cv::Mat constante(100,256,CV_8U,cv::Scalar(128));
	constante.copyTo(channels[1]);
	constante.copyTo(channels[2]);
	cv::merge(channels,image);

	// convert back to BGR
	cv::Mat brightness;	cv::cvtColor(image,brightness, CV_Lab2BGR);
	cv::split(brightness, channels);

	// create combined image
	cv::Mat combined(200,256, CV_8U);
	cv::Mat half1(combined,cv::Rect(0,0,256,100));
	linear.copyTo(half1);
	cv::Mat half2(combined,cv::Rect(0,100,256,100));
	channels[0].copyTo(half2);

	cv::namedWindow("Luminance vs Brightness");
	cv::imshow("Luminance vs Brightness",combined);
	cv::waitKey(0);
	
}