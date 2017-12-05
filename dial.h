#ifndef DIAL_H
#define DIAL_H

#include <QDialog>
#include "ui_mainwindow.h"
#include <QTimer>
#include "getframe.h"
#include <QList>

namespace Ui {
class dial;
}

class dial : public QDialog
{
    Q_OBJECT

public:
    explicit dial(QWidget *parent = 0);
    ~dial();

    void SetUi(Ui::MainWindow *p);

public:
    bool getLabel_1_on() const;
    void setLabel_1_on(bool value);
    bool getLabel_2_on() const;
    void setLabel_2_on(bool value);
    bool getLabel_3_on() const;
    void setLabel_3_on(bool value);
    bool getLabel_4_on() const;
    void setLabel_4_on(bool value);
    list<GetFrame>::iterator getV4x4_1() const;
    void setV4x4_1(const list<GetFrame>::iterator &value);
    list<GetFrame>::iterator getV4x4_2() const;
    void setV4x4_2(const list<GetFrame>::iterator &value);
    list<GetFrame>::iterator getV4x4_3() const;
    void setV4x4_3(const list<GetFrame>::iterator &value);
    list<GetFrame>::iterator getV4x4_4() const;
    void setV4x4_4(const list<GetFrame>::iterator &value);

private slots:
    void on_l_1_clicked();
    void on_l_2_clicked();
    void on_l_3_clicked();
    void on_l_4_clicked();
    void on_l_5_clicked();

private:
    Ui::dial *ui;
    Ui::MainWindow *wsk_UI;
    QTimer *timer;
    bool label_1_on;
    bool label_2_on;
    bool label_3_on;
    bool label_4_on;
    list<GetFrame>::iterator v4x4_1, v4x4_2, v4x4_3, v4x4_4;

};

#endif // DIAL_H
