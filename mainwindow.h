#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <QTimer>
#include <QString>
#include <QStringList>
#include <QKeyEvent>
#include <QDir>
#include <QFileDialog>
#include <QDesktopServices>
#include <QThread>
#include <QWheelEvent>
#include "camcollection.h"
#include "getframe.h"
#include "savepic.h"
#include "photoviewer.h"
#include "dial.h"
#include "camconfig.h"
#include "reopencam.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread mThread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void oCam(VideoCapture *, QString);

private slots:
    void S_is_pressed();
    void on_configCam_clicked();
    void Mouse_current_pos();
    void Mouse_current_pos_cams();
    void Mouse_Pressed();
    void Mouse_current_Relase();
    void Mouse_Pressed_cams();
    void Mouse_D_Pressed();
    void updatePicture();

    void updateSaveInfoView();
    void updatePicture4x4();
    void updatePicture4x4helper(QLabel *, list<GetFrame>::iterator);
    void updateLabelCams();
    void on_get64_clicked();
    void on_get32_clicked();
    void on_start_b_clicked();
    void on_stop_b_clicked();
    void on_next_b_2_clicked();
    void on_back_b_clicked();
    void on_next_b_clicked();
    void on_get256_clicked();
    void on_get128_clicked();
    void on_get128_64_clicked();
    void on_radioButtonVideo_clicked();
    void on_radioButtonPic_clicked();
    void on_openSaveB_clicked();
    void on_back_b_2_clicked();
    void on_openPhoto_clicked();
    void on_rotate_r_clicked();
    void on_rotate_l_clicked();
    void on_get256_2_clicked();
    void on_get128_65_clicked();

public:
   void showCapture(Mat); // wyswietla obraz na Label
   void showCapture(Mat, QLabel *);// wyswietla obraz na podanym Label
   void deleteFileInFolder(QString); // usuwa folder
   void initializeVariable(); // ustawianie zmiennych
   void restScroll(); // resetuje niektóre zmienne po użyciu scrolla
   void keyPressEvent(QKeyEvent *ev); // obsługa wsisniecia klawiatury
   void wheelEvent(QWheelEvent *ev); // obsługa scrolla

public:
    CamCollection cams;
    QTimer *timer, *timer2, *timer3;
    PhotoViewer photo;
    PhotoViewer videoPhoto;
    dial *dialog;

    int save_info_cntr;
    float perc_reszie;

// main cam window //
    int rect_x;
    int rect_y;
    int rect_w;
    int rect_h;
 // label_cams_window //
    int cams_pos_x;
    int cams_pos_y;
    int initial_x_size;
    int initial_y_size;
    int offset;
    int incrase_width;
    Mat *show_cams;
    Mat r_pic;
    Mat small_pic_a;

// custom size rect //
    int click;
    int temp_rect_x;
    int temp_rect_y;
    int a_size,b_size;

// strat, stop, flags //

    bool re_size;
    bool start_c;
    bool stop_c;
    bool back_c;
    bool next_c;
    bool l4x4;
    bool l4x4_1;
    bool l4x4_2;
    bool l4x4_3;
    bool l4x4_4;
    bool mouse_p;
    bool open_image;

    std::string img_name;
    std::string img_loc;
    std::string img_loc_t;
    std::string photo_loc;

    Mat show_pic;

    list<GetFrame>::iterator v4x4_1, v4x4_2, v4x4_3, v4x4_4;



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
