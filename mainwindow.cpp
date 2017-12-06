#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_qlabel.h"

#include <QString>
#include <QDebug>
#include <QMouseEvent>

#include <stdio.h>

#define SMALL_CAM_WIDTH 90
#define SMALL_CAM_HEIGHT 74
#define TIME_SAVE_INFO_VIEW 9
#define LABEL_WIDTH 995
#define LABEL_HEIGHT 705



using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), img_loc("save\\")// tu bd trzeba zmienic
{
    incrase_width = SMALL_CAM_WIDTH;
    cams.initialize("config/c.txt");

  // cams.addCam("rtsp://admin:admin@10.10.110.3:554/Streaming/Channels/1");
  // cams.addCam(0);


    ui->setupUi(this);

    connect(ui->label, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos())); // obsługa pozycji na etykecie label (główny ekran wyświetlający)
    connect(ui->label_cams, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos_cams()));// obsługa pozycji na etykecie label_cams (podgląd małych kamer)
    connect(ui->label, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed())); // obsługa wcisniecia na etykiete label
    connect(ui->label_cams, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed_cams())); // obsługa wcisniecia na etykiete label_cams
    connect(ui->label, SIGNAL(Mouse_Double_Pressed()), this, SLOT(Mouse_D_Pressed()));// obsługa podwójnego wciśniecia na głównym widoku
    connect(ui->label, SIGNAL(Mouse_Relase()), this, SLOT(Mouse_current_Relase()));// obsługa puszczenia myszy


    timer = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(updatePicture()));    
    connect(timer3,SIGNAL(timeout()),this,SLOT(updateSaveInfoView()));
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePicture4x4()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(updateLabelCams()));

    timer->start(25);
    timer2->start(2);
    timer3->start(250);

    photo.setUi(ui);
    initializeVariable();

}

MainWindow::~MainWindow()
{
    deleteFileInFolder("temp");
    delete ui;
}



void MainWindow::S_is_pressed()
{
    Mouse_D_Pressed();
}


void MainWindow::initializeVariable()
{
    rect_x = 0;
    rect_y = 0;
    rect_w = 0;
    rect_h = 0;
    click = 0;
    initial_x_size = LABEL_WIDTH;
    initial_y_size = LABEL_HEIGHT;
    perc_reszie = 0;
    save_info_cntr = TIME_SAVE_INFO_VIEW;
    l4x4 = false;
    l4x4_1 = false;
    l4x4_2 = false;
    l4x4_3 = false;
    l4x4_4 = false;
    open_image = false;
    re_size = false;
    dialog = new dial(this);
    dialog->SetUi(ui);
    cams.main_view = cams.cams.begin();
    stop_c = false;
    photo.checkSize(ui->label);
    videoPhoto.checkSize(ui->label);
    ui->scrollArea_2->setWidgetResizable(true);
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == 's' || ev->key() == 'S')
        Mouse_D_Pressed();
}

void MainWindow::wheelEvent(QWheelEvent *ev)
{
    if(open_image && ui->radioButtonPic->isChecked())
    {
        if(ev->delta() > 0)
            perc_reszie += 0.05;
        if(ev->delta() < 0)
            perc_reszie -= 0.05;

        photo.clearRect();
        photo.photoResize2(ui->label,perc_reszie);
        photo.rt(photo.getAngle());
        photo.show(ui->label);
        photo.checkSize(ui->label);

        ui->picture_size_3->setText(QString::number(photo.getImg_per()) + " %");
        QString temp = QString::number(photo.getImg_width_resize()) + " x " + QString::number(photo.getImg_height_resize()) + " pix";
        ui->picture_size_2->setText(temp);
    }

    if(ui->radioButtonVideo->isChecked() == true && stop_c == true && start_c == false)
    {
        if(ev->delta() > 0)
            perc_reszie += 0.05;
        if(ev->delta() < 0)
            perc_reszie -= 0.05;       

        videoPhoto.clearRect();
        videoPhoto.photoResize2(ui->label,perc_reszie);
        videoPhoto.rt(videoPhoto.getAngle());
        videoPhoto.show(ui->label);
        videoPhoto.checkSize(ui->label);

        ui->picture_size_3->setText(QString::number(videoPhoto.getImg_per()) + " %");
        QString temp = QString::number(videoPhoto.getImg_width_resize()) + " x " + QString::number(videoPhoto.getImg_height_resize()) + " pix";
        ui->picture_size_2->setText(temp);

    }
}

// ustalanie aktulanej pozycji myszy na etykiecie z widokiem głownym
void MainWindow::Mouse_current_pos()
{
    ui->pozycjaMyszy->setText(QString("X = %1, Y = %2").arg(ui->label->x).arg(ui->label->y));

   rect_x = ui->label->x;
   rect_y = ui->label->y;

   if(rect_x + rect_w  >= ui->label->width())
      rect_x = ui->label->width() - rect_w - 3;

   if(rect_y + rect_h  >= ui->label->height())
      rect_y = ui->label->height() - rect_h - 4;

}

// ustalanie aktulanej pozycji myszy na etykiecie z podgladem kamer
void MainWindow::Mouse_current_pos_cams()
{
    cams_pos_x = ui->label_cams->x;
    cams_pos_y = ui->label_cams->y;
}
// obsługa zdarzenia jednokrotnego wcisniecia na widok główny
void MainWindow::Mouse_Pressed()
{

}

// obsługa zdarzenia puszczenia przycisku myszy
void MainWindow::Mouse_current_Relase()
{

}

// obsługa zdarzenia jednokrotnego wcisniecia na etykiete podgladu kamer
void MainWindow::Mouse_Pressed_cams()
{
    if(start_c)
    {
        cams_pos_x /= SMALL_CAM_WIDTH;
        cams.setMainViewIT(cams_pos_x);
        qDebug() << cams_pos_x;

        if(ui->tab_2->isVisible())
        {
            dialog->show();
            l4x4 = true;
        }
    }
}

// obsługa zdarzenie dwukrotnego klikniecia na widok główny, tutaj zapisywany jest wycinek
void MainWindow::Mouse_D_Pressed()
{
    if(ui->radioButtonVideo->isChecked())
    {
        if(start_c)
        {
            SavePic saver(cams.main_view->cntr, cams.main_view->getOldFrame());
            updatePicture();
            saver.save(rect_x, rect_y, rect_w, rect_h, img_loc_t);
        }
        else
        {
            videoPhoto.clearRect();
            SavePic saver(cams.main_view->cntr, videoPhoto.getMatImg());
            videoPhoto.fillPoz(ui->label,&rect_x,&rect_y);
            saver.save(rect_x, rect_y, rect_w, rect_h, img_loc_t);
            rect_x = ui->label->x;
            rect_y = ui->label->y;
        }
    }
    else if(ui->radioButtonPic->isChecked())
    {
        SavePic saver(photo.getMatImg());
        photo.fillPoz(ui->label,&rect_x,&rect_y);
        saver.saveP(rect_x, rect_y, rect_w, rect_h, img_loc_t + photo.getName());
        rect_x = ui->label->x;
        rect_y = ui->label->y;
    }
    ui->zdarzenieMyszy->setText("Zapsiano wycinek");
    save_info_cntr = 0;
}



// uaktualnianie wyświetlanego obrazu na widoku głównym
void MainWindow::updatePicture()
{
    if(ui->label->width() > 995 || ui->label->height() > 705)
    {
        ui->label->resize(initial_x_size,initial_y_size);
    }

    if(cams.getAmount_of_cam() < 1)
    {
        ui->radioButtonPic->setChecked(true);
        ui->radioButtonVideo->setEnabled(false);
        ui->openPhoto->setEnabled(true);
    }

    if(ui->radioButtonVideo->isChecked())
    {
        if(start_c)
        {
            cams.main_view->resizePic(ui->label->width() - 2, ui->label->height() - 3);
            cams.main_view->putFrame(cams.getViewFromCam(cams.main_view, false)); // <- zapis do bufora
            show_pic = cams.getViewFromCam(cams.main_view, false).clone();
            cams.main_view->putRect(show_pic,rect_x, rect_y, rect_w, rect_h);

            ui->picture_size_3->setText("100 %");
            QString temp = QString::number((ui->label->width())) + " x " + QString::number((ui->label->height())) + " pix";
            ui->picture_size_2->setText(temp);
            ui->picture_size->setText(temp);

            if(!show_pic.empty())
                showCapture(show_pic);
         }
        else
        {
            show_pic = cams.main_view->getOldFrame().clone();
            videoPhoto.setMatImg(show_pic);
            videoPhoto.clearRect();
            videoPhoto.putRect(ui->label,rect_x,rect_y,rect_w,rect_h);
        }
    }
    else if(ui->radioButtonPic->isChecked())
    {
        if(open_image)
        {

            photo.clearRect();
            photo.putRect(ui->label,rect_x,rect_y,rect_w,rect_h);
            QString size_info;
            size_info = QString::number(photo.getImageWidth()) + "x" + QString::number(photo.getImageHeight()) + " pix";
            ui->picture_size->setText(size_info);
        }
    }
}


void MainWindow::updateSaveInfoView()
{
    save_info_cntr++;
    if(save_info_cntr > TIME_SAVE_INFO_VIEW)
    {
        ui->zdarzenieMyszy->setText("");
    }

    if(save_info_cntr > 2000)
    {
        save_info_cntr = TIME_SAVE_INFO_VIEW + 1;
    }
}

// aktualizacja widoku kamer 4x4
void MainWindow::updatePicture4x4()
{
    if(dialog->getLabel_1_on() == true)
    {
        l4x4_1 = true;
        dialog->setLabel_1_on(false);
        v4x4_1 = cams.main_view;
    }

    if(dialog->getLabel_2_on() == true)
    {
        l4x4_2 = true;
        dialog->setLabel_2_on(false);
        v4x4_2 = cams.main_view;
    }
    if(dialog->getLabel_3_on() == true)
    {
        l4x4_3 = true;
        dialog->setLabel_3_on(false);
        v4x4_3 = cams.main_view;
    }

    if(dialog->getLabel_4_on() == true)
    {
        l4x4_4 = true;
        dialog->setLabel_4_on(false);
        v4x4_4 = cams.main_view;
    }


    if(l4x4)
    {
         if(l4x4_1 == true)
        {
            cams.it_muli_vindow = v4x4_1;
            updatePicture4x4helper(ui->label4x4_1, v4x4_1);
         }
         if(l4x4_2 == true)
        {
             cams.it_muli_vindow = v4x4_2;
             updatePicture4x4helper(ui->label4x4_2, v4x4_2);
         }
         if(l4x4_3 == true)
        {
             cams.it_muli_vindow = v4x4_3;
             updatePicture4x4helper(ui->label4x4_3, v4x4_3);
         }
         if(l4x4_4 == true)
         {
             cams.it_muli_vindow = v4x4_4;
             updatePicture4x4helper(ui->label4x4_4, v4x4_4);
         }
    }
}



// funkcja pomocnicza do uaktualniania widoku 4x4
void MainWindow::updatePicture4x4helper(QLabel *l, list<GetFrame>::iterator iter)
{
    show_pic = cams.getViewFromCam(iter, true,l->width() - 2, l->height() - 3).clone();
    showCapture(show_pic, l);
}

// aktualizacja widoku podglądu kamer
void MainWindow::updateLabelCams()
{
    if(cams.getAmount_of_cam() > 0 && cams.all_cams_ready)
    {
            incrase_width = 0;
            show_cams = new Mat;

            for(cams.it_read = cams.cams.begin(); std::distance(cams.it_read, cams.cams.end()) > 0 ; cams.it_read++)
            {
                incrase_width += SMALL_CAM_WIDTH;
                cams.it_read->getCapture();
                small_pic_a = cams.it_read->getSmallPic(SMALL_CAM_WIDTH, ui->label_cams->height() - 2);

                if(show_cams->empty())
                {
                    (*show_cams) = small_pic_a.clone();
                }
                else
                {
                    hconcat((*show_cams), small_pic_a, (*show_cams));
                }
            }

        QImage image1 = QImage((uchar*) show_cams->data, show_cams->cols, show_cams->rows, show_cams->step, QImage::Format_RGB888);
        ui->label_cams->resize(incrase_width, ui->label_cams->height());
        ui->label_cams->setPixmap(QPixmap::fromImage(image1));
        delete show_cams;
    }
}

// ustawienie rozmiaru wycinanego odcianka na 256 x 128
void MainWindow::on_get256_clicked()
{
    if(ui->get256->isChecked())
    {
        ui->get32->setChecked(false);
        ui->get64->setChecked(false);
        ui->get128->setChecked(false);
        ui->get128_64->setChecked(false);
        ui->get256_2->setChecked(false);
        ui->get128_65->setChecked(false);
        rect_w = 128;
        rect_h = 256;

        img_loc_t = img_loc;
        img_loc_t += "256 x 128\\";
    }
    else
    {
        rect_w = 0;
        rect_h = 0;
    }
}

// ustawienie rozmiaru wycinanego odcianka na 128 x 128
void MainWindow::on_get128_clicked()
{
    if(ui->get128->isChecked())
    {
        ui->get32->setChecked(false);
        ui->get64->setChecked(false);
        ui->get256->setChecked(false);
        ui->get128_64->setChecked(false);
        ui->get256_2->setChecked(false);
        ui->get128_65->setChecked(false);
        rect_w = 128;
        rect_h = 128;

        img_loc_t = img_loc;
        img_loc_t += "128 x 128\\";
    }
    else
    {
        rect_w = 0;
        rect_h = 0;
    }
}


void MainWindow::on_get256_2_clicked()
{
    if(ui->get256_2->isChecked())
    {
        ui->get32->setChecked(false);
        ui->get64->setChecked(false);
        ui->get128->setChecked(false);
        ui->get256->setChecked(false);
        ui->get128_65->setChecked(false);
        ui->get128_64->setChecked(false);
        rect_w = 256;
        rect_h = 128;

        img_loc_t = img_loc;
        img_loc_t += "128 x 256\\";
    }
    else
    {
        rect_w = 0;
        rect_h = 0;
    }
}

void MainWindow::on_get128_65_clicked()
{
    if(ui->get128_65->isChecked())
    {
        ui->get32->setChecked(false);
        ui->get64->setChecked(false);
        ui->get128->setChecked(false);
        ui->get256->setChecked(false);
        ui->get256_2->setChecked(false);
        ui->get128_64->setChecked(false);
        rect_w = 128;
        rect_h = 64;

        img_loc_t = img_loc;
        img_loc_t += "64 x 128\\";
    }
    else
    {
        rect_w = 0;
        rect_h = 0;
    }
}


void MainWindow::on_get128_64_clicked()
{
    if(ui->get128_64->isChecked())
    {
        ui->get32->setChecked(false);
        ui->get64->setChecked(false);
        ui->get128->setChecked(false);
        ui->get256->setChecked(false);
        ui->get128_65->setChecked(false);
        rect_w = 64;
        rect_h = 128;

        img_loc_t = img_loc;
        img_loc_t += "128 x 64\\";
    }
    else
    {
        rect_w = 0;
        rect_h = 0;
    }
}

// ustawienie rozmiaru wycinanego odcianka na 64 x 64
void MainWindow::on_get64_clicked()
{
    if(ui->get64->isChecked())
    {
        ui->get32->setChecked(false);
        ui->get256->setChecked(false);
        ui->get128->setChecked(false);
        ui->get128_64->setChecked(false);
        ui->get256_2->setChecked(false);
        ui->get128_65->setChecked(false);
        rect_w = 64;
        rect_h = 64;

        img_loc_t = img_loc;
        img_loc_t += "64 x 64\\";
    }
    else
    {
        rect_w = 0;
        rect_h = 0;
    }
}

// ustawienie rozmiaru wycinanego odcianka na 32 x 32
void MainWindow::on_get32_clicked()
{
    if(ui->get32->isChecked())
    {
        ui->get256->setChecked(false);
        ui->get64->setChecked(false);
        ui->get128->setChecked(false);
        ui->get128_64->setChecked(false);
        ui->get256_2->setChecked(false);
        ui->get128_65->setChecked(false);
        rect_w = 32;
        rect_h = 32;

        img_loc_t = img_loc;
        img_loc_t += "32 x 32\\";
    }
    else
    {
        rect_w = 0;
        rect_h = 0;
    }
}

// rozpoczęcie zapisu do bufora
void MainWindow::on_start_b_clicked()
{
    start_c = true;
    stop_c = false;
    back_c = false;
    next_c = false;
    ui->start_b->setEnabled(false);
    ui->stop_b->setEnabled(true);
    ui->rotate_l->setEnabled(false);
    ui->rotate_r->setEnabled(false);
    ui->label->resize(initial_x_size,initial_y_size);
    restScroll();
}

// zatrzymanie zapisu do bufora
void MainWindow::on_stop_b_clicked()
{
    start_c = false;
    stop_c = true;
    back_c = false;
    next_c = false;
    ui->start_b->setEnabled(true);
    ui->stop_b->setEnabled(false);
    ui->rotate_l->setEnabled(true);
    ui->rotate_r->setEnabled(true);
    videoPhoto.setAngleR(0);
    videoPhoto.setAngleL(0);
    restScroll();
    videoPhoto.setMatImgCopy(cams.main_view->getOldFrame());   
}

// cofniecie klatki o 1 lub zaladowanie poprzedniego zdjecia
void MainWindow::on_back_b_clicked()
{
    restScroll();
    if(ui->radioButtonVideo->isChecked())
    {
        cams.main_view->decIterator();
        showCapture(cams.main_view->getOldFrame());
        videoPhoto.setMatImgCopy(cams.main_view->getOldFrame());
    }
    else if(ui->radioButtonPic->isChecked())
    {
        photo.decCntr();
        open_image =  photo.showImage(ui->label);
        restScroll();
    }
}

// cofniecie klatki o 5 lub zaladowanie zdjecia 5 wstecz
void MainWindow::on_back_b_2_clicked()
{
    restScroll();
    if(ui->radioButtonVideo->isChecked())
    {
        for(int i = 0; i<5; i++)
        {
           cams.main_view->decIterator();
        }
       showCapture(cams.main_view->getOldFrame());
       videoPhoto.setMatImgCopy(cams.main_view->getOldFrame());
    }
    else if(ui->radioButtonPic->isChecked())
    {
        for(int i = 0; i<5; i++)
        {
           photo.decCntr();
        }
        open_image = photo.showImage(ui->label);
        restScroll();
    }
}

//  wyswietlenie następnej klatki lub zaladowanie nastepnego zdjecia
void MainWindow::on_next_b_clicked()
{
    restScroll();
    if(ui->radioButtonVideo->isChecked() == true && start_c == false)
    {
        videoPhoto.setMatImgCopy(cams.main_view->getOldFrame());
        cams.main_view->incIterator();
        showCapture(cams.main_view->getOldFrame());
    }
    else if(ui->radioButtonPic->isChecked())
    {
        photo.incCntr();
        open_image = photo.showImage(ui->label);
        restScroll();
    }
}

// wyswietlenie 5 nastepnej kaltki lub 5 nastepnego zdjecia
void MainWindow::on_next_b_2_clicked()
{
    restScroll();
    if(ui->radioButtonVideo->isChecked() == true && start_c == false)
    {
        for(int i = 0; i<5; i++)
        {
           cams.main_view->incIterator();
        }
        showCapture(cams.main_view->getOldFrame());
        videoPhoto.setMatImgCopy(cams.main_view->getOldFrame());
    }
    else if(ui->radioButtonPic->isChecked())
    {
        for(int i = 0; i<5; i++)
        {
           photo.incCntr();
        }
        open_image = photo.showImage(ui->label);
        restScroll();
    }
}

// otwiera okno do konfiguracji kamery
void MainWindow::on_configCam_clicked()
{
    camConfig c_conf;
    c_conf.setModal(true);
    c_conf.exec();
}

// ustawienie wyswietlania na widok z kamer
void MainWindow::on_radioButtonVideo_clicked()
{
    if(ui->radioButtonVideo->isChecked())
    {
        ui->radioButtonPic->setChecked(false);
        ui->openPhoto->setEnabled(false);

        if(start_c)
        {
            ui->rotate_l->setEnabled(false);
            ui->rotate_r->setEnabled(false);
        }
    }
}

// ustawienie wyswietlania na przegladarke zdjec
void MainWindow::on_radioButtonPic_clicked()
{
    if(ui->radioButtonPic->isChecked())
    {
        ui->radioButtonVideo->setChecked(false);
        ui->openPhoto->setEnabled(true);
        ui->rotate_l->setEnabled(true);
        ui->rotate_r->setEnabled(true);
    }
}

// otwieranie folderu zapisu
void MainWindow::on_openSaveB_clicked()
{
    QString adr = "save";
    QDesktopServices::openUrl(adr);
}

// wybor folderu skad maja zostac zaladowane zdjecia
void MainWindow::on_openPhoto_clicked()
{
   photo.getDirectory();
   open_image = photo.showImage(ui->label);
   restScroll();
}

// obrót obrazu
void MainWindow::on_rotate_r_clicked()
{
    restScroll();
    if(ui->radioButtonPic->isChecked())
    {
        photo.checkSize(ui->label);
        photo.photoResize2(ui->label,perc_reszie);
        photo.roateR();
        photo.show(ui->label);        
    }

    if(ui->radioButtonVideo->isChecked() && !start_c)
    {
        videoPhoto.checkSize(ui->label);
        videoPhoto.photoResize2(ui->label,perc_reszie);
        videoPhoto.roateR();
        videoPhoto.show(ui->label);
    }
}

void MainWindow::on_rotate_l_clicked()
{
    restScroll();
    if(ui->radioButtonPic->isChecked())
    {
        photo.checkSize(ui->label);
        photo.photoResize2(ui->label,perc_reszie);
        photo.roateL();
        photo.show(ui->label);
    }

    if(ui->radioButtonVideo->isChecked() && !start_c)
    {
        videoPhoto.checkSize(ui->label);
        videoPhoto.photoResize2(ui->label,perc_reszie);
        videoPhoto.roateL();
        videoPhoto.show(ui->label);
    }
}


// funkcja do wyswietlania MAT
void MainWindow::showCapture(Mat t)
{
    QImage image1 = QImage((uchar*) t.data,  t.cols,  t.rows,  t.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image1));
}

// funkcja do wyswietlania MAT
void MainWindow::showCapture(Mat t, QLabel * l)
{
    if(t.empty())
    {
        Mat tmp(480, 640, CV_8UC3, Scalar(250, 0, 0));
        putText(tmp, "Error!!", cvPoint(480 * 0.3,640 * 0.4),FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
        t = tmp.clone();
    }
    QImage image1 = QImage((uchar*) t.data,  t.cols,  t.rows,  t.step, QImage::Format_RGB888);
    l->setPixmap(QPixmap::fromImage(image1));
}

// usówanie plików w folderze
void MainWindow::deleteFileInFolder(QString path)
{
    QDir dir(path);
    qDebug() << path;
    foreach(QString dirFile, dir.entryList())
    {
        qDebug() << dirFile;
        if(dirFile[0] == 'c')
        {
            qDebug() << path + "/" + dirFile;
            deleteFileInFolder(path + "/" + dirFile);
        }
        dir.remove(dirFile);
    }
}




void MainWindow::restScroll()
{
    perc_reszie = 0;
    videoPhoto.setAngle(0);

    if(open_image)
    {
        ui->picture_size_2->setText(QString::number(photo.getImageHeight()) + " x " + QString::number(photo.getImageWidth()) + " pix");
        ui->picture_size_3->setText("100 %");
        photo.setAngle(0);
    }
}
