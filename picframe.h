#ifndef PICFRAME_H
#define PICFRAME_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ctime>
#include <Qdebug>
#include <iostream>
#include <windows.h>


class PicFrame
{
public:
    PicFrame();
    ~PicFrame();

public:    
    void GetTime(); // pobiera aktualny czas, i tworzy z niego nazwe
    // getters and setters
    void putImage(cv::Mat t){img = t;}
    std::string getCurrent_time() const;
    void setCurrent_time(const std::string &value);
    cv::Mat getImage(){return img;}

private:
    std::string current_time;
    cv::Mat img;

};

#endif // PICFRAME_H
