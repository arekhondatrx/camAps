#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H

#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QStringList>
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <iostream>

using namespace cv;
using namespace std;

class PhotoViewer
{
public:
    static int cntr;

public:
    PhotoViewer();
    PhotoViewer(Ui::MainWindow *ui);

public:
    void getDirectory();
    bool showImage(QLabel *);
    int checkType();
    void setUi(Ui::MainWindow *ui);
    void putRect(QLabel *label,int rect_x, int rect_y, int rect_w, int rect_h);
    void photoResize(QLabel *label,int rect_x, int rect_y, int rect_w, int rect_h);
    void photoResize2(QLabel *label,float perc);
    void clearRect();
    void incCntr();
    void decCntr();
    int getImageWidth();
    int getImageHeight();
    string getName();
    void fillPoz(QLabel *, int *,int *);
    Mat getMatImg() const;
    void setMatImg(const Mat &value);
    void roateR();
    void roateL();
    void checkSize(QLabel *label);
    float getImg_per() const;
    int getImg_width_resize() const;
    int getImg_height_resize() const;
    void setPathh(const QString &value);
    void rt(Mat& src,int angle);
    void rt(int angle);
    void show(QLabel * label);

    int getAngle() const;
    void setAngle(int value);

    void setMatImgCopy(const Mat &value);

    void setAngleR(int value);

    void setAngleL(int value);

private slots:


private:
    Ui::MainWindow *ui;
    QDir dir;
    QStringList list;
    QString pathh, old_path;
    QString load_picture_loc;
    int angleR, angleL, angle;
    int img_width;
    int img_height;
    int img_width_resize;
    int img_height_resize;
    int label_w;
    int label_h;
    float img_per;
    Mat matImg, matImgCopy, matImgSrc;

};

#endif
