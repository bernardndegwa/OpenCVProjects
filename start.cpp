#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void onMouse(int event, int x, int y, int flags, void* param){
	
	cv::Mat *im = reinterpret_cast<cv::Mat*>(param);
	
	switch(event) {	//dispatch the event
		case CV_EVENT_LBUTTONDOWN: //Left mouse button down event
		//display pixel at x and y coordinates
		cout << "At (" << x << " , " << y << ") value is: "
			<< static_cast<int>(
				im->at<uchar>(cv::Point(x,y))) << endl;
		break;
		
	}
}

int main (int argc, char** argv){
	cv::Mat image, result;
	//cout<< "This image is "<<image.rows << " * " << image.cols<<endl;
	image = cv::imread("/home/bernard/Everette/2-14.jpg", CV_LOAD_IMAGE_COLOR);
	//if(!image.empty())
		cout << "The image has "<<image.channels() <<"channels"<<endl;
		cv::namedWindow("kde");
		cv::imshow("kde", image);		
	//}
	cv::setMouseCallback("kde", onMouse,
				reinterpret_cast<void*>(&image));	
	cv::flip(image, result, 0);
	cv::namedWindow("Flipped");
	cv::imshow("Flipped", result);
	cv::waitKey(0);
	cv::imwrite("output.ppm", result);
	
	cv::putText(image,							//destination image
				"This is Everette at two",		//text to overlay
				cv::Point(40, 200),				//text position
				cv::FONT_HERSHEY_PLAIN,			//Font type
				2.0,							//font scale
				255,							//text color(white)
				2);								//text thickness
	
	
	/* This method of drawing a circle on an image will only work on gray scale images
	cv::circle(image, 					//destination image
				cv::Point(275, 230),	//center coordinate
				65,						//radius
				0,						//color (black in this case)
				50);					//thickness
				
	*/

}
