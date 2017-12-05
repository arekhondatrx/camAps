#include "camcollection.h"


int CamCollection::amount_of_cam = 0;
int CamCollection::max_H = 10;
int CamCollection::max_W = 10;

CamCollection::CamCollection()
{

}

CamCollection::~CamCollection()
{

}

void CamCollection::initialize(string adr)
{
    all_cams_ready = false;
    fstream file;
    file.open(adr, ios::in);
        while(getline(file, cam_adr))
        {
            int cam_type = isUSB_cam(cam_adr);
            if(cam_type == ITS_IP_CAM)
            {
                for(int i = 0; i < ATTEMP; i++)
                {
                    if(addCamIP(cam_adr))
                        break;
                    else
                        msg("proba połączenia : " + QString::number(i));
                }

            }
            else if(cam_type == ITS_LOCAL_CAM)
            {
                for(int i = 0; i < ATTEMP; i++)
                {
                    if(addCamLocal(localCamNr(cam_adr)))
                        break;
                    else
                        msg("proba połączenia : " + QString::number(i));
                }
            }
            else
            {
                qDebug() << "nie rozpoznanao urządzenia";
            }

            list<GetFrame>::iterator it_temp = cams.begin();
            for(it_temp = cams.begin(); std::distance(it_temp, cams.end()) > 0; it_temp++ )
            {
                for(int i = 0; i < 50; i++)
                {
                    Mat temp_mat;
                    it_temp->cap >> temp_mat;
                }
            }
        }
    file.close();
    all_cams_ready = true;
}

bool CamCollection::addCamLocal(int nr)
{
    GetFrame temp;
    bool result = false;

    if(temp.setAdrCapture(nr))
    {
        cams.push_front(temp);
        temp.cam_name = "loc_cam_" + to_string(nr);
        qDebug() << QString::fromStdString(temp.cam_name);
        amount_of_cam++;
        result = true;
    }

    return result;
}

bool CamCollection::addCamIP(string adr)
{
    GetFrame temp;
    bool result = false;

    if(temp.setAdrCapture(adr))
    {
        cams.push_front(temp);
        amount_of_cam++;
        cam_adr = adr;
        result = true;
    }

    return result;
}

Mat CamCollection::getViewFromCam(list<GetFrame>::iterator iter, bool get_small_pic, int x_img_size, int y_img_size)
{
    Mat temp;

    if(get_small_pic)
    {
        temp = iter->getSmallPic(x_img_size,y_img_size);
    }
    else
    {
        temp = iter->getImg().clone();
    }

    if(temp.empty())
    {
        if(std::distance(cams.begin(), iter) < 0)
            msg("ponizej");
        if(std::distance(iter, cams.end()) < 0)
            msg("wiekszy");
    }

    if(!temp.empty())
    {
        max_H = temp.rows;
        max_W = temp.cols;
        return temp;
    }
    else
    {
        Mat tmp(max_H, max_W, CV_8UC3, Scalar(250, 0, 0));
        putText(tmp, "Error!!", cvPoint(max_H * 0.3,max_W * 0.4),FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
        return tmp;
    }

}

void CamCollection::setMainViewIT(int nr)
{
    main_view = cams.begin();
         for(int i = 0; i < nr; i++)
         {
             if(std::distance(main_view,cams.end()) > 0)
                main_view++;
             else
             {
                 msg("CamCollection::setIT po za " + QString::number(nr) + "i= " + QString::number(i) + "  "   + QString::number(std::distance(main_view,cams.end())));
             }
        }
}

void CamCollection::msg(QString s)
{
    QMessageBox m;
    m.setText(s);
    m.exec();
}

int CamCollection::isUSB_cam(string adr)
{
    if(adr.length() > 3)
    {
        return ITS_IP_CAM;
    }
    else
    {
        return ITS_LOCAL_CAM;
    }
}

int CamCollection::localCamNr(string adr)
{
    int digit;

    digit = adr[1] - FROM_CHAR_TO_INT;

    return digit;
}

int CamCollection::getAmount_of_cam()
{
    return amount_of_cam;
}
