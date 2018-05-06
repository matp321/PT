#pragma once

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>
#include "Obiekt.cpp"




Drawing_Position position;
Drawing_Position *Tracking_points;
int counter = 0;
cv::VideoCapture capture;
cv::Mat mat_frame;
cv::Mat mat_img;
cv::Mat mat_roi;
cv::Mat mat_mask_roi;
cv::Mat mat_hsv;
cv::Mat mat_contour;
cv::Mat mat_histogram;
cv::Mat mat_backproj;
cv::Mat mat_card;
cv::Mat mat_card_table[3];
cv::Mat mat_temp;
cv::Mat mat_roi_H;
cv::Mat mat_roi_Contour;
std::vector<cv::Mat> mat_hsv_split;
cv::Mat mat_histogram_picture = cv::Mat::zeros(200, 320, CV_8UC3);
int histogram_Size = 16;
float histogram_Zasieg[] = { 0, 180 };
const float *histogram_pointer_Zasieg = histogram_Zasieg;
std::vector<cv::Point2i>Drawing_points;
std::vector<Obiekt>obiekt;
int temp;

int j = 0;
std::string window_histogram[] = {"Histogram1", "Histogram2","Histogram3","Histogram4"};
std::string window_contour[] = {"Contour1", "Contour2","Contour3","Contour4"};
std::string window_contour_roi[] = { "Contour_roi_1", "Contour_roi_2","Contour_roi_3","Contour_roi_4" };
std::string window_calback_proj[] = { "Callback_1", "Callback_2","Callback_3","Callback_4" };
std::string window_card[] = { "card1", "card2","card3","card4" };

double h_min_range = 0;
double h_max_range = 360;


cv::String names[] = { "1","2","3","4","5"};
const cv::String *names_pointer = names;



#pragma region Trackbar parametry
int Trackbars_parametr_H_MIN = 0;
int Trackbars_parametr_H_MAX = 360;
//double h_min_range = 0;
//double h_max_range = 93;
int Trackbars_parametr_BLUR = 2;
int Trackbars_parametr_DILATE = 3;
int Trackbars_parametr_ERODE = 2;
int Trackbars_parametr_diameterScale = 2;//zmienne
#pragma endregion

#pragma region bool parametres
bool Is_Painting_active = false;
bool Is_Contour_active = false;
bool Is_Original_active = false;
bool Is_HSV_active = false;
bool Is_Drawing_active = false;
bool Is_Drawing_area_being_selected = false;
bool Is_Drawing_area_selected = false;
int Is_Tracking_active = 0;
bool Is_backprojMode = false;
bool Is_start_active = false;
bool Is_pause_active = false;
#pragma endregion 

#pragma region Drawing and seelecting area
cv::Rect Area_Rectangular_selected;

cv::Point Area_Point_begin;
cv::Point Area_Point_end;
int Drawing_line_Color_Value = 0;
cv::Point2i pt(-1, -1);
#pragma endregion%

#pragma region stale
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

#pragma endregion


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
	private: System::Windows::Forms::Button^  button_start;
	protected:


	private: System::Windows::Forms::PictureBox^  Image_Original;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Timer^  Timer_Capture;

	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button_drawing;
	private: System::Windows::Forms::NumericUpDown^  numeric_Objects_Detect;
	private: System::Windows::Forms::Label^  Text_Number_of_Objects;
	private: System::Windows::Forms::Button^  button_pauses;
	private: System::Windows::Forms::Timer^  Timer_Capture_pause;
	private: System::Windows::Forms::Button^  button_clear;
	private: System::Windows::Forms::Button^  button_reset;



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
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->Image_Original = (gcnew System::Windows::Forms::PictureBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->Timer_Capture = (gcnew System::Windows::Forms::Timer(this->components));
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button_drawing = (gcnew System::Windows::Forms::Button());
			this->numeric_Objects_Detect = (gcnew System::Windows::Forms::NumericUpDown());
			this->Text_Number_of_Objects = (gcnew System::Windows::Forms::Label());
			this->button_pauses = (gcnew System::Windows::Forms::Button());
			this->Timer_Capture_pause = (gcnew System::Windows::Forms::Timer(this->components));
			this->button_clear = (gcnew System::Windows::Forms::Button());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Image_Original))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_Objects_Detect))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(-2, 368);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(109, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"HSV";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::Button_Show_HSV);
			// 
			// button_start
			// 
			this->button_start->Location = System::Drawing::Point(-2, 13);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(109, 23);
			this->button_start->TabIndex = 1;
			this->button_start->Text = L"START";
			this->button_start->UseVisualStyleBackColor = true;
			this->button_start->Click += gcnew System::EventHandler(this, &MyForm::Button_Video_Start);
			// 
			// Image_Original
			// 
			this->Image_Original->Location = System::Drawing::Point(113, 8);
			this->Image_Original->Name = L"Image_Original";
			this->Image_Original->Size = System::Drawing::Size(640, 480);
			this->Image_Original->TabIndex = 3;
			this->Image_Original->TabStop = false;
			this->Image_Original->Click += gcnew System::EventHandler(this, &MyForm::Image_Original_Click);
			this->Image_Original->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Down_Image_Original);
			this->Image_Original->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Up_Image_Original);
			// 
			// Timer_Capture
			// 
			this->Timer_Capture->Interval = 30;
			this->Timer_Capture->Tick += gcnew System::EventHandler(this, &MyForm::Timer_motion);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(-2, 397);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(109, 23);
			this->button5->TabIndex = 5;
			this->button5->Text = L"Contour";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::Button_Show_Contour);
			// 
			// button_drawing
			// 
			this->button_drawing->Enabled = false;
			this->button_drawing->Location = System::Drawing::Point(-2, 71);
			this->button_drawing->Name = L"button_drawing";
			this->button_drawing->Size = System::Drawing::Size(109, 23);
			this->button_drawing->TabIndex = 6;
			this->button_drawing->Text = L"Start drawing";
			this->button_drawing->UseVisualStyleBackColor = true;
			this->button_drawing->Click += gcnew System::EventHandler(this, &MyForm::Button_Drawing_Start_Stop);
			// 
			// numeric_Objects_Detect
			// 
			this->numeric_Objects_Detect->Location = System::Drawing::Point(-2, 242);
			this->numeric_Objects_Detect->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numeric_Objects_Detect->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numeric_Objects_Detect->Name = L"numeric_Objects_Detect";
			this->numeric_Objects_Detect->Size = System::Drawing::Size(109, 20);
			this->numeric_Objects_Detect->TabIndex = 7;
			this->numeric_Objects_Detect->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// Text_Number_of_Objects
			// 
			this->Text_Number_of_Objects->AutoSize = true;
			this->Text_Number_of_Objects->Location = System::Drawing::Point(-5, 226);
			this->Text_Number_of_Objects->Name = L"Text_Number_of_Objects";
			this->Text_Number_of_Objects->Size = System::Drawing::Size(102, 13);
			this->Text_Number_of_Objects->TabIndex = 8;
			this->Text_Number_of_Objects->Tag = L"Number of objects being detected";
			this->Text_Number_of_Objects->Text = L"   Number of objects";
			// 
			// button_pauses
			// 
			this->button_pauses->Enabled = false;
			this->button_pauses->Location = System::Drawing::Point(-2, 42);
			this->button_pauses->Name = L"button_pauses";
			this->button_pauses->Size = System::Drawing::Size(109, 23);
			this->button_pauses->TabIndex = 9;
			this->button_pauses->Text = L"PAUSE";
			this->button_pauses->UseVisualStyleBackColor = true;
			this->button_pauses->Click += gcnew System::EventHandler(this, &MyForm::Button_Pause);
			// 
			// Timer_Capture_pause
			// 
			this->Timer_Capture_pause->Tick += gcnew System::EventHandler(this, &MyForm::Timer_motion_pause);
			// 
			// button_clear
			// 
			this->button_clear->Location = System::Drawing::Point(-2, 100);
			this->button_clear->Name = L"button_clear";
			this->button_clear->Size = System::Drawing::Size(109, 23);
			this->button_clear->TabIndex = 10;
			this->button_clear->Text = L"Clear";
			this->button_clear->UseVisualStyleBackColor = true;
			this->button_clear->Click += gcnew System::EventHandler(this, &MyForm::Button_Clear_Card);
			// 
			// button_reset
			// 
			this->button_reset->Location = System::Drawing::Point(-2, 130);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(109, 23);
			this->button_reset->TabIndex = 11;
			this->button_reset->Text = L"RESET";
			this->button_reset->UseVisualStyleBackColor = true;
			this->button_reset->Click += gcnew System::EventHandler(this, &MyForm::Button_Reset);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(767, 493);
			this->Controls->Add(this->button_reset);
			this->Controls->Add(this->button_clear);
			this->Controls->Add(this->button_pauses);
			this->Controls->Add(this->Text_Number_of_Objects);
			this->Controls->Add(this->numeric_Objects_Detect);
			this->Controls->Add(this->button_drawing);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->Image_Original);
			this->Controls->Add(this->button_start);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Image_Original))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_Objects_Detect))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

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
			cv::createTrackbar("Thresh lb", "Trackbars", &Trackbars_parametr_H_MIN, 360, NULL);
			cv::createTrackbar("Thresh ub", "Trackbars", &Trackbars_parametr_H_MAX, 360, NULL);
			//cv::createTrackbar("Diameter scale", "Trackbars", &diameterScale, 10, 0);
			cv::createTrackbar("Dilate", "Trackbars", &Trackbars_parametr_DILATE, 15, NULL);
			cv::createTrackbar("Erode", "Trackbars", &Trackbars_parametr_ERODE, 15, NULL);
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
		bool Drawing_Radius_move(Drawing_Position actualposition, int movestabilize, int Radiustabilize)
		{
			bool stabilize = false;
			if (abs(actualposition.point.x - position.point.x) > movestabilize)
			{
				position.point.x = actualposition.point.x;
				stabilize = true;
			}
			if (abs(actualposition.point.y - position.point.y) > movestabilize)
			{
				position.point.y = actualposition.point.y;
				stabilize = true;
			}
			if (abs(actualposition.r - position.r) > Radiustabilize)
			{
				position.r = actualposition.r;
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
				if (Trackbars_parametr_diameterScale == 0)
				{
					Trackbars_parametr_diameterScale = 1;
				}
				circle(img, center, radius / Trackbars_parametr_diameterScale, color, -1, cv::LINE_AA);
			}
		}

		void Drawing_line(cv::InputOutputArray img, Drawing_Position start, Drawing_Position end, const cv::Scalar& color)
		{
			if (Is_Drawing_active)
			{
				if (Trackbars_parametr_diameterScale <= 0)
				{
					Trackbars_parametr_diameterScale = 1;
				}
				line(img, start.point, end.point, color, end.r / Trackbars_parametr_diameterScale);
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
			Is_Drawing_active = false;
			Is_Drawing_area_being_selected = false;
			Is_Tracking_active = false;
			Is_HSV_active = false;
			//Is_Original_active = false;
			Is_Contour_active = false;
		}
		void Operation_filter_Blur(cv::Mat &thresh) {
			if (Trackbars_parametr_BLUR < 1)
			{
				Trackbars_parametr_BLUR = 1;
			}
			blur(thresh, thresh, cv::Size(Trackbars_parametr_BLUR, Trackbars_parametr_BLUR));
		}

		void Operation_filter_Erode(cv::Mat &thresh) {
			if (Trackbars_parametr_ERODE < 1)
			{
				Trackbars_parametr_ERODE = 1;
			}
			cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(Trackbars_parametr_ERODE, Trackbars_parametr_ERODE));

			erode(thresh, thresh, erodeElement);
		}

		void Operation_filter_Dilate(cv::Mat &thresh) {
			if (Trackbars_parametr_DILATE < 1)
			{
				Trackbars_parametr_DILATE = 1;
			}
			cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(Trackbars_parametr_DILATE, Trackbars_parametr_DILATE));

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
		Point P = PointToScreen(Point(Image_Original->Bounds.Left, Image_Original->Bounds.Top));
		Int32 X = Cursor->Position.X - P.X;
		Int32 Y = Cursor->Position.Y - P.Y;
		std::cout << "Mouse_Down_EVENT";
		Operation_Deactivate();
		Is_Tracking_active = true;
		Area_Point_begin = cv::Point(X, Y);
		Is_Drawing_area_being_selected = true;

		//Is_Original_active = true;
		//Timer_Capture->Start();
	}
	private: System::Void Mouse_Up_Image_Original(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		
		std::cout << "Mouse_Up";
		Is_Drawing_area_being_selected = false;
		//if (Is_Original_active == true)
		Operation_Deactivate();
		Is_Tracking_active = true;
		Is_Original_active = true;
		//Is_Tracking_active = -1;
		if (Is_pause_active)
		{
			Operation_DrawCVImage(Image_Original, mat_img);
		}
		if (Area_Rectangular_selected.width > 0 && Area_Rectangular_selected.height > 0)
		{
			temp--;
			Is_Drawing_area_being_selected = false;
			Is_Tracking_active = -1;
			button_drawing->Enabled = true;
			Is_Drawing_active = false;	
			std::cout << "Mouse check";
		}
	}
#pragma endregion
#pragma region Button actions (Button_*)
	private: System::Void Button_Reset(System::Object^  sender, System::EventArgs^  e) 
		{
		std::cout << "CHeck";
		temp = (int)numeric_Objects_Detect->Value;
		Operation_Deactivate();
		Image_Original->Enabled = true;
		obiekt.clear();
	}
	private: System::Void Button_Clear_Card(System::Object^  sender, System::EventArgs^  e)
	{
		mat_card = cv::Mat(mat_frame.rows, mat_frame.cols, CV_8UC3, cv::Scalar(255, 255, 255));
	}
	private: System::Void Button_Pause(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_pause_active == true)///wznowienie wideo
		{
			Is_pause_active = false;
			button_pauses->Text = "PAUSE";
			//Timer_Capture_pause->Stop();
			//Timer_Capture->Start();
			//Timer_Capture->
			return;
		}
		if (Is_pause_active == false)//zatrzymanie wideo
		{
			Is_pause_active = true;
			//Operation_Deactivate();
			
			//Timer_Capture->Stop();
			//Timer_Capture_pause->Start();
			cv::imshow("CONTOUR", mat_img);
			button_pauses->Text = "RESUME";
			return;
		}
	}
	private: System::Void Button_Video_Start(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_start_active == false)
		{
			Image_Original->Enabled = true;
			button_pauses->Enabled = true;
			temp = (int)numeric_Objects_Detect->Value;
			Operation_Deactivate();
			Is_Original_active = true;
			button_start->Text = "STOP";
			Is_start_active = true;
			capture.release();
			capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
			capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
			Operation_Deactivate();
		    capture = cv::VideoCapture("MyVideo_2.mp4");
			//capture = cv::VideoCapture(0);
			Image_Original->Show();	
			obiekt.clear();
			Timer_Capture->Start();
		
			return;
		}
		if (Is_start_active == true)
		{
			obiekt.clear();
			button_pauses->Enabled = false;
			Is_Original_active = false;
			Image_Original->Hide();
			Is_start_active = false;
			button_start->Text = "START";
			Timer_Capture->Stop();
			capture.release();
			return;
		}
	}
	private: System::Void Button_Show_Contour(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_Contour_active == true)
		{
			Operation_Deactivate();
			return;
			//if (capture.isOpened() == true)std::cout << "Opened";	
		}
		if (Is_Contour_active == false)
		{
			Operation_Deactivate();
			Is_Contour_active = true;
			return;
			//if (capture.isOpened() == true)std::cout << "Opened";	
		}
	}
	private: System::Void Button_Show_HSV(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_HSV_active == true)
		{
			Operation_Deactivate();
			return;
			//if (capture.isOpened() == true)std::cout << "Opened";	
		}
		if (Is_HSV_active == false)
		{
			Operation_Deactivate();
			Is_HSV_active = true;
			return;
			//if (capture.isOpened() == true)std::cout << "Opened";	
		}
	}
	private: System::Void Button_Drawing_Start_Stop(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_Drawing_active) {
			Is_Drawing_active = false; button_drawing->Text = "Start drawing"; return;
		}

		if (Is_Drawing_active == false) {
			std::cout << "Drawing_is active";
			Is_Drawing_active = true;
			button_drawing->Text = "Stop drawing"; return;
		}

	}
#pragma endregion 
#pragma region Real time capture(Timer_motion)
	private: System::Void Timer_motion(System::Object^  sender, System::EventArgs^  e)
	{
		Trackbars_Create();
		Point P = PointToScreen(Point(Image_Original->Bounds.Left, Image_Original->Bounds.Top));
		Int32 X = Cursor->Position.X - P.X;
		Int32 Y = Cursor->Position.Y - P.Y;
		//cv::namedWindow("CARD", cv::WINDOW_AUTOSIZE);
		//cv::namedWindow("BACKPROJ", cv::WINDOW_AUTOSIZE);
		capture >> mat_frame;
		flip(mat_frame, mat_frame, 1);
		mat_frame.copyTo(mat_img);
		//cv::imshow("HISTOGRAM", mat_frame);
		if (Is_Original_active)
		{
			cv::cvtColor(mat_img, mat_hsv, cv::COLOR_BGR2HSV);
			cv::split(mat_hsv, mat_hsv_split);
			int ch[] = { 0, 0 };
			cv::mixChannels(&mat_hsv, 1, &mat_hsv_split[0], 1, ch, 1);	
			if (Is_Drawing_area_being_selected)
			{
				Area_Rectangular_selected.x = MIN(X, Area_Point_begin.x);
				Area_Rectangular_selected.y = MIN(Y, Area_Point_begin.y);
				Area_Rectangular_selected.width = std::abs(X - Area_Point_begin.x);
				Area_Rectangular_selected.height = std::abs(Y - Area_Point_begin.y);
				cv::rectangle(mat_img, Area_Rectangular_selected, cv::Scalar(128), 1, 8, 0);
				Area_Rectangular_selected &= cv::Rect(0, 0, mat_img.cols, mat_img.rows);//tworzenie prostokata
			}
			if (temp == 0)Image_Original->Enabled = false;
			if (Is_Tracking_active)
			{
				if (Is_Tracking_active < 0)
				{
					cv::Mat mat_contour_temp;
					cv::Mat mat_histogram;
					cv::Mat mat_roi_H = cv::Mat(mat_hsv_split[0], Area_Rectangular_selected);
					cv::minMaxLoc(mat_roi_H, &h_min_range, &h_max_range, nullptr, nullptr);
					cv::inRange(mat_hsv_split[0], h_min_range, h_max_range, mat_contour_temp);
					cv::Mat mat_roi_Contour = cv::Mat(mat_contour_temp, Area_Rectangular_selected);
					calcHist(&mat_roi_H, 1, 0, mat_roi_Contour, mat_histogram, 1, &histogram_Size, &histogram_pointer_Zasieg);
					cv::normalize(mat_histogram, mat_histogram, 0, 255, cv::NORM_MINMAX);
					Is_Tracking_active = 1;
					mat_histogram_picture = cv::Scalar::all(0);
					int binW = mat_histogram_picture.cols / histogram_Size;
					cv::Mat buffor(1, histogram_Size, CV_8UC3);
				
					for (int y = 0; y < histogram_Size; y++) 
					{
						buffor.at<cv::Vec3b>(y) = cv::Vec3b(cv::saturate_cast<uchar>(y * 180/ histogram_Size), 255, 255);
					}
					cvtColor(buffor, buffor, cv::COLOR_HSV2BGR);
					for (int x = 0; x < histogram_Size; x++) {
						int val = cv::saturate_cast<int>(mat_histogram.at<float>(x) * mat_histogram_picture.rows / 255);
						cv::rectangle(mat_histogram_picture, cv::Point(x * binW, mat_histogram_picture.rows),
							cv::Point((x + 1) * binW, mat_histogram_picture.rows - val), cv::Scalar(buffor.at<cv::Vec3b>(x)), -1, 8);
					}
					mat_card = cv::Mat(mat_frame.rows, mat_frame.cols, CV_8UC3, cv::Scalar(255, 255, 255));
					cv::imshow(window_histogram[0], mat_histogram_picture);
					obiekt.push_back(Obiekt(Area_Rectangular_selected, (int)h_min_range, (int)h_max_range, mat_contour_temp, mat_histogram));
					
				}
				for (int i = 0; i < obiekt.size(); i++)
				{		
					cv::calcBackProject(&mat_hsv_split[0], 1, 0, obiekt.at(i).gethistogram(), mat_backproj, &histogram_pointer_Zasieg);
					mat_backproj &= obiekt.at(i).getMat_contour();	
					cv::RotatedRect Area_Rectangular_tracked_trackbox = CamShift(mat_backproj, obiekt.at(i).getRectangle(),
						cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10, 1)); 
					
				
					//std::cout << "Rectangle after nr" << i << "x" << obiekt.at(i).getRectangle().x << "\n";
					
					//cv::cvtColor(mat_backproj, mat_img, cv::COLOR_GRAY2BGR);		
					
				    // position = point_track;
					obiekt.at(i).setTracking_Points(Drawing_Position(Area_Rectangular_tracked_trackbox.center, Drawing_Radius_get(Area_Rectangular_tracked_trackbox.size.width, Area_Rectangular_tracked_trackbox.size.height)));
					if (Is_Drawing_active == true)
					{
						circle(mat_card, obiekt.at(0).getTracking_Points().point, position.r / Trackbars_parametr_diameterScale, cv::Scalar(0, 0, 0), 4, cv::LINE_AA);
						circle(mat_card, obiekt.at(1).getTracking_Points().point, position.r / Trackbars_parametr_diameterScale, cv::Scalar(0, 0, 0), 4, cv::LINE_AA);
					}
				  
				    cv::circle(mat_img, obiekt.at(i).getTracking_Points().point, 20, cv::Scalar(i*40, 0, 0), 4, cv::LINE_8);//Tracking point
					cv::circle(mat_img, obiekt.at(i).getTracking_Points().point, 10, cv::Scalar(i*40, i*40, i*40), 4, cv::LINE_8);//Tracking point
					cv::circle(mat_img, obiekt.at(i).getTracking_Points().point, 5, cv::Scalar(i*40, 0, 0), 4, cv::LINE_8);//Tracking point
					cv::putText(mat_img, names_pointer[i], obiekt.at(i).getTracking_Points().point, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar::all(255), 2, 8);
					cv::imshow(window_card[0], mat_card);
					
				}
			}
			cv::circle(mat_img, cv::Point(X, Y), 1, cv::Scalar(255, 0, 0), 1, cv::LINE_8, 0);//Kursor

		}
		if (Is_HSV_active)
		{
			cv::cvtColor(mat_img, mat_hsv, cv::COLOR_BGR2HSV);
			Operation_DrawCVImage(Image_Original, mat_hsv);
			return;
		}
		if (Is_Contour_active)
		{
			///cv::cvtColor(mat_img, mat_hsv, cv::COLOR_BGR2HSV);
			cv::inRange(mat_hsv_split[0], Trackbars_parametr_H_MIN, Trackbars_parametr_H_MAX, mat_contour);
			Operation_filter(mat_contour);
			//return;
		}
		Operation_DrawCVImage(Image_Original, mat_img);
	}
#pragma endregion
	private: System::Void Timer_motion_pause(System::Object^  sender, System::EventArgs^  e)
	{
		Point P = PointToScreen(Point(Image_Original->Bounds.Left, Image_Original->Bounds.Top));
		Int32 X = Cursor->Position.X - P.X;
		Int32 Y = Cursor->Position.Y - P.Y;
		mat_img.copyTo(mat_temp);
		if (Is_Drawing_area_being_selected)
		{
			Area_Rectangular_selected.x = MIN(X, Area_Point_begin.x);
			Area_Rectangular_selected.y = MIN(Y, Area_Point_begin.y);
			Area_Rectangular_selected.width = std::abs(X - Area_Point_begin.x);
			Area_Rectangular_selected.height = std::abs(Y - Area_Point_begin.y);
			cv::rectangle(mat_temp, Area_Rectangular_selected, cv::Scalar(128), 1, 8, 0);
			Area_Rectangular_selected &= cv::Rect(0, 0, mat_img.cols, mat_img.rows);//tworzenie prostokata
			Operation_DrawCVImage(Image_Original, mat_temp);
		}

	}
	private: System::Void Image_Original_Click(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
