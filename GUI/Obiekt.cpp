#include <iostream>
//cv::Mat kontur(kontur.rows, kontur.cols, CV_8UC3, cv::Scalar(255, 255, 255));
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>


struct Drawing_Position
{
	cv::Point2i point = cv::Point2i(0, 0);
	int r = 0;

	Drawing_Position()
	{
		this->point = cv::Point2i(0, 0);
		this->r = 0;
	}
	Drawing_Position(cv::Point2i point, int r)
	{
		this->point = point;
		this->r = r;
	}
};
class Obiekt
{
public:
	cv::Rect rectangle;
	Obiekt() {};
	int erode, dilate, blur;
	int Hmin, Hmax;
	cv::Mat mat_contour;
	cv::Mat mat_backproj;
	Drawing_Position position;
	
	void deactivate_drawing()
	{
		this->Is_drawing_Pencil_active = false;
		this->Is_drawing_rectangle_active = false;
		this->Is_drawing_circle_active = false;
		this->Is_drawing_line_active = false;
	}
	Obiekt(cv::Rect rectangle,int Hmin,int Hmax,cv::Mat histogram)
	{
		this->rectangle = rectangle;
		this->Hmax = Hmax;
		this->Hmin = Hmin;
		this->histogram = histogram;
		this->color = cv::Scalar(255, 0, 0);
		this->erode = 7;
		this->dilate = 1;
		this->blur = 2;
		bool Is_drawing_Pencil_active = false;
		bool Is_drawing_rectangle_active = false;
		bool Is_drawing_circle_active = false;
		bool Is_drawing_line_active = false;
	}
	void setMat_backproj(cv::Mat mat_backproj) { this->mat_backproj = mat_backproj; }
	cv::Mat getMat_backproj() { return this->mat_backproj; }
	void setErode(int erode) { this->erode = erode; }
	int getErode() { return this->erode; }
	void setDilate(int dilate) { this->dilate = dilate; }
	int getDilate() { return this->dilate; }
	void setTracking_Points(Drawing_Position Tracking_Points) { this->Tracking_Points = Tracking_Points; }
	Drawing_Position getTracking_Points() { return this->Tracking_Points; }
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
	void setColor(cv::Scalar color) { this->color = color; }
	cv::Scalar getColor() { return this->color; }
	void setIs_drawing_Pencil_active(bool Is_drawing_Pencil_active) { this->Is_drawing_Pencil_active = Is_drawing_Pencil_active; }
	bool getIs_drawing_Pencil_active() { return this->Is_drawing_Pencil_active; }
	void setIs_drawing_rectangle_active(bool Is_drawing_rectangle_active) { this->Is_drawing_rectangle_active = Is_drawing_rectangle_active; }
	bool getIs_drawing_rectangle_active() { return this->Is_drawing_rectangle_active; }
	void setIs_drawing_circle_active(bool Is_drawing_circle_active) { this->Is_drawing_circle_active = Is_drawing_circle_active; }
	bool getIs_drawing_circle_active() { return this->Is_drawing_circle_active; }
	void setIs_drawing_line_active(bool Is_drawing_line_active) { this->Is_drawing_line_active = Is_drawing_line_active; }
	bool getIs_drawing_line_active() { return this->Is_drawing_line_active; }
	void setLine_thickness(int line_thickness) { this->line_thickness = line_thickness; }
	int getLine_thickness() { return this->line_thickness; }



private:

	cv::Mat histogram;
	cv::RotatedRect rectangle_tracked;
	Drawing_Position Tracking_Points;
	cv::Scalar color;
	bool Is_drawing_Pencil_active = false;
	bool Is_drawing_rectangle_active = false;
	bool Is_drawing_circle_active = false;
	bool Is_drawing_line_active = false;
	int line_thickness = 1;
};
