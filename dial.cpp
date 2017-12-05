#include "dial.h"
#include "ui_dial.h"

dial::dial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dial)
{
    ui->setupUi(this);

    label_1_on = false;
    label_2_on = false;
    label_3_on = false;
    label_4_on = false;
}

dial::~dial()
{
    delete ui;
}

void dial::SetUi(Ui::MainWindow *p)
{
    wsk_UI = p;
}

void dial::on_l_1_clicked()
{
    label_1_on = true;
    this->close();
}

void dial::on_l_2_clicked()
{
    label_2_on = true;
    this->close();
}

void dial::on_l_3_clicked()
{
    label_3_on = true;
    this->close();
}

void dial::on_l_4_clicked()
{
    label_4_on = true;
    this->close();
}

void dial::on_l_5_clicked()
{
    this->close();
}

list<GetFrame>::iterator dial::getV4x4_4() const
{
    return v4x4_4;
}

void dial::setV4x4_4(const list<GetFrame>::iterator &value)
{
    v4x4_4 = value;
}

list<GetFrame>::iterator dial::getV4x4_3() const
{
    return v4x4_3;
}

void dial::setV4x4_3(const list<GetFrame>::iterator &value)
{
    v4x4_3 = value;
}

list<GetFrame>::iterator dial::getV4x4_2() const
{
    return v4x4_2;
}

void dial::setV4x4_2(const list<GetFrame>::iterator &value)
{
    v4x4_2 = value;
}

list<GetFrame>::iterator dial::getV4x4_1() const
{
    return v4x4_1;
}

void dial::setV4x4_1(const list<GetFrame>::iterator &value)
{
    v4x4_1 = value;
}

bool dial::getLabel_4_on() const
{
    return label_4_on;
}

void dial::setLabel_4_on(bool value)
{
    label_4_on = value;
}

bool dial::getLabel_3_on() const
{
    return label_3_on;
}

void dial::setLabel_3_on(bool value)
{
    label_3_on = value;
}

bool dial::getLabel_2_on() const
{
    return label_2_on;
}

void dial::setLabel_2_on(bool value)
{
    label_2_on = value;
}

bool dial::getLabel_1_on() const
{
    return label_1_on;
}

void dial::setLabel_1_on(bool value)
{
    label_1_on = value;
}

