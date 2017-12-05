#ifndef CAMCOLLECTION_H
#define CAMCOLLECTION_H
#include <list>
#include <iostream>
#include "getframe.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QString>
#include <QMessageBox>

#define ITS_LOCAL_CAM 0
#define ITS_IP_CAM 1
#define FROM_CHAR_TO_INT 48
#define ATTEMP 1

using namespace std;


class CamCollection
{
    static int amount_of_cam;
    static int max_W,max_H;

public:
    CamCollection();
    ~CamCollection();

public:
    void initialize(string);
    bool addCamLocal(int);
    bool addCamIP(string);
    Mat getViewFromCam(list<GetFrame>::iterator, bool, int = 0, int = 0);
    void setMainViewIT(int);
    void msg(QString s);

private:
    int isUSB_cam(string);
    int localCamNr(string adr);

public:
    list<GetFrame> cams;
    list<GetFrame>::iterator main_view, it_read, it_muli_vindow;
    bool all_cams_ready;

    static int getAmount_of_cam();

    void setMain_view(const list<GetFrame>::iterator &value);

private:
    fstream file;
    string cam_adr;


};

#endif // CAMCOLLECTION_H
