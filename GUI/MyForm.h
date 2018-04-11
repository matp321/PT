#pragma once

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>
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
std::vector<cv::Mat> mat_hsv_split;
cv::Mat mat_histogram_picture = cv::Mat::zeros(200, 320, CV_8UC3);



int histogram_Size = 16;
float histogram_Zasieg[] = { 0, 180 };
const float *histogram_pointer_Zasieg = histogram_Zasieg;
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
}position;

#pragma region Trackbar parametry
int Trackbars_parametr_H_MIN = 0;
int Trackbars_parametr_H_MAX = 0;
double h_min_range = 0;
double h_max_range = 93;
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
bool Is_Tracking_active = false;
bool Is_backprojMode = false;
#pragma endregion 

#pragma region Drawing and seelecting area
cv::Rect Area_Rectangular_selected;
cv::Rect Area_Rectangular_tracked;
cv::Point Area_Point_begin;
cv::Point Area_Point_end;
int Drawing_line_Color_Value = 0;
cv::Point2i pt(-1, -1);
#pragma endregion%


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
	private: System::Windows::Forms::Button^  button6;

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
			this->button6 = (gcnew System::Windows::Forms::Button());
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
			this->button3->Location = System::Drawing::Point(-2, 130);
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
			this->Image_Original->Size = System::Drawing::Size(640, 480);
			this->Image_Original->TabIndex = 3;
			this->Image_Original->TabStop = false;
			this->Image_Original->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Down_Image_Original);
			this->Image_Original->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Up_Image_Original);
			// 
			// Timer_Capture
			// 
			this->Timer_Capture->Interval = 5;
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
			// button6
			// 
			this->button6->Location = System::Drawing::Point(-2, 159);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(109, 23);
			this->button6->TabIndex = 6;
			this->button6->Text = L"Activate drawing";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::Button_Drawing_Start_Stop);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(776, 512);
			this->Controls->Add(this->button6);
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
			Is_Drawing_area_selected = false;
			Is_HSV_active = false;
			Is_Original_active = false;
			Is_Contour_active = false;
			Is_Drawing_area_being_selected = false;
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

		//Operation_Deactivate();
		Area_Point_begin = cv::Point(X, Y);
		Is_Drawing_area_being_selected = true;
		Is_Original_active = true;
		//Timer_Capture->Start();
	}
	private: System::Void Mouse_Up_Image_Original(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		std::cout << "Mouse_Up";
		Is_Drawing_area_being_selected = false;
		if (Is_Original_active == true)Trackbars_Create();
		Operation_Deactivate();
		Is_Drawing_area_selected = true;
		Is_Original_active = true;
		
		//Area_Point_end.x = Image_Original->Cursor->Position.X;
		//Area_Point_end.y = Image_Original->Cursor->Position.Y;

	}
#pragma endregion
#pragma region Button actions (Button_*)
	private: System::Void Button_Video_Start(System::Object^  sender, System::EventArgs^  e)
	{
		capture.release();
		capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
		
		//Trackbars_Create();
		Operation_Deactivate();
		//	cv::setMouseCallback(window_name[0], Mouse_Action, (void *)&pt);
		capture = cv::VideoCapture(0);
		Image_Original->Show();
		Timer_Capture->Start();
	}
	private: System::Void Button_Video_Stop(System::Object^  sender, System::EventArgs^  e)
	{
		Operation_Deactivate();
		Timer_Capture->Stop();
		capture.release();
		Image_Original->Hide();
	}//Implemented
	private: System::Void Button_Show_Contour(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_Contour_active == false)
		{
			Operation_Deactivate();
			Is_Contour_active = true;
		}
	}
	private: System::Void Button_Show_HSV(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_HSV_active == false)
		{
			Operation_Deactivate();
			Is_HSV_active = true;
			//if (capture.isOpened() == true)std::cout << "Opened";	
		}
	}
	private: System::Void Button_Show_Original(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_Original_active == false)
		{
			Operation_Deactivate();
			Is_Original_active = true;

		}
	}
	private: System::Void Button_Drawing_Start_Stop(System::Object^  sender, System::EventArgs^  e)
	{
		if (Is_Drawing_active)Is_Drawing_active = false; return;
		if (Is_Drawing_active==false)Is_Drawing_active = true; return;
	}
#pragma endregion 
#pragma region Real time capture(Timer_motion)
	private: System::Void Timer_motion(System::Object^  sender, System::EventArgs^  e)
	{
		Point P = PointToScreen(Point(Image_Original->Bounds.Left, Image_Original->Bounds.Top));
	Int32 X = Cursor->Position.X - P.X;
	Int32 Y = Cursor->Position.Y - P.Y;
	cv::namedWindow("HISTOGRAM", cv::WINDOW_AUTOSIZE);
	
		
		capture >> mat_frame;
		flip(mat_frame, mat_frame, 1);
		mat_frame.copyTo(mat_img);
		//cv::imshow("HISTOGRAM", mat_frame);
		if (Is_Original_active)
		{
			cv::cvtColor(mat_img, mat_hsv, cv::COLOR_BGR2HSV);
			cv::split(mat_img, mat_hsv_split);
			cv::inRange(mat_hsv_split[0], Trackbars_parametr_H_MIN, Trackbars_parametr_H_MAX, mat_contour);
			int ch[] = { 0, 0 };
			cv::mixChannels(&mat_hsv, 1, &mat_hsv_split[0], 1, ch, 1);
			Operation_filter(mat_contour);
			if (Is_Drawing_area_being_selected)
			{
				
				std::cout << "Mouse_Down\n";
				std::cout << Image_Original->Cursor->Position.X;
				//Area_Rectangular = cv::Rect(Area_Point_begin.x, Area_Point_begin.y, 100, 100);
				Area_Rectangular_selected.x = MIN(X, Area_Point_begin.x);
				Area_Rectangular_selected.y = MIN(Y, Area_Point_begin.y);
				Area_Rectangular_selected.width = std::abs(X - Area_Point_begin.x);
				Area_Rectangular_selected.height = std::abs(Y - Area_Point_begin.y);

			
				cv::rectangle(mat_img, Area_Rectangular_selected, cv::Scalar(128), 1, 8, 0);

			}
			if (Is_Drawing_area_selected &&Is_Drawing_area_being_selected == false)
			{

				if (Area_Rectangular_selected.width>10 && Area_Rectangular_selected.height>10 )
				{		
					if (Is_Tracking_active==false)
					{
						cv::Mat mat_roi_H(mat_hsv_split[0], Area_Rectangular_selected), mat_roi_Contour(mat_contour, Area_Rectangular_selected);
						cv::minMaxLoc(mat_roi_H, &h_min_range, &h_max_range, nullptr, nullptr);
						Trackbars_parametr_H_MIN = (int)h_min_range;
						Trackbars_parametr_H_MAX = (int)h_max_range;
						cv::calcHist(&mat_roi_H, 1, 0, mat_roi_Contour, mat_histogram, 1, &histogram_Size, &histogram_pointer_Zasieg);
						cv::normalize(mat_histogram, mat_histogram, 0, 255, cv::NORM_MINMAX);
						Area_Rectangular_tracked = Area_Rectangular_selected;
						//cout << "Histogram picture\n" << histogrampicture.rows << "\n" << histogrampicture.cols;///Jest to zwykla rozdzielczosc
						Is_Tracking_active = true;
						mat_histogram_picture = cv::Scalar::all(0);
						//cout << "Histogram picture\n" << histogrampicture.rows << "\n" << histogrampicture.cols;///Jest to zwykla rozdzielczosc
						int binW = mat_histogram_picture.cols / histogram_Size;
						cv::Mat buffor(1, histogram_Size, CV_8UC3);

						for (int i = 0; i < histogram_Size; i++) {
							buffor.at<cv::Vec3b>(i) = cv::Vec3b(cv::saturate_cast<uchar>(i * 180. / histogram_Size), 255, 255);
						}
						cvtColor(buffor, buffor, cv::COLOR_HSV2BGR);

						for (int i = 0; i < histogram_Size; i++) {
							int val = cv::saturate_cast<int>(mat_histogram.at<float>(i) * mat_histogram_picture.rows / 255);
							cv::rectangle(mat_histogram_picture, cv::Point(i * binW, mat_histogram_picture.rows),
								cv::Point((i + 1) * binW, mat_histogram_picture.rows - val), cv::Scalar(buffor.at<cv::Vec3b>(i)), -1, 8);
						}

						//cout << "After execurting everything" << "\n";
						imshow("HISTOGRAM", mat_histogram_picture);

					}
					
					
						cv::calcBackProject(&mat_hsv_split[0], 1, 0, mat_histogram, mat_backproj, &histogram_pointer_Zasieg);
						mat_backproj &= mat_contour;
						cv::RotatedRect Area_Rectangular_tracked_trackbox = cv::CamShift(mat_backproj, Area_Rectangular_tracked,
							cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10, 1)); //
						if (Area_Rectangular_tracked.area() <= 1)
						{
							int cols = mat_backproj.cols, rows = mat_backproj.rows, r = (MIN(cols, rows) + 5) / 6;
							Area_Rectangular_tracked = cv::Rect(Area_Rectangular_tracked.x - r, Area_Rectangular_tracked.y - r, Area_Rectangular_tracked.x + r, Area_Rectangular_tracked.y + r) & cv::Rect(0, 0, cols, rows);
						}
						if (Is_backprojMode)
						{
							cv::cvtColor(mat_backproj, mat_img, cv::COLOR_GRAY2BGR);
						}
						Drawing_Position aktualnaPozycja = Drawing_Position(Area_Rectangular_tracked_trackbox.center, Drawing_Radius_get(Area_Rectangular_tracked_trackbox.size.width, Area_Rectangular_tracked_trackbox.size.height));
						//Radiusmove(aktualnaPozycja, 10, 10);
						Drawing_line(mat_card, position, aktualnaPozycja,1);
						position = aktualnaPozycja;
						circle(mat_img, position.point, 2, cv::Scalar(255, 0, 0), 2, cv::LINE_8);
						circle(mat_img, position.point, 4, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
						circle(mat_img, position.point, 6, cv::Scalar(0, 0, 255), 2, cv::LINE_8);
						circle(mat_img, position.point, pozycja.r / Trackbars_parametr_diameterScale, cv::Scalar(0, 0, 255), 1, cv::LINE_8);		
				}


			}	
			cv::circle(mat_img, cv::Point(X, Y), 10, cv::Scalar(255, 0, 0), 2, cv::LINE_8,0);
			Operation_DrawCVImage(Image_Original, mat_img);
		}
		if (Is_HSV_active)
		{
			cv::cvtColor(mat_img, mat_img, cv::COLOR_BGR2HSV);
			Operation_DrawCVImage(Image_Original, mat_img);
		}
		if (Is_Contour_active)
		{

			cv::cvtColor(mat_img, mat_hsv, cv::COLOR_BGR2HSV);
			split(mat_hsv, mat_hsv_split);
			cv::inRange(mat_hsv_split[0], Trackbars_parametr_H_MIN, Trackbars_parametr_H_MAX, mat_contour);
			int ch[] = { 0, 0 };
			//cv::mixChannels(&mat_hsv, 1, &mat_hsv_split[0], 1, ch, 1);
			Operation_filter(mat_contour);
			Operation_DrawCVImage(Image_Original, mat_contour);
		}
		else Operation_DrawCVImage(Image_Original, mat_img);

	}
#pragma endregion



};
}