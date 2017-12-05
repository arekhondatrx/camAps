#include "reopencam.h"
#include <QDebug>

ReOpenCam::ReOpenCam(QObject *parent) : QThread(parent)
{
    reOpe = false;
    whileTrue = true;
}
void ReOpenCam::run()
{
    while (whileTrue == true)
    {
        if(reOpe == true)
        {
            try
            {
                cap->open(adr.toUtf8().constData());
                reOpe = false;
                whileTrue = false;

            }
            catch(cv::Exception e)
            {
                qDebug()<< "Bład"  << e.what();
            }
        qDebug() << "reopenowałem";
        }
        msleep(1);
    }
}

void ReOpenCam::openCam(VideoCapture *cap, QString adr)
{
    this->cap = cap;
    this->adr = adr;
    reOpe = true;
}

void ReOpenCam::setWhileTrue(bool value)
{
    whileTrue = value;
}
