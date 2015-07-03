#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char** argv){
	//read an image
	cv::Mat image1= cv::imread("/home/bernard/pics/6.jpg");
	cv::Mat logo= cv::imread("/home/bernard/pics/1.jpg");
	cv::Mat image2= cv::imread("/home/bernard/pics/6.jpg");
	cv::namedWindow("Image1");
	cv::imshow("Image1", image1);
	cv::waitKey(0);
	
	
			//	define	image	ROI	at	image	bottom-right
		//cv::Mat	imageROI(image,	cv::Rect(image.cols-logo.cols,image.rows-logo.rows,logo.cols,logo.rows));//	ROI	size
		//	insert	logo
		//logo.copyTo(imageROI);
	//image range issues check online or so==================================
	
	cv::Mat imageROI = image1;
	cv::imshow("ImageROI", imageROI);
	cv::waitKey(0);
	imageROI=image1(cv::Range(image1.rows-logo.rows,image1.rows),cv::Range(image1.cols-logo.cols,image1.cols));
	cv::imshow("ImageRange", imageROI);
	cv::waitKey(0);
	//	define	image	ROI	at	image	bottom-right
	imageROI=	image1(cv::Rect(image1.cols-logo.cols, image1.rows-logo.rows, logo.cols,logo.rows));
	//	use	the	logo	as	a	mask	(must	be	gray-level)
	cv::Mat	mask(logo);
	//	insert	by	copying	only	at	locations	of	non-zero	mask
	logo.copyTo(imageROI,mask);
/*
	====================OpenCV 2.4:

src.copyTo(dst(Rect(left, top, src.cols, src.rows)));================================
* /
	//imageROI.copyTo(image2);
	
	//cv::Mat imageROI(image,cv::Rect(510,75,340, 240));	
	
	/*
	cv::Mat imageROI(image,
			cv::Rect(image.cols-logo.cols,		//region of interest coordinates
			image.rows-logo.rows,
			logo.cols, logo.rows));				//region of interest size
	*/
	//insert the logo
	//logo.copyTo(imageROI);
	//cv::namedWindow("Image2");
	cv::imshow("Image1", imageROI);
	cv::waitKey(0);
	return(0);
}
