#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
/*
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
*/

int main()
{
    IplImage* img = cvLoadImage("/home/bernard/Desktop/Computer_Vision/videos/sporti.jpeg",CV_LOAD_IMAGE_COLOR);
    cvNamedWindow("opencvtest",CV_WINDOW_AUTOSIZE);
    cvShowImage("opencvtest",img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    return 0;
}
