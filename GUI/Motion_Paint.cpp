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
	static void Mouse_Action(int event, int x, int y, int flags, void*)
	{

		if (Is_Drawing_area_being_selected == true)  //Zostaje pobrany obszar ktory zaznaczylismy myszka
		{
			//cout << "IsAreaSelected: " << IsAreaSelected << "\n";
			Area_Rectangular.x = MIN(x, Area_Point_begin.x);
			Area_Rectangular.y = MIN(y, Area_Point_begin.y);
			Area_Rectangular.width = std::abs(x - Area_Point_begin.x);
			Area_Rectangular.height = std::abs(y - Area_Point_begin.y);
			Area_Rectangular &= cv::Rect(0, 0, mat_img.cols, mat_img.rows);//tworzenie prostokata

																		   //cout << "Rectangular_selected_area values: " << Rectangular_selected_area.x << "\n";
																		   //cout << "Rectangular_selected_area values: " << Rectangular_selected_area.y << "\n";
																		   //cout << "Rectangular_selected_area values: " << Rectangular_selected_area.width << "\n";
																		   //cout << "Rectangular_selected_area values: " << Rectangular_selected_area.height << "\n";
		}
		switch (event)
		{
		case cv::EVENT_LBUTTONDOWN:///zainicjowane po nacisnieciu przycisku myszki
								   //cout << "Test myszki LButtonDOWN" << "\n";//Event na klikniecie myszki jest wywolywany prawidlowo
			Area_Point_begin = cv::Point(x, y);
			Area_Rectangular = cv::Rect(x, y, 0, 0);
			Is_Drawing_area_being_selected = true;
			cout << "Event_L_Buttondown";
			break;
		case cv::EVENT_LBUTTONUP:////zainicjowane po puszczeniu przycisku myszki
								 //cout << "Test myszki LButtonUP" << "\n";
			Is_Drawing_area_being_selected = false;
			//TODO zainicjowanie aktywacji tego if
			if (Area_Rectangular.width > 0 && Area_Rectangular.height > 0) 
			{
				//cout << "Selected area width=" << Rectangular_selected_area.width << "\n";
				//cout << "Selected area height=" << Rectangular_selected_area.height << "\n";
				Is_Drawing_area_selected = true;
			}
			break;
		}
		//endregion
	}

};

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());
	return 0;
}