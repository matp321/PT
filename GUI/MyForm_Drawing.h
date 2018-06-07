#pragma once
#include "Common.h"

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm1
	/// </summary>
	public ref class MyForm_Drawing : public System::Windows::Forms::Form
	{
	public:
		//bool Is_button_circle_clicked;
		System::Windows::Forms::ColorDialog^  colorDialog;
		MyForm_Drawing()
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
		~MyForm_Drawing()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::Button^  button_line;
	protected:
	public: System::Windows::Forms::Button^  button_rectangle;


	public: System::Windows::Forms::Button^  button_pencil;

	public: System::Windows::Forms::Button^  button_colorpick;




	protected:

	protected:








	







	private:
		ColorDialog^ colordialog;
	private: System::Windows::Forms::NumericUpDown^  numeric_Line_Thickness;

	private: System::Windows::Forms::Label^  label1;
			 /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm_Drawing::typeid));
			this->button_line = (gcnew System::Windows::Forms::Button());
			this->button_rectangle = (gcnew System::Windows::Forms::Button());
			this->button_pencil = (gcnew System::Windows::Forms::Button());
			this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->button_colorpick = (gcnew System::Windows::Forms::Button());
			this->numeric_Line_Thickness = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_Line_Thickness))->BeginInit();
			this->SuspendLayout();
			// 
			// button_line
			// 
			this->button_line->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_line.Image")));
			this->button_line->Location = System::Drawing::Point(9, 12);
			this->button_line->Name = L"button_line";
			this->button_line->Size = System::Drawing::Size(40, 32);
			this->button_line->TabIndex = 0;
			this->button_line->UseVisualStyleBackColor = true;
			this->button_line->Click += gcnew System::EventHandler(this, &MyForm_Drawing::Button_Line);
			// 
			// button_rectangle
			// 
			this->button_rectangle->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_rectangle.Image")));
			this->button_rectangle->Location = System::Drawing::Point(53, 12);
			this->button_rectangle->Name = L"button_rectangle";
			this->button_rectangle->Size = System::Drawing::Size(40, 32);
			this->button_rectangle->TabIndex = 4;
			this->button_rectangle->UseVisualStyleBackColor = true;
			this->button_rectangle->Click += gcnew System::EventHandler(this, &MyForm_Drawing::Button_Rectangle);
			// 
			// button_pencil
			// 
			this->button_pencil->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_pencil.Image")));
			this->button_pencil->Location = System::Drawing::Point(7, 53);
			this->button_pencil->Name = L"button_pencil";
			this->button_pencil->Size = System::Drawing::Size(40, 32);
			this->button_pencil->TabIndex = 7;
			this->button_pencil->UseVisualStyleBackColor = true;
			this->button_pencil->Click += gcnew System::EventHandler(this, &MyForm_Drawing::Button_Pencil);
			// 
			// colorDialog
			// 
			this->colorDialog->AnyColor = true;
			this->colorDialog->FullOpen = true;
			this->colorDialog->ShowHelp = true;
			// 
			// button_colorpick
			// 
			this->button_colorpick->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_colorpick.Image")));
			this->button_colorpick->Location = System::Drawing::Point(53, 50);
			this->button_colorpick->Name = L"button_colorpick";
			this->button_colorpick->Size = System::Drawing::Size(40, 35);
			this->button_colorpick->TabIndex = 9;
			this->button_colorpick->UseVisualStyleBackColor = true;
			this->button_colorpick->Click += gcnew System::EventHandler(this, &MyForm_Drawing::Button_Color_Pick);
			// 
			// numeric_Line_Thickness
			// 
			this->numeric_Line_Thickness->Location = System::Drawing::Point(108, 50);
			this->numeric_Line_Thickness->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numeric_Line_Thickness->Name = L"numeric_Line_Thickness";
			this->numeric_Line_Thickness->Size = System::Drawing::Size(120, 20);
			this->numeric_Line_Thickness->TabIndex = 10;
			this->numeric_Line_Thickness->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numeric_Line_Thickness->ValueChanged += gcnew System::EventHandler(this, &MyForm_Drawing::numeric_Line_Thickness_Event_Value_changed);
			this->numeric_Line_Thickness->Click += gcnew System::EventHandler(this, &MyForm_Drawing::Click_numeric_line);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(129, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 13);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Line thickness";
			// 
			// MyForm_Drawing
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(253, 128);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->numeric_Line_Thickness);
			this->Controls->Add(this->button_colorpick);
			this->Controls->Add(this->button_pencil);
			this->Controls->Add(this->button_rectangle);
			this->Controls->Add(this->button_line);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"MyForm_Drawing";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"Tools";
			this->Load += gcnew System::EventHandler(this, &MyForm_Drawing::MyForm_Drawing_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_Line_Thickness))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_Drawing_Load(System::Object^  sender, System::EventArgs^  e) 
	{
		colordialog = gcnew ColorDialog;
		//obiekt.at(selected_index).setLine_thickness(int(numeric_Line_Thickness->Value));
		//obiekt.at(selected_index).setIs_drawing_Pencil_active(true);
		
		
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void Button_Color_Pick(System::Object^  sender, System::EventArgs^  e) {

	colordialog->AllowFullOpen = true;
	colordialog->ShowHelp = true;
	colordialog->ShowDialog();
	Color clr = colordialog->Color;
	obiekt.at(selected_index).setColor(cv::Scalar(clr.B, clr.G, clr.R));

}	
private: System::Void Button_Line(System::Object^  sender, System::EventArgs^  e) {
	obiekt.at(selected_index).deactivate_drawing();
	obiekt.at(selected_index).setIs_drawing_line_active(true);
}
private: System::Void Button_Rectangle(System::Object^  sender, System::EventArgs^  e) {
	obiekt.at(selected_index).deactivate_drawing();
	obiekt.at(selected_index).setIs_drawing_rectangle_active(true);
}
private: System::Void Button_Circle(System::Object^  sender, System::EventArgs^  e) {
	std::cout << "Activation"<<"\n";
	obiekt.at(selected_index).deactivate_drawing();
	obiekt.at(selected_index).setIs_drawing_circle_active(true);
}
private: System::Void Button_Pencil(System::Object^  sender, System::EventArgs^  e) {
	obiekt.at(selected_index).deactivate_drawing();
	obiekt.at(selected_index).setIs_drawing_Pencil_active(true);
}
private: System::Void Button_Eraser(System::Object^  sender, System::EventArgs^  e) {
	obiekt.at(selected_index).deactivate_drawing();
	//obiekt.at(selected_index).setIS(true);
}
private: System::Void Button_Thickness(System::Object^  sender, System::EventArgs^  e) {

}

private: System::Void numeric_Line_Thickness_Event_Value_changed(System::Object^  sender, System::EventArgs^  e) {

	obiekt.at(selected_index).setLine_thickness(int(numeric_Line_Thickness->Value));
	std::cout << "Check";
}
public: System::Void Click_numeric_line(System::Object^  sender, System::EventArgs^  e) {
	
}
};
}
