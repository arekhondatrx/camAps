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
    void getDirectory(); // pobiera lokalizacje folderu skad maja byc pobierane zdjecia
    bool showImage(QLabel *); // pokazuje obraz
    int checkType(); // sprawdza czy obraz jest typu jpg
    void setUi(Ui::MainWindow *ui); // setter
    void putRect(QLabel *label,int rect_x, int rect_y, int rect_w, int rect_h); // wrzuca prostakat na zdjecie
    void photoResize(QLabel *label,int rect_x, int rect_y, int rect_w, int rect_h); // zmienia obraz obrazu
    void photoResize2(QLabel *label,float perc);
    void clearRect(); // czysci prostakat z obrazu
    void incCntr(); //inkrementacja iteratora
    void decCntr(); // deinkrementacja iteratora
    void fillPoz(QLabel *, int *,int *);   // dopasowuje zmienne do rozmiaru QLabel
    void roateR(); // obraca obraz w Prawo
    void roateL(); // obraza obraz w lewo
    void rt(Mat& src,int angle); // funkcja pomocnicza do obrazania
    void rt(int angle);
    void show(QLabel * label); // wyswietla aktualny matImg

    // setters and getters
    int getAngle() const;
    void setAngle(int value);
    void setMatImgCopy(const Mat &value);
    void setAngleR(int value);
    void setAngleL(int value);
    float getImg_per() const;
    int getImg_width_resize() const;
    int getImg_height_resize() const;
    int getImageWidth();
    int getImageHeight();
    string getName();
    Mat getMatImg() const;
    void setMatImg(const Mat &value);
    void checkSize(QLabel *label);
    void setPathh(const QString &value);

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
