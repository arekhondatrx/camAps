#include "savepic.h"
#include <fstream>
#include <QImageWriter>
#include <QImage>
#include <QMessageBox>
#include <QFileInfo>

SavePic::~SavePic()
{

}

void SavePic::save(int rect_x, int rect_y, int rect_w, int rect_h, string loc, string type)
{
    if(rect_x + rect_w  >= temp.cols)
       rect_x = temp.cols - rect_w - 1;

    if(rect_y + rect_h  >= temp.rows)
       rect_y = temp.rows - rect_h - 1;

    if(!temp.empty())
    {
        temp = temp(Rect(rect_x,rect_y, rect_w, rect_h));
        loc +=cntr->getCurrent_time();
        saveHelper(temp,loc,type);
    }
    else
    {
        qDebug() << "nie zapisono , bład";
    }
}

void SavePic::saveP(int rect_x, int rect_y, int rect_w, int rect_h, string loc, string type)
{
   if(rect_x < 0)
        rect_x = 0;

   if(rect_y < 0)
        rect_y = 0;

    if(rect_x + rect_w  >= temp.cols)
        rect_x = temp.cols - rect_w - 1;

    if(rect_y + rect_h  >= temp.rows)
       rect_y = temp.rows - rect_h - 1;

    if(temp.empty() == false)
    {
        temp = temp(Rect(rect_x,rect_y, rect_w, rect_h));
        saveHelper(temp,loc,type);
    }
}

void SavePic::saveHelper(Mat pic, string loc, string type)
{
    img_number = 0;
     while(true)
     {
         this->loc = loc + to_string(img_number) + type;

         if(QFileInfo::exists(QString::fromStdString(this->loc.c_str())))
         {
             img_number++;
         }
         else
         {
             if(!pic.empty())
             {
             QImage image1 = QImage((uchar*) pic.data,  pic.cols,  pic.rows,  pic.step, QImage::Format_RGB888);
             QImageWriter writer(QString::fromStdString(this->loc));
             writer.write(image1);
             }

             img_number++;
             return;
         }
     }
}

list<PicFrame>::iterator SavePic::getCntr() const
{
    return cntr;
}

void SavePic::setCntr(const list<PicFrame>::iterator &value)
{
    cntr = value;
}
