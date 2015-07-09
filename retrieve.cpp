#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "imagecomparator.h"

int main()
{
	// Read reference image
	cv::Mat image= cv::imread("/home/bernard/pics/2.jpg");
	if (!image.data)
		return 0; 

	// Display image
	cv::namedWindow("Query Image");
	cv::imshow("Query Image",image);

	ImageComparator c;
	c.setReferenceImage(image);

	// Read an image and compare it with reference
	cv::Mat input= cv::imread("/home/bernard/pics/1.jpg");
	cout << "waves vs dog: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input= cv::imread("/home/bernard/pics/4.jpg");
	cout << "waves vs marais: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input= cv::imread("/home/bernard/pics/5.jpg");
	cout << "waves vs bear: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input= cv::imread("/home/bernard/pics/6.jpg");
	cout << "waves vs beach: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input= cv::imread("/home/bernard/pics/7.jpg");
	cout << "waves vs polar: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input= cv::imread("/home/bernard/pics/8.jpg");
	cout << "waves vs moose: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input= cv::imread("/home/bernard/pics/9.jpg");
	cout << "waves vs lake: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input= cv::imread("/home/bernard/pics/10.jpg");
	cout << "waves vs fundy: " << c.compare(input) << endl;

	cv::waitKey();
	return 0;
}
