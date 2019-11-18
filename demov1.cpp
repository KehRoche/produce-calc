#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

Mat origin, gray;

Mat element, egde;

int minvalue = 31;
int maxvalue = 105;

int erode_size = 6;
int gaussian_size = 9;

static void filter_size(int, void *)
{
    element = getStructuringElement(MORPH_RECT, Size(erode_size, erode_size));
    erode(gray, egde, element);

    imshow("Edge", egde);
}

static void thresholdfilter(int, void *)
{
    inRange(origin, Scalar(0, 0, minvalue), Scalar(255, 255, maxvalue), gray);
    imshow("dst", gray);
}
int main(int argc, char **argv)
{

    origin = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    namedWindow("input", CV_WINDOW_AUTOSIZE);


    namedWindow("dst", CV_WINDOW_AUTOSIZE);

    createTrackbar("Minvalue", "dst", &minvalue, 255, thresholdfilter);
    createTrackbar("Maxvalue", "dst", &maxvalue, 255, thresholdfilter);

    inRange(origin, Scalar(0, 0, minvalue), Scalar(255, 255, maxvalue), gray);

    namedWindow("Edge", CV_WINDOW_AUTOSIZE);

    element = getStructuringElement(MORPH_RECT, Size(5, 5));
    createTrackbar("erode size", "Edge", &erode_size, 10, filter_size);
    erode(gray, egde, element);


    vector<vector<Point>> contours;
    vector<Vec4i> hierarcy;
    findContours(egde, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    vector<Rect> boundRect(contours.size());  //定义外接矩形集合
    vector<RotatedRect> box(contours.size()); //定义最小外接矩形集合
    Point2f rect[4];
    Mat clone_origin = origin.clone();
    for (int i = 0; i < contours.size(); i++)
    {

        boundRect[i] = boundingRect(Mat(contours[i]));
    }
    Mat imageroi = gray(Rect(boundRect[1].x - 10, boundRect[1].y + 40, boundRect[1].width + 20, boundRect[1].height - 80));
    int x_diff = boundRect[1].x - 10;
    int y_diff = (boundRect[1].y + 40);
    contours.clear();
    hierarcy.clear();
    boundRect.clear();
    findContours(imageroi, contours, hierarcy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    boundRect.resize(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        boundRect[i] = boundingRect(Mat(contours[i]));
        if (boundRect[i].area() <= 30)
            continue;
        rectangle(clone_origin, Point(boundRect[i].x + x_diff, boundRect[i].y + y_diff), Point(boundRect[i].x + x_diff + boundRect[i].width, boundRect[i].y + y_diff + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
        cout << "the width of the produce =" << boundRect[i].width << endl;
    }
    imshow("edge", imageroi);
    imshow("input", clone_origin);

    waitKey(0);
}
