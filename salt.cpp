#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void salt(cv::Mat image, int n){
	int i, j;
	for (int k=0; k<n; k++){
		//rand() is the random number generator
		i = rand()%image.cols;
		j = rand()%image.rows;
		
		if (image.type() == CV_8UC1) { // gray-level image 
			image.at<uchar>(j,i) = 255;		
			
		}
		else if (image.type() == CV_8UC3)//color image 
		 {
			image.at<cv::Vec3b>(j,i)[0] = 255;
			image.at<cv::Vec3b>(j,i)[1] = 255;
			image.at<cv::Vec3b>(j,i)[1] = 255;
		}		
	}	
}

int main (int argc, char** argv){
		cv::Mat image = cv::imread("/home/bernard/pics/6.jpg", CV_LOAD_IMAGE_COLOR);
		salt(image, 3000); 	//function to add noise)
		
		cv::namedWindow("Image");
		cv::imshow("Image", image);
		cv::waitKey(0);
}
