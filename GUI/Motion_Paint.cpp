#include "MyForm.h"

using namespace GUI;
using namespace System::Windows::Forms;
using namespace std;
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <iostream>
#include <string>
//INIT
//INIT2
//using namespace cv;
using namespace std;
#pragma region Pozycja_struktura
#pragma endregion 

class Motion_Paint
{
public:
 static const cv::VideoCapture capture;
};
const cv::VideoCapture Motion_Paint::capture = cv::VideoCapture("Video.mp4");

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());
	return 0;
}