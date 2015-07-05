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
		//This method image.ptr<TYPE> directly gives you the address of
		//the image row.
		
		for (int i=0; i<nc; i++){
			//process each pixel
			data[i]= data[i]/div*div + div/2;
			//end of each line
			//an alternative way to move from column to column would:
			
			*data = *data/(div*div) + (div/2); data++;
			
			//or use bitwise operations which result in efficiency 
			//especially in embedded processing
			
			/*int n; we assume that div will be always be a power of 2
			//div= pow(2,n);
			uchar mask= 0xFF<<n;	//the mask to round the pixel value
									//for div=16 , mask= 0xF0
			*data &=mask;		//masking
			*data++ +=div>>1;
				*/					
		}//end of pixel processing
		
	}
}

//An alternative way to change the image and save it
//The resulting image should be stored in a data buffer with a size,
//and pixel type that matches the input type.
cv::Mat image= cv::imread("/home/bernard/pics/6.jpg"); //read the image
cv::Mat result;
result.create(image.rows, image.cols, image.type());
//The	allocated	memory	block	has	a	size	of	total()*elemSize().	
//The	looping	is	then	done with	two	pointers:
//

void colorReduce(const::cv Mat &image, cv::Mat &result, int div=64)
{
//with this method signature the image is passed in as a const and will not 
//be changed while the address of the result is where the image.
}

int main(int argc, char** argv){
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg"); //read the image
	colorReduce(image,64);	//process the image
	cv::namedWindow("Image");
	cv::imshow("Image", image);		//display the image+12163083175
	cv::waitKey(0);
}











