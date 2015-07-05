#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void sharpen(const cv::Mat &image, cv::Mat &result){
		//allocate if necessary
		//result.create(image.size(), image.type());
		int nchannels= image.channels();	//get number of channels
		
		//for all rows (except first and last)
		for (int j=1; j<image.rows-1; j++){
			const uchar* previous= image.ptr<const uchar>(j-1);	//previous row
			const uchar* next= image.ptr<const uchar>(j+1);	//next row
			const uchar* current= image.ptr<const uchar>(j);	//current
			
			uchar* output= result.ptr<uchar>(j);	//output row
			
			for (int i=nchannels; i<(image.cols-1)*nchannels; i++){
				*output++= cv::saturate_cast<uchar>(5*current[i]-current[i-nchannels]-
													current[i+nchannels]-previous[i]-next[i]);
			}		
		}
		//set the unprocessed pixels to 0
		result.row(0).setTo(cv::Scalar(0));
		result.row(result.rows-1).setTo(cv::Scalar(0));
		result.col(result.cols-1).setTo(cv::Scalar(0));
		result.col(result.cols-1).setTo(cv::Scalar(0));
		//return result;
	}

int main(int argc, char** argv){
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg"); //read the image
	cv::Mat result;
	result.create(image.size(), image.type());
	sharpen(image, result);
	//colorReduce(image,64);	//process the image
	cv::namedWindow("Image");
	cv::namedWindow("SharpenedImage");
	cv::imshow("Image", image);		//display the image+12163083175
	cv::imshow("SharpenedImage", result);
	cv::waitKey(0);
}
