#pragma once

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>
cv::VideoCapture capture;
cv::Mat mat_frame;
cv::Mat mat_img;
cv::Mat mat_rectangle;
std::vector<cv::Mat> mat_img_split;
#pragma region Trackbar parametry (Trackbar_*)
int Trackbar_H_MIN = 0;
int Trackbar_H_MAX = 0;
double Trackbar_H_MIN_RANGE = 0;
double Trackbar_H_MAX_RANGE = 93;
int Trackbar_BLUR = 2;
int Trackbar_DILATE = 3;
int Trackbar_ERODE = 2;
int Trackbar_Circle_diameter = 2;//zmienne
#pragma endregion
#pragma region bool parametres (Is_)
bool Is_Original_active = false;
bool Is_HSV_active = false;
bool Is_Drawing_active = false;
bool Is_Drawing_area_being_selected = false;
bool Is_Drawing_area_selected = false;
bool Is_Tracking_active = false;
bool Is_backprojMode = false;
bool Is_Contour_active = false;
#pragma endregion 
#pragma region Drawing and seelecting area  (Area_*)


cv::Rect Area_Rectangular;
cv::Point Area_Point_begin;
cv::Point Area_Point_end;



#pragma endregion%
cv::Point2i pt(-1, -1);
int Drawing_line_Color_Value = 0;



#pragma temporary variables
int mouseX, mouseY;
#pragma endregion

struct Position
{
	cv::Point2i point = cv::Point2i(0, 0);
	int r = 0;

	Position()
	{
		this->point = cv::Point2i(0, 0);
		this->r = 0;
	}
	Position(cv::Point2i point, int r)
	{
		this->point = point;
		this->r = r;
	}
}pozycja;
namespace GUI {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::PictureBox^  Image_Original;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Timer^  Timer_Capture;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;

	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->Image_Original = (gcnew System::Windows::Forms::PictureBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->Timer_Capture = (gcnew System::Windows::Forms::Timer(this->components));
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Image_Original))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(-2, 41);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(109, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"HSV";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::Button_Show_HSV);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(-2, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(109, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Capture start";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::Button_Video_Start);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(-2, 202);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(109, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Capture stop";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::Button_Video_Stop);
			// 
			// Image_Original
			// 
			this->Image_Original->Location = System::Drawing::Point(113, 8);
			this->Image_Original->Name = L"Image_Original";
			this->Image_Original->Size = System::Drawing::Size(1274, 592);
			this->Image_Original->TabIndex = 3;
			this->Image_Original->TabStop = false;
			
			this->Image_Original->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Down_Image_Original);
			this->Image_Original->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Up_Image_Original);
			// 
			// Timer_Capture
			// 
			this->Timer_Capture->Interval = 30;
			this->Timer_Capture->Tick += gcnew System::EventHandler(this, &MyForm::Timer_motion);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(-2, 71);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(109, 23);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Original";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::Button_Show_Original);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(-2, 101);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(109, 23);
			this->button5->TabIndex = 5;
			this->button5->Text = L"Contour";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::Button_Show_Contour);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1399, 612);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->Image_Original);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Image_Original))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
#pragma region Trackbary (Trackbars_Create)
		void on_trackbar(int, void*)
		{//This function gets called whenever a
		 // trackbar position is changed
		}
		void Trackbars_Create()
		{
			cv::namedWindow("Trackbars", 0);
			cv::createTrackbar("Thresh lb", "Trackbars", &Trackbar_H_MIN, 360, NULL);
			cv::createTrackbar("Thresh ub", "Trackbars", &Trackbar_H_MAX, 360, NULL);
			//cv::createTrackbar("Diameter scale", "Trackbars", &diameterScale, 10, 0);
			cv::createTrackbar("Dilate", "Trackbars", &Trackbar_DILATE, 15, NULL);
			cv::createTrackbar("Erode", "Trackbars", &Trackbar_ERODE, 15, NULL);
			//cv::createTrackbar("Line color", "Trackbars", &lineColorValue, 4, NULL);
		}
#pragma endregion
#pragma region Funkcje rysujace (Drawing_*)
		int Drawing_Radius_get(int x, int y)
		{
			if (x < y)
			{
				return x / 2;
			}
			else
			{
				return y / 2;
			}
		}
		bool Drawing_Radius_move(Position actualposition, int movestabilize, int Radiustabilize)
		{
			bool stabilize = false;
			if (abs(actualposition.point.x - pozycja.point.x) > movestabilize)
			{
				pozycja.point.x = actualposition.point.x;
				stabilize = true;
			}
			if (abs(actualposition.point.y - pozycja.point.y) > movestabilize)
			{
				pozycja.point.y = actualposition.point.y;
				stabilize = true;
			}
			if (abs(actualposition.r - pozycja.r) > Radiustabilize)
			{
				pozycja.r = actualposition.r;
				stabilize = true;
			}
			return stabilize;
		}
		cv::Scalar Drawing_line_Color()
		{
			switch (Drawing_line_Color_Value)
			{
			case 0:
				return cv::Scalar(0, 0, 0);

			case 1:
				return cv::Scalar(255, 255, 255);

			case 2:
				return cv::Scalar(255, 0, 0);

			case 3:
				return cv::Scalar(0, 255, 0);

			case 4:
				return cv::Scalar(0, 0, 255);

			default:
				return cv::Scalar(255, 255, 255);
				break;
			}
		}
		void Drawing_circle(cv::InputOutputArray img, cv::Point center, int radius, const cv::Scalar& color)
		{
			if (Is_Drawing_active)
			{
				if (Trackbar_Circle_diameter == 0)
				{
					Trackbar_Circle_diameter = 1;
				}
				circle(img, center, radius / Trackbar_Circle_diameter, color, -1, cv::LINE_AA);
			}
		}
		void Drawing_line(cv::InputOutputArray img, Position poczatkowa, Position koncowa, const cv::Scalar& color)
		{
			if (Is_Drawing_active)
			{
				if (Trackbar_Circle_diameter <= 0)
				{
					Trackbar_Circle_diameter = 1;
				}
				line(img, poczatkowa.point, koncowa.point, color, koncowa.r / Trackbar_Circle_diameter);
			}
		}	
#pragma endregion
#pragma region Image processing functions (Operation_*) :::Operacje morfologiczne i DrawCVOmage
		void Operation_DrawCVImage(System::Windows::Forms::Control^ control, cv::Mat& colorImage)
		{
			System::Drawing::Graphics^ graphics = control->CreateGraphics();
			System::IntPtr ptr(colorImage.ptr());
			System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(colorImage.cols, colorImage.rows, colorImage.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
			System::Drawing::RectangleF rect(0, 0, control->Width, control->Height);
			graphics->DrawImage(b, rect);
			delete graphics;
		}
		void Operation_Deactivate()
		{
			Is_HSV_active = false;
			Is_Original_active = false;
			Is_Contour_active = false;
			Is_Drawing_area_being_selected = false;
		}
		void Operation_filter_Blur(cv::Mat &thresh) {
			if (Trackbar_BLUR < 1)
			{
				Trackbar_BLUR = 1;
			}
			blur(thresh, thresh, cv::Size(Trackbar_BLUR, Trackbar_BLUR));
		}

		void Operation_filter_Erode(cv::Mat &thresh) {
			if (Trackbar_ERODE < 1)
			{
				Trackbar_ERODE = 1;
			}
			cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(Trackbar_ERODE, Trackbar_ERODE));

			erode(thresh, thresh, erodeElement);
		}

		void Operation_filter_Dilate(cv::Mat &thresh) {
			if (Trackbar_DILATE < 1)
			{
				Trackbar_DILATE = 1;
			}
			cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(Trackbar_DILATE, Trackbar_DILATE));

			dilate(thresh, thresh, dilateElement);
		}

		void Operation_filter(cv::Mat &thresh) {

			Operation_filter_Dilate(thresh);

			Operation_filter_Erode(thresh);
		}

#pragma endregion
#pragma region mouse actions (Mouse_)
private: System::Void Mouse_Down_Image_Original(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	std::cout << "Mouse_Down";
	/*this->Cursor = new Cursor(Cursor->Current.Handle);

	int xCoordinate = Cursor.Position.X;
	int yCoordinate = Cursor.Position.Y;*/
	//Operation_Deactivate();
	mouseX = e->X;
	mouseY = e->Y;
	Is_Drawing_area_being_selected = true;
	Image_Original->Refresh();
	//Timer_Capture->Start();
}
private: System::Void Mouse_Up_Image_Original(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	std::cout << "Mouse_Up";
	Is_Drawing_area_being_selected = false;
	if(Is_Original_active==true)Trackbars_Create();
	Is_Drawing_area_being_selected = false;
	Is_Drawing_area_selected = true;
	Area_Point_end.x = Image_Original->Cursor->Position.X;
	Area_Point_end.y = Image_Original->Cursor->Position.Y;
}
#pragma endregion
#pragma region Button actions (Button_*)
//approved
private: System::Void Button_Video_Start(System::Object^  sender, System::EventArgs^  e) 
{
	//Trackbars_Create();
	Operation_Deactivate();
//	cv::setMouseCallback(window_name[0], Mouse_Action, (void *)&pt);
	capture = cv::VideoCapture(0);
	Image_Original->Show();
	Timer_Capture->Start();
}
//approved
private: System::Void Button_Video_Stop(System::Object^  sender, System::EventArgs^  e) 
{
	Timer_Capture->Stop();
	capture.release();
	Image_Original->Hide();
}//Implemented
//approved
private: System::Void Button_Show_Contour(System::Object^  sender, System::EventArgs^  e)
{
	if (Is_Contour_active == false)
	{
		Operation_Deactivate();
		Is_Contour_active = true;
	}
}
//approved
private: System::Void Button_Show_HSV(System::Object^  sender, System::EventArgs^  e)
{
	if (Is_HSV_active == false)
	{
		Operation_Deactivate();
		Is_HSV_active = true;
		//if (capture.isOpened() == true)std::cout << "Opened";	
	}
}
//approved
 private: System::Void Button_Show_Original(System::Object^  sender, System::EventArgs^  e)
 {
	 if (Is_Original_active == false)
	 {
		 Operation_Deactivate();
		 Is_Original_active = true;

	 }
 }
#pragma endregion 
#pragma region Real time capture(Timer_motion)
private: System::Void Timer_motion(System::Object^  sender, System::EventArgs^  e) 
{
	
	capture >> mat_frame;
	flip(mat_frame, mat_frame, 1);
	mat_frame.copyTo(mat_img);
	if (Is_Original_active)
	{
		if (Is_Drawing_area_being_selected)
		{
			std::cout << "Mouse_Down\n";
			
	
			//Area_Rectangular = cv::Rect(Image_Original->Cursor->Position.X, Image_Original->Cursor->Position.Y,0,0);
			//Operation_DrawCVImage(Image_Original, mat_img);
			//std::cout << Image_Original->Cursor->Position.X;
		}
		if (Is_Drawing_area_selected &&Is_Drawing_area_being_selected==false)
		{

			//std::cout << "Drawing area selected";
			std::cout << "X" << Image_Original->Cursor->Position.X << "\n";
			std::cout << "Y" << Image_Original->Cursor->Position.Y << "\n";
			cv::Rect Rec(100, 100, 50, 50);
			rectangle(mat_img, Rec, cv::Scalar(255), 1, 8, 0);
			cv::Mat Roi = mat_img(Rec);
			cv::Rect WhereRec(100, 100, Roi.cols, Roi.rows);
			Roi.copyTo(mat_img(WhereRec));
			//cv::setMouseCallback(mat_img, CallBackFunc, NULL);
			//cv::Mat roi(mat_img, selection);
			//bitwise_not(roi, roi);
			/*Area_Rectangular.x = MIN(x, Area_Point_begin.x);
			Area_Rectangular.y = MIN(y, Area_Point_begin.y);
			Area_Rectangular.width = std::abs(x - Area_Point_begin.x);
			Area_Rectangular.height = std::abs(y - Area_Point_begin.y);*/
		}
		Operation_DrawCVImage(Image_Original, mat_img);
	}
	if (Is_HSV_active)
	{

		cv::cvtColor(mat_img, mat_img, cv::COLOR_BGR2HSV);
		Operation_DrawCVImage(Image_Original, mat_img);

	}
	if (Is_Contour_active)
	{
		
		cv::cvtColor(mat_img, mat_img, cv::COLOR_BGR2HSV);
		split(mat_img, mat_img_split);
		cv::inRange(mat_img_split[0],Trackbar_H_MIN, Trackbar_H_MAX, mat_img);
		int ch[] = { 0, 0 };
		cv::mixChannels(&mat_img, 1, &mat_img_split[0], 1, ch, 1);
		Operation_filter(mat_img);
		Operation_DrawCVImage(Image_Original, mat_img);

	}
	else Operation_DrawCVImage(Image_Original, mat_img);
	
}
#pragma endregion


};
}