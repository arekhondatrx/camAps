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
   bool setAdrCapture(int); // otwiera loklana kamere
   bool setAdrCapture(string);// otwiera kamere IP
   void getCapture(); // poniera ramke z buffora kamry
   void resizePic(int, int); // zmienia rozmiar obrazu
   void resizePic(Mat, int, int);
   void putRect(Mat ,int, int, int, int); // wrzyca na obraz prostokat
   void setCamName(); // ustawia nazwe kamery
   void putFrame(Mat); // wrzuca ramke do lokalnego buffora
   Mat getOldFrame(); // pobiera rake z lokalnego bufora
   bool incIterator();// inkrementuje iterator
   bool decIterator();// deinkrementuje iterator
   // setters and getters
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
