#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "colordetector.h"
#include "colordetector.cpp"

int main()
{
    // 1. Create image processor object
	ColorDetector cdetect;

    // 2. Read input image
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg");
	if (image.empty())
		return 0; 

    // 3. Set input parameters
	cdetect.setTargetColor(230,190,130); // here blue sky

   // 4. Process the image and display the result
	cv::namedWindow("result");
	cv::imshow("result",cdetect.process(image));

	// or using functor
	ColorDetector colordetector(230, 190, 130,  // color
		                             45, true); // Lab threshold
	cv::namedWindow("result (functor)");
	cv::imshow("result (functor)",colordetector(image));

	cv::waitKey();

	return 0;
}

