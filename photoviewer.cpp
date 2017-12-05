#include "photoviewer.h"
#include <QDebug>

#define INCRASE_ANGLE 90

int PhotoViewer::cntr = 1;

PhotoViewer::PhotoViewer(Ui::MainWindow *ui)
{
    this->ui = ui;
    angleL = 0;
    angleR = 0;
    angle = 0;
    old_path = "save";
}

PhotoViewer::PhotoViewer()
{
    angleL = 0;
    angleR = 0;
    angle = 0;
    old_path = "save";
}

void PhotoViewer::getDirectory()
{
    cntr = 1;
    pathh = QFileDialog::getExistingDirectory(ui->centralWidget);
    if(pathh == "")
    {
        pathh = old_path;
    }
    old_path = pathh;
    ui->label->setText(pathh);
    dir.setPath(pathh);
    list = dir.entryList(QDir::AllEntries);
    list.pop_front();
}

bool PhotoViewer::showImage(QLabel *label)
{

    load_picture_loc = pathh + "/" + list.at(cntr);
    matImg = imread(load_picture_loc.toUtf8().constData());


    if(matImg.empty() == false)
    {
        cvtColor(matImg, matImg, CV_BGR2RGB);
        matImgCopy = matImg.clone();
        matImgSrc = matImg.clone();

        QImage tt = QImage((uchar*) matImg.data,  matImg.cols,  matImg.rows,  matImg.step, QImage::Format_RGB888);
        QPixmap image(QPixmap::fromImage(tt));
        img_width = image.width();
        img_height = image.height();

        if(img_width > label->width() && img_height > label->height())
         {
             image = image.scaled(label->width() - 2, label->height() - 3,  Qt::KeepAspectRatio);
         }
         label->setStyleSheet("QLabel { background-color : green; color : blue; }");
         label->setPixmap(image);
         return true;
    }
    else
        return false;
}

int PhotoViewer::checkType()
{
    int img_cntr = 0;
    for (int i = 0; i < list.size(); i++)
    {
        if(!(list.at(i).endsWith(".JPG",Qt::CaseSensitive)) || (list.at(i).endsWith(".jpg",Qt::CaseSensitive)))
        {
            list.removeAt(i);
            i--;
        }
        else
        {
            img_cntr++;
        }
    }
    return img_cntr;
}

void PhotoViewer::putRect(QLabel *label,int rect_x, int rect_y, int rect_w, int rect_h)
{    
    if(rect_x + rect_w  >= matImg.cols)
       rect_x = matImg.cols - rect_w - 1;

    if(rect_y + rect_h  >= matImg.rows)
       rect_y = matImg.rows - rect_h - 1;

    if(rect_x <= 0)
       rect_x = 1;

    if(rect_y  <= 0)
       rect_y = 1;

    rectangle(matImg,cvPoint(rect_x - 1,rect_y - 1),cvPoint(rect_x + rect_w ,rect_y + rect_h),CV_RGB(0,255,0),1,4);
    QImage tt = QImage((uchar*) matImg.data,  matImg.cols,  matImg.rows,  matImg.step, QImage::Format_RGB888);
    QPixmap image(QPixmap::fromImage(tt));
    label->setPixmap(image);
}

void PhotoViewer::photoResize(QLabel *label,int rect_x, int rect_y, int rect_w, int rect_h)
{
    fillPoz(label, &rect_x, &rect_y);
    rect_w += img_width;
    rect_h += img_height;

    if(rect_w > 2 && rect_h > 2)
    {
        if(rect_w != matImg.cols || rect_h != matImg.rows)
        {
            cv::resize(matImg, matImg, Size(rect_w,rect_h));
            cv::resize(matImg, matImgCopy, Size(rect_w,rect_h));
            img_height_resize = matImg.rows;
            img_width_resize =  matImg.cols;
        }

        if(img_width != rect_w && img_height !=rect_h)
        {
            label->setStyleSheet("QLabel { background-color : red; color : blue; }");
        }
        else
        {
            label->setStyleSheet("QLabel { background-color : green; color : blue; }");
        }
    }
    QImage tt = QImage((uchar*) matImg.data,  matImg.cols,  matImg.rows,  matImg.step, QImage::Format_RGB888);
    QPixmap image(QPixmap::fromImage(tt));
    label->setPixmap(image);
}

void PhotoViewer::photoResize2(QLabel *label,float perc)
{
    float x,y;
    x = img_width;
    y = img_height;

    if(perc >= 2)
        perc = 2;

    x = x + x * perc;
    y = y + y * perc;

    matImg = matImgSrc.clone();

    if(x > 2 && y > 2)
    {
        if(x!= matImg.cols || y != matImg.rows)
        {
            cv::resize(matImg, matImg, Size(x,y));
            cv::resize(matImg, matImgCopy, Size(x,y));

            if(matImg.rows >= label->height())
                img_height_resize = matImg.rows;
            else
                img_height_resize = matImg.rows;

            if(matImg.cols >= label->width())          
                img_width_resize =  matImg.cols ;
            else
                img_width_resize =  matImg.cols;
        }
        else
        {
            img_width_resize =  matImg.cols;
            img_height_resize = matImg.rows;
        }
    }
    label->resize(matImg.cols,matImg.rows);
    img_per = (float(img_height_resize * img_width_resize) / float(img_height * img_width) * 100);
}

void PhotoViewer::clearRect()
{
    if(matImgCopy.empty() == false)
        matImg = matImgCopy.clone();
}

void PhotoViewer::setUi(Ui::MainWindow *ui)
{
    this->ui = ui;
}

void PhotoViewer::incCntr()
{
    if(cntr < list.size() - 1)
    {
        cntr++;
    }
    else
    {
        cntr = 1;
    }
}

void PhotoViewer::decCntr()
{
    if(cntr > 1)
    {
        cntr--;
    }
    else
    {
        cntr = list.size() - 1;
    }
}

int PhotoViewer::getImageWidth()
{
    return img_width;
}


int PhotoViewer::getImageHeight()
{
    return img_height;
}

string PhotoViewer::getName()
{
    return list.at(cntr).toUtf8().constData();
}

void PhotoViewer::fillPoz(QLabel *label, int *x, int *y)
{
    int c_x, c_y;

    c_x = (label->width() / 2) - 0.5 * matImg.cols;
    c_y = (label->height() / 2) - 0.5 * matImg.rows;

    (*x) -= c_x;
    (*y) -= c_y;
}
Mat PhotoViewer::getMatImg() const
{
    return matImg;
}

void PhotoViewer::setMatImg(const Mat &value)
{
    matImg = value;
    matImgSrc = matImg.clone();
    img_height = matImg.rows;
    img_width = matImg.cols;
}

void PhotoViewer::rt(Mat& src,int angle)
{
    cv::Point2f center(src.cols / 2.0, src.rows / 2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();
    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    cv::warpAffine(src, src, rot, bbox.size());

    if(src.rows > label_h && angle != 0)
    {
       float temp_size = float(label_h) / float(src.rows);
        cv::resize(src,src,Size(src.cols * temp_size,label_h));
    }

    if(src.cols > label_w && angle != 0)
    {
       float temp_size = float(label_w) / float(src.cols);
       cv::resize(src,src,Size(label_w,src.rows * temp_size));
    }
}

void PhotoViewer::rt(int angle)
{
    cv::Point2f center(matImg.cols / 2.0, matImg.rows / 2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Rect bbox = cv::RotatedRect(center, matImg.size(), angle).boundingRect();
    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    cv::warpAffine(matImg, matImg, rot, bbox.size());

    if(matImg.rows > label_h && angle != 0)
    {
       float temp_size = float(label_h) / float(matImg.rows);
        cv::resize(matImg,matImg,Size(matImg.cols * temp_size,label_h));
    }

    if(matImg.cols > label_w && angle != 0)
    {
       float temp_size = float(label_w) / float(matImg.cols);
       cv::resize(matImg,matImg,Size(label_w,matImg.rows * temp_size));
    }
    matImgCopy = matImg.clone();
}

void PhotoViewer::show(QLabel *label)
{
    QImage tt = QImage((uchar*) matImg.data,  matImg.cols,  matImg.rows,  matImg.step, QImage::Format_RGB888);
    QPixmap image(QPixmap::fromImage(tt));
    label->setPixmap(image);
}

int PhotoViewer::getAngle() const
{
    return angle;
}

void PhotoViewer::setAngle(int value)
{
    angle = value;
}

void PhotoViewer::setMatImgCopy(const Mat &value)
{
    matImgCopy = value;
}

void PhotoViewer::setAngleR(int value)
{
    angleR = value;
}

void PhotoViewer::setAngleL(int value)
{
    angleL = value;
}

void PhotoViewer::roateR()
{
    angleR -= 90;
    angleR += angleL;
    if(angleL > 0)
    {
        angleL = 0;
    }

    if(angleR < -4 * INCRASE_ANGLE)
    {
        angleR = -INCRASE_ANGLE;
    }

   rt(matImg, angleR);
   matImgCopy = matImg.clone();
   angle = angleR;
}

void PhotoViewer::roateL()
{
    angleL += 90;
    angleL += angleR;
    if(angleR < 0)
    {
        angleR = 0;
    }

    if(angleL > 4 * INCRASE_ANGLE)
    {
        angleL = INCRASE_ANGLE;
    }

   rt(matImg, angleL);
   matImgCopy = matImg.clone();
   angle = angleL;
}

void PhotoViewer::checkSize(QLabel *label)
{
    label_h = label->height();
    label_w = label->width();
}

float PhotoViewer::getImg_per() const
{
    return img_per;
}

int PhotoViewer::getImg_width_resize() const
{
    return img_width_resize;
}

int PhotoViewer::getImg_height_resize() const
{
    return img_height_resize;
}

void PhotoViewer::setPathh(const QString &value)
{
    pathh = value;
    dir.setPath(pathh);
    list = dir.entryList(QDir::AllEntries);
    list.pop_front();
}

