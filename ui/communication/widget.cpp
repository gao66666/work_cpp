#include "widget.h"
#include "ui_widget.h"
#include<QGraphicsDropShadowEffect>
#include<QPainterPath>
#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{



    ui->setupUi(this);
    //QMovie *movie = new QMovie(":/src_pic/bg2.gif");
    // ui->label_2->resize(300,300);
    //ui->label_2->setMovie(movie);
    //movie->start();



}

Widget::~Widget()
{
    delete ui;
}
// void Widget::paintEvent(QPaintEvent *event)
// {
//     Q_UNUSED(event);

//     QPainter painter;
//     painter.begin(this);

//     painter.setRenderHints(QPainter::Antialiasing,true);
//     QPixmap pixmap(":/src_pic/QQ.jpg");
//     QPainterPath path;
//     path.addEllipse(140,50,90,90);//加入一个圆形   绘图是从左上角的（56，20）坐标开始绘制的  ，120，120是绘图的宽高
//     painter.setClipPath(path);
//     painter.drawPixmap(QRect(140,50,90,90),pixmap);
//     painter.end();
// }
