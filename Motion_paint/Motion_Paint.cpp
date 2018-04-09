#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>

#include <iostream>
#include <string>
//INIT
//INIT2
using namespace cv;
using namespace std;

//region Pozycja_struktura

struct Pozycja
{
	Point2i point = Point2i(0, 0);
	int r = 0;

	Pozycja()
	{
		this->point = Point2i(0, 0);
		this->r = 0;
	}
	Pozycja(Point2i point, int r)
	{
		this->point = point;
		this->r = r;
	}
}pozycja;  ////Pozycja

		   //endregion

		   //region zmienne

bool IsAreaSelected = false;
bool Is_drawing_active = false;
bool Is_threshold_active = false;
bool backprojMode = false;
int diameterScale = 2;//zmienne
int smin = 30;
Mat img;
vector<Vec3f> circles;
int lineColorValue = 0;
int Is_tracking_object_active = 0;
int H_MIN = 0;
int H_MAX = 93;
double h_min_range = 0;
double h_max_range = 93;
Rect Rectangular_selected_area;///obszar ktory bedziemy zaznaczac
Point point_beginning;
int BLUR = 2;
int DILATE = 3;
int ERODE = 2;
//endregion

//region Stale

const int FRAME_WIDTH = 1280;
const int FRAME_HEIGHT = 720;
const int MAX_NUM_OBJECTS = 50;
const int MIN_OBJECT_AREA = 50 * 50;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
string window_name[] = { "Kamera", "HSV", "Threeshold","Card","Trackbars","Okno testowe","Histogram" };
//endregion
//region Stablizacja_promienia

int getRadius(int x, int y)
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
bool Radiusmove(Pozycja actualposition, int movestabilize, int Radiustabilize)
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
//endregion

//region Funkcje rysowania

void circledrawing(InputOutputArray img, Point center, int radius, const Scalar& color)
{
	if (Is_drawing_active)
	{
		if (diameterScale == 0)
		{
			diameterScale = 1;
		}
		circle(img, center, radius / diameterScale, color, -1, LINE_AA);
	}
}
void linedrawing(InputOutputArray img, Pozycja poczatkowa, Pozycja koncowa, const Scalar& color)
{
	if (Is_drawing_active)
	{
		if (diameterScale <= 0)
		{
			diameterScale = 1;
		}
		line(img, poczatkowa.point, koncowa.point, color, koncowa.r / diameterScale);
	}
}   ///Rysowani  //Rysowanie
	//endregion

	//region Trackbars przsuwanie suwakiem

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed
}

void createTrackbars()
{
	namedWindow(window_name[4], 0);
	createTrackbar("Thresh lb", window_name[4], &H_MIN, 255, NULL);
	createTrackbar("Thresh ub", window_name[4], &H_MAX, 255, NULL);
	createTrackbar("Diameter scale", window_name[4], &diameterScale, 10, 0);
	createTrackbar("Blur", window_name[4], &BLUR, 15, 0);
	createTrackbar("Dilate", window_name[4], &DILATE, 15, NULL);
	createTrackbar("Erode", window_name[4], &ERODE, 15, NULL);
	createTrackbar("Line color", window_name[4], &lineColorValue, 4, NULL);
}
//endregion


void filterBlur(Mat &thresh) {
	if (BLUR < 1)
	{
		BLUR = 1;
	}
	blur(thresh, thresh, cv::Size(BLUR, BLUR));
}

void filterErode(Mat &thresh) {
	if (ERODE < 1)
	{
		ERODE = 1;
	}
	Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(ERODE, ERODE));

	erode(thresh, thresh, erodeElement);
}

void filterDilate(Mat &thresh) {
	if (DILATE < 1)
	{
		DILATE = 1;
	}
	Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(DILATE, DILATE));

	dilate(thresh, thresh, dilateElement);
}

void filter(Mat &thresh) {

	filterDilate(thresh);

	filterErode(thresh);
}

Scalar lineColor()
{
	switch (lineColorValue)
	{
	case 0:
		return Scalar(0, 0, 0);

	case 1:
		return Scalar(255, 255, 255);

	case 2:
		return Scalar(255, 0, 0);

	case 3:
		return Scalar(0, 255, 0);

	case 4:
		return Scalar(0, 0, 255);

	default:
		return Scalar(255, 255, 255);
		break;
	}
}
static void mouseAction(int event, int x, int y, int flags, void*)
{

	if (IsAreaSelected == true)  //Zostaje pobrany obszar ktory zaznaczylismy myszka
	{
		//cout << "IsAreaSelected: " << IsAreaSelected << "\n";
		Rectangular_selected_area.x = MIN(x, point_beginning.x);
		Rectangular_selected_area.y = MIN(y, point_beginning.y);
		Rectangular_selected_area.width = std::abs(x - point_beginning.x);
		Rectangular_selected_area.height = std::abs(y - point_beginning.y);

		Rectangular_selected_area &= Rect(0, 0, img.cols, img.rows);//tworzenie prostokata

																	//cout << "Rectangular_selected_area values: " << Rectangular_selected_area.x << "\n";
																	//cout << "Rectangular_selected_area values: " << Rectangular_selected_area.y << "\n";
																	//cout << "Rectangular_selected_area values: " << Rectangular_selected_area.width << "\n";
																	//cout << "Rectangular_selected_area values: " << Rectangular_selected_area.height << "\n";
	}
	switch (event)
	{
	case EVENT_LBUTTONDOWN:///zainicjowane po nacisnieciu przycisku myszki
						   //cout << "Test myszki LButtonDOWN" << "\n";//Event na klikniecie myszki jest wywolywany prawidlowo
		point_beginning = Point(x, y);
		Rectangular_selected_area = Rect(x, y, 0, 0);
		IsAreaSelected = true;
		break;
	case EVENT_LBUTTONUP:////zainicjowane po puszczeniu przycisku myszki
						 //cout << "Test myszki LButtonUP" << "\n";
		IsAreaSelected = false;
		//TODO zainicjowanie aktywacji tego if
		if (Rectangular_selected_area.width > 0 && Rectangular_selected_area.height > 0) {
			//cout << "Selected area width=" << Rectangular_selected_area.width << "\n";
			//cout << "Selected area height=" << Rectangular_selected_area.height << "\n";
			Is_tracking_object_active = -1;
		}
		break;
	}
	//endregion

}

int main() {

	//region Inizjalizacja danych histogramu

	//endregion
	cout << "test";
	try
	{
		int histogramSize = 16;
		float histogramZasieg[] = { 0, 180 };
		const float *pHistogramZasieg = histogramZasieg;
		//endregion
		vector<Mat> HSV_SPLIT;
		Point2i pt(-1, -1);
		VideoCapture capture = VideoCapture(0);
		//region inicjalizacja trackbarow oraz towrzenie nowego okna do rysowania
		createTrackbars();
		//endregion
		//region inicjalizacja wielkosc okna
		capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
		//endregion
		//region inicjalizacja okien do wyswietlania
		///inicjalizacja okien
		namedWindow(window_name[0], WINDOW_AUTOSIZE);//Oryginalny obraz z kamery
													 //namedWindow(window_name[1], WINDOW_AUTOSIZE);//Obraz HSV
													 //namedWindow(window_name[2], WINDOW_AUTOSIZE);//Konturoway obraz
													 //namedWindow(window_name[3], WINDOW_AUTOSIZE);//Karta do rysowania  window_name[4] --Okno na trackbary
													 //namedWindow(window_name[5], WINDOW_AUTOSIZE);//okno do testowania
													 //namedWindow(window_name[6], WINDOW_AUTOSIZE);//okno do Histogram
													 //endregion
		setMouseCallback(window_name[0], mouseAction, (void *)&pt);///wlczenie akcji myszy														   //region Mat_variables_declaration
		Rect  Rectangular_window_to_track;
		Mat HSV;
		//Mat hue;
		//Mat mask;
		Mat histogram;
		Mat histogrampicture = Mat::zeros(200, 320, CV_8UC3);
		Mat backproj;
		Mat threshold;
		Mat frame;
		capture >> frame;
		Mat card(frame.rows, frame.cols, CV_8UC3, Scalar(255, 255, 255));
		imshow(window_name[3], card);
		while (true)///getting new frame
		{
			//cout<<"Is tracking object active value"<<Is_tracking_object_active<<"\n";

			//region Rozdzielenia kanalow HSv i inicjalizacja przechwytywanie obrazu z kamery
			capture >> frame;
			flip(frame, frame, 1);
			frame.copyTo(img);
			filterBlur(img);
			cvtColor(img, HSV, COLOR_BGR2HSV);
			split(HSV, HSV_SPLIT);
			// int ch[] = { 0, 0 };
			inRange(HSV_SPLIT[0], H_MIN, H_MAX, threshold);
			int ch[] = { 0, 0 };
			mixChannels(&HSV, 1, &HSV_SPLIT[0], 1, ch, 1);
			filter(threshold);
			imshow(window_name[2], threshold);
			//endregion
			if (Is_tracking_object_active)//exectued after selecting area with mouse
			{
				//region Threeshold initialization after selecting area with mouse
				//region Executed during selecting area with mouse
				if (Is_tracking_object_active < 0)//exectued after selecting area with mouse
				{
					//cout << "Is_tracking_object_active value:" << Is_tracking_object_active;
					Mat roi(HSV_SPLIT[0], Rectangular_selected_area), maskroi(threshold, Rectangular_selected_area);//pobieranie obszaru///stworzenie dwoch nowych matryc pbrazu jedna dotyczy zaznaczonego obszaru hue a druga konturowa
					minMaxLoc(roi, &h_min_range, &h_max_range, nullptr, nullptr);
					H_MIN = (int)h_min_range;
					H_MAX = (int)h_max_range;
					createTrackbars();

					calcHist(&roi, 1, 0, maskroi, histogram, 1, &histogramSize, &pHistogramZasieg);
					normalize(histogram, histogram, 0, 255, NORM_MINMAX);
					Rectangular_window_to_track = Rectangular_selected_area;//Rectangular selected area inicjowane w mouse callback
					Is_tracking_object_active = 1;
					//cout << "Tracking object is active" << "\n";
					histogrampicture = Scalar::all(0);
					//cout << "Histogram picture\n" << histogrampicture.rows << "\n" << histogrampicture.cols;///Jest to zwykla rozdzielczosc
					int binW = histogrampicture.cols / histogramSize;
					Mat buffor(1, histogramSize, CV_8UC3);

					for (int i = 0; i < histogramSize; i++) {
						buffor.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i * 180. / histogramSize), 255, 255);
					}
					cvtColor(buffor, buffor, COLOR_HSV2BGR);

					for (int i = 0; i < histogramSize; i++) {
						int val = saturate_cast<int>(histogram.at<float>(i) * histogrampicture.rows / 255);
						rectangle(histogrampicture, Point(i * binW, histogrampicture.rows),
							Point((i + 1) * binW, histogrampicture.rows - val), Scalar(buffor.at<Vec3b>(i)), -1, 8);
					}

					//cout << "After execurting everything" << "\n";
					imshow(window_name[6], histogrampicture);
				}
				//endregion


				//cout << "Left mouse button has been released" << "\n";
				calcBackProject(&HSV_SPLIT[0], 1, 0, histogram, backproj, &pHistogramZasieg);
				backproj &= threshold;
				RotatedRect trackBox = CamShift(backproj, Rectangular_window_to_track,
					TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1)); //
				if (Rectangular_window_to_track.area() <= 1)
				{
					int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5) / 6;
					Rectangular_window_to_track = Rect(Rectangular_window_to_track.x - r, Rectangular_window_to_track.y - r, Rectangular_window_to_track.x + r, Rectangular_window_to_track.y + r) & Rect(0, 0, cols, rows);
				}
				if (backprojMode)
				{
					cvtColor(backproj, img, COLOR_GRAY2BGR);
				}
				Pozycja aktualnaPozycja = Pozycja(trackBox.center, getRadius(trackBox.size.width, trackBox.size.height));
				//Radiusmove(aktualnaPozycja, 10, 10);
				linedrawing(card, pozycja, aktualnaPozycja, lineColor());
				pozycja = aktualnaPozycja;
				circle(img, pozycja.point, 2, Scalar(255, 0, 0), 2, LINE_8);
				circle(img, pozycja.point, 4, Scalar(0, 255, 0), 2, LINE_8);
				circle(img, pozycja.point, 6, Scalar(0, 0, 255), 2, LINE_8);
				circle(img, pozycja.point, pozycja.r / diameterScale, Scalar(0, 0, 255), 1, LINE_8);
			}
			if (Rectangular_selected_area.width && IsAreaSelected > 0 && Rectangular_selected_area.height > 0)//
			{
				Mat roi(img, Rectangular_selected_area);//tworzenie now
				bitwise_not(roi, roi);///zamiana obrazu na negatyw
			}

			if (Is_threshold_active)
			{
				imshow(window_name[0], threshold);
			}
			else
			{
				if (Is_drawing_active == true)
				{
					//cout << "Is_drawing_active==" << Is_drawing_active << "\n";
					//imshow(window_name[3],card);
					addWeighted(img, 1, card, 0.9, 0.0, img);
					imshow(window_name[0], img);
				}
				else
				{
					//cout << "Is_drawing_active==false" << endl;
					addWeighted(img, 1, card, 0.5, 0.0, img);
					imshow(window_name[0], img);
				}
			}
			//imshow(window_name[1], HSV);//Obraz HSV
			//imshow(window_name[3], card);//Kartka do rysowaniak
			//imshow(window_name[0], img); ///executed after selecting area with mouse ///executed after selecting area with mouse



			//region Interfejs wyboru akcji
			char c = (char)waitKey(10);//Koniec proogramu esc
			if (c == 27) {
				break;
			}
			switch (c) {
			case 's': //zatrzymuje sledzenie obiektu
				Is_tracking_object_active = 0;
				break;
			case 'c': //czysci kartkecc
			{
				//cout << "Card cleaning" << "\n";//
				Mat temp(frame.rows, frame.cols, CV_8UC3, Scalar(255, 255, 255));
				card = temp;
				break;
			}
			case 'r': //zatrzymuje rysowanie//przycisk dziala poprawnie
				if (Is_drawing_active == true) {
					Is_drawing_active = false;
					//cout << "Is_drawing_active value:" << +Is_drawing_active << "\n";
				}
				else {
					Is_drawing_active = true;
					//cout << "Is_drawing_active value:" << +Is_drawing_active << "\n";
				}
				break;
			case 'h': //ukrywa/pokazuje obraz threshold
				if (Is_threshold_active == true) {
					Is_threshold_active = false;
					//cout << "Is_drawing_active value:" << +Is_drawing_active << "\n";
				}
				else {
					Is_threshold_active = true;
					//cout << "Is_drawing_active value:" << +Is_drawing_active << "\n";
				}
				break;
			case 'q':
				diameterScale++;
				break;
			case 'w':
				diameterScale--;
				if (diameterScale <= 0)
				{
					diameterScale = 1;
				}
				break;
			case '0':
				lineColorValue = 0;
				break;
			case '1':
				lineColorValue = 1;
				break;
			case '2':
				lineColorValue = 2;
				break;
			case '3':
				lineColorValue = 3;
				break;
			case '4':
				lineColorValue = 4;
				break;
			default:
				break;
			}
			//endregion
		}
	}
	catch (const exception& ex)
	{
		cout << "Checking";
		main();
	}
	
	
	//TODO


	return 0;

}








