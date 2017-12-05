#include "camconfig.h"
#include "ui_camconfig.h"
#include <fstream>
#include <QDebug>

camConfig::camConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::camConfig)
{
    ui->setupUi(this);
    getCamList();
}

camConfig::~camConfig()
{
    delete ui;
}

void camConfig::on_cancel_clicked()
{
    this->close();
}

void camConfig::on_pushButton_clicked()
{
    addres = ui->addresEdit->text().toUtf8().constData();
    login = ui->loginEdit->text().toUtf8().constData();
    pass = ui->passEdit->text().toUtf8().constData();
    port = ui->portEdit->text().toUtf8().constData();

    string temp = "rtsp://" + login + ":" + pass + "@" + addres + ":" + port + "/Streaming/Channels/1";
    ui->textEdit->append(QString::fromStdString(temp));
}

void camConfig::getCamList()
{
    fstream file;
    file.open("config\\c.txt", ios::in);

    if(file.good() == true)
    {
        string data;
        while (getline(file,data))
        {
            ui->textEdit->append(QString::fromStdString(data));
        }
    }
    file.close();
}

void camConfig::on_saveB_clicked()
{
    WriteToFile w("config/c.txt");

    QString data = ui->textEdit->toPlainText();
    w.clear();
    w.append(data.toUtf8().constData());
    qDebug() << data.toUtf8().constData();
}

void camConfig::on_camList_textChanged()
{


}
