#ifndef GETFRAME_H
#define GETFRAME_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <list>
#include "picframe.h"
#include <QString>
#include <windows.h>

#define BUFFOR_SIZE 50

using namespace std;
using namespace cv;

class GetFrame
{
public:
    GetFrame();
    GetFrame(int);
    GetFrame(string);
    ~GetFrame();

public:
   bool setAdrCapture(int);
   bool setAdrCapture(string);
   void getCapture();
   void resizePic(int, int);
   void resizePic(Mat, int, int);
   void putRect(Mat ,int, int, int, int);
   void setNamePic();
   void setCamName();
   void putFrame(Mat);
   void putFrame2(Mat);
   Mat getOldFrame();
   Mat getOldFrame2();
   bool incIterator();
   bool decIterator();
   Mat getImg() const;
   void setImg(Mat t);
   int getImg_number() const;
   void setImg_number(int value);
   int getBuffor_counter() const;
   void setBuffor_counter(int value);
   string getCam_adr() const;
   Mat getSmallPic(int x, int y);

private:
   void msg(QString s);

public:
   VideoCapture cap;
   list<PicFrame>::iterator cntr;
   int buffor_counter;
   int current_buffor_size;
   Mat img, img_copy;
   int img_number;
   string loc;
   string cam_adr;
   string cam_name;
   string frame_time;
   bool reopen_cam;

private:
   list<PicFrame> buffor1;

};

#endif // GETFRAME_H
