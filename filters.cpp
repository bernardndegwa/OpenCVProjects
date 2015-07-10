#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
	// Read input image
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg",0);
	if (!image.data)
		return 0; 
	// image is resize for book printing
	cv::resize(image, image, cv::Size(), 0.6, 0.6);

    // Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image",image);
	cv::waitKey(0);

	// Blur the image
	cv::Mat result;
	cv::GaussianBlur(image,result,
		  cv::Size(5,5), // size of the filter
		  1.5);			 // parameter controlling the 
						 // shape of the Gaussian

    // Display the blurred image
	cv::namedWindow("Gaussian filtered Image");
	cv::imshow("Gaussian filtered Image",result);
	cv::waitKey(0);

	cv::GaussianBlur(image,result,cv::Size(9,9),1.7);

    // Display the blurred image
	cv::namedWindow("Gaussian filtered Image (9x9)");
	cv::imshow("Gaussian filtered Image (9x9)",result);
	cv::waitKey(0);

	// Get the gaussian kernel (1.5)
	cv::Mat gauss= cv::getGaussianKernel(9,1.5,CV_32F);
		  
	// Display kernel values
	cv::Mat_<float>::const_iterator it= gauss.begin<float>();  
	cv::Mat_<float>::const_iterator itend= gauss.end<float>();  
	std::cout << "1.5 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the gaussian kernel (0.5)
	gauss= cv::getGaussianKernel(9,0.5,CV_32F);
		  
	// Display kernel values
	it= gauss.begin<float>();  
	itend= gauss.end<float>();  
	std::cout << "0.5 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the gaussian kernel (2.5)
	gauss= cv::getGaussianKernel(9,2.5,CV_32F);
		  
	// Display kernel values
	it= gauss.begin<float>();  
	itend= gauss.end<float>();  
	std::cout << "2.5 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the gaussian kernel (9 elements)
	gauss= cv::getGaussianKernel(9,-1,CV_32F);
		  
	// Display kernel values
	it= gauss.begin<float>();  
	itend= gauss.end<float>();  
	std::cout << "9 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the Deriv kernel (2.5)
	cv::Mat kx, ky;
    cv::getDerivKernels(kx,ky,2,2,7,true);
		  
	// Display kernel values
	cv::Mat_<float>::const_iterator kit= kx.begin<float>();  
	cv::Mat_<float>::const_iterator kitend= kx.end<float>();  
	std::cout << "[";
	for ( ; kit!= kitend; ++kit) {
		std::cout << *kit << " ";
	}
	std::cout << "]" << std::endl;

	// Blur the image with a mean filter
	cv::blur(image,result,cv::Size(5,5));
		
    // Display the blurred image
	cv::namedWindow("Mean filtered Image");
	cv::imshow("Mean filtered Image",result);

	// Blur the image with a mean filter 9x9
	cv::blur(image,result,cv::Size(9,9));
		
    // Display the blurred image
	cv::namedWindow("Mean filtered Image (9x9)");
	cv::imshow("Mean filtered Image (9x9)",result);
	cv::waitKey(0);

	// Read input image with salt&pepper noise
	image= cv::imread("/home/bernard/pics/6.jpg",0);
	if (!image.data)
		return 0; 

    // Display the S&P image
	cv::namedWindow("/home/bernard/pics/6.jpg");
	cv::imshow("S&P Image",image);
	cv::waitKey(0);

	// Blur the image with a mean filter
	cv::blur(image,result,cv::Size(5,5));
		
    // Display the blurred image
	cv::namedWindow("Mean filtered Image");
	cv::imshow("Mean filtered Image",result);
	cv::waitKey(0);

	// Applying a median filter
	cv::medianBlur(image,result,5);
		
    // Display the blurred image
	cv::namedWindow("Median filtered Image");
	cv::imshow("Median filtered Image",result);
	cv::waitKey(0);

	// Resizing the image 
	image = cv::imread("/home/bernard/pics/6.jpg", 0);
	cv::Mat resized;
	cv::resize(image, resized,
		cv::Size(), 1.0 / 4.0, 1.0 / 4.0); // 1/4 resizing
	cv::resize(resized, resized, cv::Size(), 2, 2, cv::INTER_NEAREST);
	// Display the reduced image
	cv::namedWindow("Resized Image");
	cv::imshow("Resized Image", resized);
	cv::waitKey(0);

	// Reduce by 4 the size of the image (the wrong way)
	image= cv::imread("/home/bernard/pics/6.jpg",0);
	cv::Mat reduced(image.rows / 4, image.cols / 4, CV_8U);

	for (int i=0; i<reduced.rows; i++)
		for (int j=0; j<reduced.cols; j++)
			reduced.at<uchar>(i,j)= image.at<uchar>(i*4,j*4);

    // Display the reduced image
	cv::namedWindow("Badly reduced Image");
	cv::imshow("Badly reduced Image",reduced);
	cv::waitKey(0);

	cv::resize(reduced,reduced, cv::Size(),2,2,cv::INTER_NEAREST);

    // Display the (resized) reduced image
	cv::namedWindow("Badly reduced");
	cv::imshow("Badly reduced",reduced);
	cv::waitKey(0);

	cv::imwrite("badlyreducedimage.bmp",reduced);

	// first remove high frequency component
	cv::GaussianBlur(image,image,cv::Size(11,11),1.75);
	// keep only 1 of every 4 pixels
	cv::Mat reduced2(image.rows/4,image.cols/4,CV_8U);
	for (int i=0; i<reduced2.rows; i++)
		for (int j=0; j<reduced2.cols; j++)
			reduced2.at<uchar>(i,j)= image.at<uchar>(i*4,j*4);

    // Display the reduced image
	cv::namedWindow("Reduced Image, original size");
	cv::imshow("Reduced Image, original size",reduced2);
	cv::waitKey(0);

	cv::imwrite("reducedimage.bmp",reduced2);

	// resizing with NN
	cv::Mat newImage;
	cv::resize(reduced2, newImage, cv::Size(), 2, 2,cv::INTER_NEAREST);

    // Display the (resized) reduced image
	cv::namedWindow("Reduced Image");
	cv::imshow("Reduced Image",newImage);
	cv::waitKey(0);

	// resizing with bilinear
	cv::resize(reduced2, newImage, cv::Size(), 3, 3, cv::INTER_LINEAR);

	// Display the (resized) reduced image
	cv::namedWindow("Bilinear resizing");
	cv::imshow("Bilinear resizing", newImage);
	cv::waitKey(0);

	// resizing with nearest-neighbor
	cv::resize(reduced2, newImage, cv::Size(), 3, 3, cv::INTER_NEAREST);

	// Display the (resized) reduced image
	cv::namedWindow("Nearest-neighbor resizing");
	cv::imshow("Nearest-neighbor resizing", newImage);

	cv::waitKey();
	return 0;
}
