#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "histogram.h"

int main()
{
	// Read input image
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return 0; 
	// Resize by 70% 
	cv::resize(image, image, cv::Size(), 0.7, 0.7);

	// save grayscale image
	cv::imwrite("groupBW.jpg", image);

    // Display the image
	cv::namedWindow("Image");
	cv::imshow("Image",image);
	cv::waitKey(0);

	// The histogram object
	Histogram1D h;

    // Compute the histogram
	cv::Mat histo= h.getHistogram(image);

	// Loop over each bin
	for (int i=0; i<256; i++) 
		cout << "Value " << i << " = " << histo.at<float>(i) << endl;  

	// Display a histogram as an image
	cv::namedWindow("Histogram");
	cv::imshow("Histogram",h.getHistogramImage(image));
	cv::waitKey(0);

	// creating a binary image by thresholding at the valley
	cv::Mat thresholded; // output binary image
	cv::threshold(image,thresholded,
		          60,    // threshold value
				  255,   // value assigned to pixels over threshold value
				  cv::THRESH_BINARY); // thresholding type
 
	// Display the thresholded image
	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image",thresholded);
	cv::waitKey(0);
	thresholded = 255 - thresholded;
	cv::imwrite("binary.bmp",thresholded);

	// Equalize the image
	cv::Mat eq= h.equalize(image);

	// Show the result
	cv::namedWindow("Equalized Image");
	cv::imshow("Equalized Image",eq);
	cv::waitKey(0);
	
	// Show the new histogram
	cv::namedWindow("Equalized Histogram");
	cv::imshow("Equalized Histogram",h.getHistogramImage(eq));
	cv::waitKey(0);

	// Stretch the image, setting the 1% of pixels at black and 1% at white
	cv::Mat str= h.stretch(image,0.01f);

	// Show the result
	cv::namedWindow("Stretched Image");
	cv::imshow("Stretched Image",str);
	cv::waitKey(0);

	// Show the new histogram
	cv::namedWindow("Stretched Histogram");
	cv::imshow("Stretched Histogram",h.getHistogramImage(str));
	cv::waitKey(0);

	// Create an image inversion table
	int dim(256);
	cv::Mat lut(1,  // 1 dimension
		&dim,       // 256 entries
		CV_8U);     // uchar
	// or cv::Mat lut(256,1,CV_8U);

	for (int i=0; i<256; i++) {
		
		lut.at<uchar>(i)= 255-i;
	}

	// Apply lookup and display negative image
	cv::namedWindow("Negative image");
	cv::imshow("Negative image",h.applyLookUp(image,lut));
	cv::waitKey(0);

	cv::waitKey();
	return 0;
}

