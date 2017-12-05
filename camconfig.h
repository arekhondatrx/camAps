#ifndef CAMCONFIG_H
#define CAMCONFIG_H

#include <QDialog>
#include <iostream>
#include "writetofile.h"


using namespace std;

namespace Ui {
class camConfig;
}

class camConfig : public QDialog
{
    Q_OBJECT

public:
    explicit camConfig(QWidget *parent = 0);
    ~camConfig();

private slots:
    void on_cancel_clicked();
    void on_pushButton_clicked();
    void on_saveB_clicked();
    void on_camList_textChanged();

public:
    void getCamList();

private:
    Ui::camConfig *ui;
    string addres;
    string login;
    string pass;
    string port;
};

#endif // CAMCONFIG_H
