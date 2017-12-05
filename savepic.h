#ifndef SAVEPIC_H
#define SAVEPIC_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "picframe.h"
#include <list>


using namespace cv;
using namespace std;

class SavePic
{
public:
    SavePic(const list<PicFrame>::iterator &cntr, Mat t){this->cntr = cntr; temp = t.clone();}
    SavePic(Mat t){temp = t.clone();}
    SavePic(){}
    ~SavePic();

public:
    void save(int rect_x, int rect_y, int rect_w, int rect_h, string loc, string = ".jpg");
    void saveP(int rect_x, int rect_y, int rect_w, int rect_h, string loc, string = ".jpg");
    void saveHelper(Mat pic, string loc, string type);

    list<PicFrame>::iterator getCntr() const;
    void setCntr(const list<PicFrame>::iterator &value);

private:
    list<PicFrame>::iterator cntr;
    int img_number;
    string loc;
    Mat temp;


};

#endif // SAVEPIC_H
