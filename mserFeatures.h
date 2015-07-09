#if !defined MSERF
#define MSERF

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

class MSERFeatures {

  private:

	  cv::MSER mser;        // mser detector
	  double minAreaRatio;  // extra rejection parameter

  public:

	  MSERFeatures(int minArea=60, int maxArea=14400, // aceptable size range 
		           double minAreaRatio=0.5, // min value for MSER area/bounding-rect area
				   int delta=5, // delta value used for stability measure
				   double maxVariation=0.25, // max allowed area variation
				   double minDiversity=0.2)  // min size increase between child and parent
		              : mser(delta,minArea,maxArea,maxVariation,minDiversity), 
					    minAreaRatio(minAreaRatio) {}

	  // get the rotated bouding rectangles corresponding to each MSER feature
	  // if (mser area / bounding rect area) < areaRatio, the feature is rejected
	  void getBoundingRects(const cv::Mat &image, std::vector<cv::RotatedRect> &rects) {

		  // detect MSER features
          std::vector<std::vector<cv::Point> > points;
		  mser(image, points);

		  // for each detected feature
          for (std::vector<std::vector<cv::Point> >::iterator it= points.begin();
			   it!= points.end(); ++it) {
				   
			  // Extract bouding rectangles
			  cv::RotatedRect rr= cv::minAreaRect(*it);
		
			  // check area ratio
			  if (it->size() > minAreaRatio*rr.size.area())
				rects.push_back(rr);
		  }
	  }

	  // draw the rotated ellipses corresponding to each MSER feature
	  cv::Mat getImageOfEllipses(const cv::Mat &image, std::vector<cv::RotatedRect> &rects, cv::Scalar color=255) {

		  // image on which to draw
		  cv::Mat output= image.clone();

		  // get the MSER features
		  getBoundingRects(image, rects);

		  // for each detected feature
		  for (std::vector<cv::RotatedRect>::iterator it= rects.begin();
			   it!= rects.end(); ++it) {

			  cv::ellipse(output,*it,color);
		  }

		  return output;
	  }

	  double getAreaRatio() {

		  return minAreaRatio;
	  }

	  void setAreaRatio(double ratio) {

		  minAreaRatio= ratio;
	  }
};


#endif
