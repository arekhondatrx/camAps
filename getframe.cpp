#pragma once
#include "getframe.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDateTime>
#include <fstream>
#include <QDebug>
#include <QDir>
#include <stdio.h>
#include "savepic.h"
#include <QMessageBox>
#include <string.h>
#include <QThread>

GetFrame::GetFrame():img_number(1),buffor_counter(0),current_buffor_size(0)
{

}

GetFrame::GetFrame(int nr):img_number(1),buffor_counter(0),current_buffor_size(0)
{
    cam_name = "";
    setAdrCapture(nr);
}


GetFrame::GetFrame(string adr):img_number(1),buffor_counter(0),current_buffor_size(0)
{
    cam_name = "";
    setAdrCapture(adr);
}

GetFrame::~GetFrame()
{

}

bool GetFrame::setAdrCapture(int nr)
{
    cap.open(nr);   
    QThread::msleep(1000);
    return cap.isOpened();
}

bool GetFrame::setAdrCapture(string adr)
{
    cap.open(adr);
    if(cap.isOpened())
    {
        cam_adr = adr;
        qDebug() << QString::fromStdString(cam_adr);
        setCamName();
        return true;
    }
    else
    {
        msg("GetFrame::setAdrCapture: Can not open cams, check your internet connection.\n App will be closed !");
        exit(0);
        return false;
    }
}

void GetFrame::resizePic(int size_x, int size_y)
{
    if(!img.empty())
    {
        resize(img, img, Size(size_x, size_y), 0, 0, INTER_CUBIC);
    }
}

void GetFrame::resizePic(Mat image, int size_x, int size_y)
{
    if(!image.empty())
    {
        resize(image, image, Size(size_x, size_y), 0, 0, INTER_CUBIC);
    }
}

void GetFrame::getCapture()
{
    if(cap.isOpened() == false)
    {
         msg("Błąd cap = null");
    }

    if(cap.grab())
    {
        cap.retrieve(img);
    }
    else
    {
        Mat img_tmp(100, 100, CV_8UC3, Scalar(250, 0, 0));
        img = img_tmp.clone();
        cap.release();

        cap.open(cam_adr);
    }

    if(!img.empty())
    {
         cvtColor(img, img, CV_BGR2RGB);
         img_copy = img.clone();
    }
}

void GetFrame::putRect(Mat image,int rect_x, int rect_y, int rect_w, int rect_h)
{
    rectangle(image,cvPoint(rect_x - 1,rect_y - 1),cvPoint(rect_x + rect_w,rect_y + rect_h),CV_RGB(0,255,0),1,4);
}

void GetFrame::setCamName()
{  
    size_t found = 0;
    size_t end = 0;
    size_t start = 0;

    for(int i = 0; i < 3; i++)
    {
        found = cam_adr.find(".", found+1);
    }
    start = found + 1;
    end = cam_adr.find(":", found+1);

    char temp[100] = "";
    size_t length;
    length = cam_adr.copy(temp, end-start, start);
    temp[length] = '\0';

    cam_name = "cam_" + (string)temp;
    qDebug() << QString::fromStdString(cam_name);
}

void GetFrame::putFrame(Mat frame)
{
    if(buffor_counter >= BUFFOR_SIZE)
    {
       buffor_counter--;
       current_buffor_size = buffor_counter;
       buffor1.pop_front();
    }
    PicFrame temp;
    temp.putImage(frame);
    temp.GetTime();
    buffor1.push_back(temp);

    cntr = buffor1.end();
    buffor_counter++;
    current_buffor_size++;
    cntr--;
}

void GetFrame::putFrame2(Mat frame)
{
    if(buffor_counter > BUFFOR_SIZE)
    {
       buffor_counter--;
       current_buffor_size = buffor_counter;
       cntr = buffor1.begin();
       string temp_name = "temp\\" + cam_name + "\\" + cntr->getCurrent_time() + "0.jpg";
       remove(temp_name.c_str());
       buffor1.pop_front();
    }

    QString path = "temp\\" + QString::fromStdString(cam_name);

    if(QDir(path).exists() == false)
    {
        qDebug() << "nie istnieje";
        QDir().mkdir(path);
    }

    PicFrame temp;
    temp.GetTime();
    buffor1.push_back(temp);
    cntr = buffor1.end();
    buffor_counter++;
    current_buffor_size++;
    cntr--;

    path = path + "\\" + QString::fromStdString(cntr->getCurrent_time());
    SavePic saver;

    if(frame.empty() == false)
        saver.saveHelper(frame, path.toUtf8().constData(), ".jpg");
}

Mat GetFrame::getOldFrame()
{
    img = cntr->getImage().clone();
    return img;
}

Mat GetFrame::getOldFrame2()
{
    string temp_name = "temp\\" + cam_name + "\\" + cntr->getCurrent_time() + "0.jpg";
    img = imread(temp_name);
    if(!img.empty())
        cvtColor(img, img, CV_BGR2RGB);
    return img;
}

bool GetFrame::incIterator()
{
    if(current_buffor_size <= BUFFOR_SIZE && buffor_counter < current_buffor_size)
    {
        cntr++;
        buffor_counter++;
        return true;
    }
    return false;
}

bool GetFrame::decIterator()
{
    if(buffor_counter > 1)
    {
        cntr--;
        buffor_counter--;
        return true;
    }
    return false;
}



int GetFrame::getBuffor_counter() const
{
    return buffor_counter;
}

void GetFrame::setBuffor_counter(int value)
{
    buffor_counter = value;
}


////////////////////////////////
/////// Seters && Geters ///////

Mat GetFrame::getImg() const
{
    return img;
}

void GetFrame::setImg(Mat t)
{
    img  = t.clone();
}


int GetFrame::getImg_number() const
{
    return img_number;
}

void GetFrame::setImg_number(int value)
{
    img_number = value;
}

string GetFrame::getCam_adr() const
{
    return cam_adr;
}

Mat GetFrame::getSmallPic(int x, int y)
{
    Mat small_pic(100, 100, CV_8UC3, Scalar(250, 0, 0));

    if(!img.empty())
    {
        resize(img, small_pic, Size(x, y), 0, 0, INTER_CUBIC);
    }

    return small_pic;
}

void GetFrame::msg(QString s)
{
    QMessageBox m;
    m.setText(s);
    m.exec();
}

