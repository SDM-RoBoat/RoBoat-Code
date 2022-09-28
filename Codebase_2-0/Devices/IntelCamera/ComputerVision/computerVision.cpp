#include "computerVision.h"

int main(int argc, char ** argv)
{
    bool loop = true;
    cv::Mat frame;
    //just to geta change
    cv::VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened())
    {
        cout << "Error on opening cam" << endl;
        return -1;
    }

    cout << "testing cam...." << endl;
    while (loop)
    {
        cap.read(frame);
        if (frame.empty())
        {
            cout << "blank frame error" << endl;
            loop = false;
        }
        else
            cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            loop = false;
    }

    return 0;
}