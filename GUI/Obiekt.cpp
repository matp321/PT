#include <iostream>
//cv::Mat kontur(kontur.rows, kontur.cols, CV_8UC3, cv::Scalar(255, 255, 255));
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>


class Obiekt
{
public:
	 //void setX(System::Int32 X)
	 //{
		// this->X = X;
	 //}
	 //void setY(System::Int32 Y)
	 //{
		// this->Y = Y;
	 //}
	 //System::Int32 getX()
	 //{
		// return this->X;
	 //}
	 //System::Int32 getY()
	 //{
		// return this->Y;
	 //}
	Obiekt(cv::Point p1,cv::Rect rectangle)
	{
		this->rectangle = rectangle;
		this->p1 = p1;

	}
	int getHmin()
	 {
		return this->Hmin;
	 }
	void setHmin(int Hmin)
	{
		this->Hmin = Hmin;

	}
	int getHmax()
	{
		return this->Hmax;
	}
	void setHmax(int Hmax)
	{
		this->Hmax = Hmax;

	}
	//Obiekt()
	cv::Point getp1()
	{
		return this->p1;
	}
	void setp1(cv::Point p1)
	{
		this->p1 = p1;
	}
	//Area_Rectangular_selected.x = MIN(X, obiekt.at(temp - 1).getp1().x);
	//Area_Rectangular_selected.y = MIN(Y, obiekt.at(temp-1).getp1().y);
	//Area_Rectangular_selected.width = std::abs(X - obiekt.at(temp - 1).getp1().x);
	//Area_Rectangular_selected.height = std::abs(Y - obiekt.at(temp - 1).getp1().y);
	cv::Rect getRectangle()
	{		
		return this->rectangle;
	}
	void setRectangle(cv::Rect rectangle)
	{
		this->rectangle = rectangle;
	}
	
private:
	//System::Int32 X,Y;
	cv::Rect rectangle;
	int Hmin, Hmax;
	cv::Point p1;
	//cv::Point p2;
};
