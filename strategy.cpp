#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

//Using the strategy design pattern in a vision application


	
	//	Computes	the	distance	from	target	color.
int	getDistanceToTargetColor(const	cv::Vec3b&	color)	const	{
		return	getColorDistance(color,	target);
}

//	Computes	the	city-block	distance	between	two	colors.
int	getColorDistance(const	cv::Vec3b&	color1,	const	cv::Vec3b&	color2)	const	{
		return	abs(color1[0]-color2[0])+ abs(color1[1]-color2[1]) + abs(color1[2]-color2[2]);
	}
	
	
cv::Mat	ColorDetector::process(const	cv::Mat	&image)	{
					//	re-allocate	binary	map	if	necessary
					//	same	size	as	input	image,	but	1-channel
					result.create(image.size(),CV_8U);
					
						//	get	the	iterators
	cv::Mat_<cv::Vec3b>::const_iterator	it=	image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator	itend=image.end<cv::Vec3b>();
	cv::Mat_<uchar>::iterator	itout=	result.begin<uchar>();
					//	for	each	pixel
	for	(;	it!=itend;	++it, ++itout){
			//	compute	distance	from	target	color
	if	(getDistanceToTargetColor(*it)<=maxDist){
		*itout=	255;
		}
	else{
		*itout=	0;
		}
	}
		return	result;
}


int main(int argc, char** argv){
	//1. Create image proccessor object
	ColorDetector cdetect;
	
	//2. Read input image
	cv::Mat image= cv::imread("/home/bernard/pics/6.jpg"); //read the image
	if(image.empty())
		return 0;
		
	//3. Set input parameters
	cdetect.setTargetColor(230,190,130);	//blue sky
	
	//4. Process the image and displat the result
	cv::namedWindow("Result");
	cv::imshow("result",cdetect.process(image));
	
	cv::waitKey();
	
	return 0;
}
