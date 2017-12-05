#ifndef REOPENCAM_H
#define REOPENCAM_H

#include <QtCore>
#include <QDebug>
#include <QThread>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QString>

using namespace cv;

class ReOpenCam : public QThread
{
    Q_OBJECT
public:
    explicit ReOpenCam(QObject *parent = NULL);
    void run();
    void setWhileTrue(bool value);

signals:

public slots:
    void openCam(VideoCapture *, QString);

private:
    VideoCapture *cap;
    QString adr;
    bool reOpe;
    bool whileTrue;
};

#endif // REOPENCAM_H
