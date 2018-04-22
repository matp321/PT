#include <iostream>
//cv::Mat kontur(kontur.rows, kontur.cols, CV_8UC3, cv::Scalar(255, 255, 255));
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>


class Obiekt
{
public:
	 void setX(System::Int32 X)
	 {
		 this->X = X;
	 }
	 void setY(System::Int32 Y)
	 {
		 this->Y = Y;
	 }
	 System::Int32 getX()
	 {
		 return this->X;
	 }
	 System::Int32 getY()
	 {
		 return this->Y;
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
private:
	System::Int32 X,Y;
	int Hmin, Hmax;
};
