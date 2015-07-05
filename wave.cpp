#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

//Creating a wavy effect on an image

void wave(const cv::Mat &image, cv::Mat &result){
	
		//map functions
		cv::Mat srcX(image.rows, image.cols, CV_32F);
		cv::Mat srcY(image.rows, image.cols, CV_32F);
		
		//creating the mapping
		for(int i=0; i<image.rows; i++){
			for (int j=0; j<image.cols; j++){
				//new location of pixel at (i,j)
				srcX.at<float>(i,j)=j;	//remain on same column
				//pixels originally on row i will be moved following a sinusoid
				srcY.at<float>(i,j)=i+5*sin(j/10.0);
			}
		}
		//apply the remapping
		cv::remap(image, result, srcX, srcY, cv::INTER_LINEAR);
	}

int main(int argc, char** argv){
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg"); //read the image
	//cv::Mat result = image.t();			//transpose of the matrix
	cv::Mat result;
	result.create(image.size(), image.type());
	wave(image, result);
	//kernelsharpen(image, result);
	//colorReduce(image,64);	//process the image
	cv::namedWindow("Image");
	cv::namedWindow("SharpenedImage");
	cv::imshow("Image", image);		//display the image+12163083175
	cv::imshow("SharpenedImage", result);
	cv::waitKey(0);
}
