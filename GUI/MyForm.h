#pragma once

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <vector>
cv::VideoCapture capture;
cv::Mat mat_frame;
cv::Mat mat_img;
std::vector<cv::Mat> mat_img_split;


bool Is_Contour_active = false;
bool Is_Original_active = false;
bool Is_HSV_active = false;
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

#pragma region Image processing functions Operation_*
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
		}
#pragma endregion
#pragma region Button actions (Button_*)
//approved
private: System::Void Button_Video_Start(System::Object^  sender, System::EventArgs^  e) 
{
	Operation_Deactivate();
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
		Is_HSV_active = false;
		Is_Original_active = false;
		Is_Contour_active = true;
	}
}
//approved
private: System::Void Button_Show_HSV(System::Object^  sender, System::EventArgs^  e)
{
	if (Is_HSV_active == false)
	{
		Is_HSV_active = true;
		Is_Original_active = false;
		//if (capture.isOpened() == true)std::cout << "Opened";	
	}
}
//approved
 private: System::Void Button_Show_Original(System::Object^  sender, System::EventArgs^  e)
 {
	 if (Is_Original_active == false)
	 {
		 Is_Original_active = true;
		 Is_HSV_active = false;

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
#pragma region Przechwytywanie
		//Is_Original_active = false;
		//cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
		Operation_DrawCVImage(Image_Original, mat_img);
#pragma endregion
	}
	if (Is_HSV_active)
	{
#pragma region Przechwytywanie
		cv::cvtColor(mat_img, mat_img, cv::COLOR_BGR2HSV);
		Operation_DrawCVImage(Image_Original, mat_img);
#pragma endregion
	}
	if (Is_Contour_active)
	{
#pragma region Przechwytywanie
		cv::cvtColor(mat_img, mat_img, cv::COLOR_BGR2HSV);
		split(mat_img, mat_img_split);
		cv::inRange(mat_img_split[0],100,200, mat_img);
		int ch[] = { 0, 0 };
		cv::mixChannels(&mat_img, 1, &mat_img_split[0], 1, ch, 1);
		Operation_DrawCVImage(Image_Original, mat_img);
#pragma endregion
	}
	else
	{
		Operation_DrawCVImage(Image_Original, mat_img);
	}
}
#pragma endregion
};
}