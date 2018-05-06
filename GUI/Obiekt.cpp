#include <iostream>
//cv::Mat kontur(kontur.rows, kontur.cols, CV_8UC3, cv::Scalar(255, 255, 255));
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>



class Obiekt
{
public:
	
	Obiekt() {};
	Obiekt(cv::Rect rectangle,int Hmin,int Hmax, cv::Mat mat_contour, cv::Mat histogram)
	{
		this->rectangle = rectangle;
		this->Hmax = Hmax;
		this->Hmin = Hmin;
		this->mat_contour = mat_contour;
		this->histogram = histogram;
	}

	void setRectangle_tracked(cv::RotatedRect rectangle_tracked) { this->rectangle_tracked = rectangle_tracked; }
	cv::RotatedRect getRectangle_tracked() { return this->rectangle_tracked; }
	void setMat_contour(cv::Mat mat_contour) { this->mat_contour = mat_contour; }
	cv::Mat getMat_contour() { return this->mat_contour; }
	void setHmin(double Hmin) { this->Hmin = Hmin; }
	double getHmin() { return this->Hmin; }
	void setHmax(double Hmax) { this->Hmax = Hmax; }
	double getHmax() { return this->Hmax; }
	cv::Rect getRectangle()
	{		
		return this->rectangle;
	}
	void setRectangle(cv::Rect rectangle)
	{
		this->rectangle = rectangle;
	}
	void sethistogram(cv::Mat histogram)
	{
		this->histogram = histogram;
	}
	cv::Mat gethistogram()
	{
		return this->histogram;
	}
	
private:
	cv::Rect rectangle;
	double Hmin, Hmax;
	cv::Mat histogram;
	cv::Mat mat_contour;
	cv::RotatedRect rectangle_tracked;
};
