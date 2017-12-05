#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include <QLabel>


class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void keyPressEvent(QKeyEvent *ev);

    void leaveEvent(QEvent *);

public:
    int x,y;

signals:
    void Mouse_Double_Pressed();
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();
    void Mouse_Relase();
    void Key_Is_Pressed();

public slots:

};

#endif // MY_QLABEL_H
