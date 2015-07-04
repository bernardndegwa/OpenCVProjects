#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void colorReduce(cv::Mat image, int div){
	int nl= image.rows; 	//number of lines 
	//total number of elements per line
	int nc= image.cols * image.channels();
	
	for (int j=0; j<nl; j++){
		//get the address of row j
		uchar* data= image.ptr<uchar>(j);
		
		for (int i=0; i<nc; i++){
			//process each pixel
			data[i]= data[i]/div*div + div/2;
			//end of each line
			
			//or use bitwise operations which result in efficeincy 
			//especially in embedded processing
			
			/*int n;
			div= pow(2,n);
			uchar mask= 0xFF<<n;	//the mask to round the pixel value
									//for div=16 , mask= 0xF0
			*data &=mask;		//masking
			*data++ +=div>>1;
				*/					
		}//end of pixel processing
		
	}
}

int main(int argc, char** argv){
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg"); //read the image
	colorReduce(image,64);	//process the image
	cv::namedWindow("Image");
	cv::imshow("Image", image);		//display the image
	cv::waitKey(0);
}











