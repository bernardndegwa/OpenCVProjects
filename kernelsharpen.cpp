#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void kernelsharpen(const cv::Mat &image, cv::Mat &result){
	
		//construct kernel with all entries as 0
		cv::Mat kernel(3,3, CV_32F, cv::Scalar(0));
		//assign kernel values
		kernel.at<float>(1,1)=5.0;
		kernel.at<float>(0,1)=	-1.0;
		kernel.at<float>(2,1)=	-1.0;
		kernel.at<float>(1,0)=	-1.0;
		kernel.at<float>(1,2)=	-1.0;
		//filter	the	image
		cv::filter2D(image,result,image.depth(),kernel);

	}

int main(int argc, char** argv){
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg"); //read the image
	//cv::Mat result = image.t();			//transpose of the matrix
	result.create(image.size(), image.type());
	kernelsharpen(image, result);
	//colorReduce(image,64);	//process the image
	cv::namedWindow("Image");
	cv::namedWindow("SharpenedImage");
	cv::imshow("Image", image);		//display the image+12163083175
	cv::imshow("SharpenedImage", result);
	cv::waitKey(0);
}
