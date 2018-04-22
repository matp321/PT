#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>
class Obiekt
{
public:
	Obiekt();
	~Obiekt();
private:
	cv::Mat kontur;
	int H_MIN;
	int H_MAX;
	int X;
	int Y;
};
Obiekt::Obiekt()
{
	cv::Mat kontur(kontur.rows, kontur.cols, CV_8UC3, cv::Scalar(255, 255, 255));
	H_MIN = 0;
	H_MAX = 0;
	int X = 0;
	int Y = 0;
}
Obiekt::~Obiekt()
{
}