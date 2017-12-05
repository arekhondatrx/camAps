#-------------------------------------------------
#
# Project created by QtCreator 2017-10-30T19:47:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nienazwany1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++11



SOURCES += \
        main.cpp \
        mainwindow.cpp \
    my_qlabel.cpp \
    getframe.cpp \
    camcollection.cpp \
    picframe.cpp \
    savepic.cpp \
    photoviewer.cpp \
    dial.cpp \
    camconfig.cpp \
    writetofile.cpp \
    reopencam.cpp

HEADERS += \
        mainwindow.h \
    my_qlabel.h \
    getframe.h \
    camcollection.h \
    picframe.h \
    savepic.h \
    photoviewer.h \
    dial.h \
    camconfig.h \
    writetofile.h \
    reopencam.h

FORMS += \
        mainwindow.ui \
    dial.ui \
    camconfig.ui




INCLUDEPATH += C:\openCV32\opencv\build\include

LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_calib3d320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_core320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_features2d320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_flann320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_highgui320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_imgcodecs320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_imgproc320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_ml320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_calib3d320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_stitching320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_video320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_superres320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_videoio320.dll
LIBS += C:\openCV32\opencv\buildQT\bin\libopencv_videostab320.dll
