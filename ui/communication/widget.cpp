#include "widget.h"
#include "ui_widget.h"
#include<QGraphicsDropShadowEffect>
#include<QPainterPath>
#include <QMovie>
#include<QMessageBox>
#include<QMouseEvent>


//功能函数-提示信息框
void show_message(QString t,int level){
    //level:0 代表信息,level:1 代表警告，level:2 代表错误
    QMessageBox msgBox;
    msgBox.setWindowTitle("QQ");
    msgBox.setWindowIcon(QIcon(":/src_pic/QQ.jpg"));
    if(level==0){
        msgBox.setIcon(QMessageBox::Information);
    }else if(level==1){
        msgBox.setIcon(QMessageBox::Warning);
    }else{
        msgBox.setIcon(QMessageBox::Critical);
    }
    msgBox.setText(t);
    msgBox.exec();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Widget::~Widget()
{
    delete ui;
}


//槽函数-登录按钮
void Widget::on_Button_login_clicked()
{
    QString user_id=ui->lineEdit_id->text();            //账号
    QString user_password=ui->lineEdit_password->text();//密码
    bool is_exsits=true;                               //该变量用于观察账号是否存在或者密码是否正确
                                                        //发送账号密码到服务器进行检验,然后对is_exsits进行修改
    if(is_exsits){
        chat_widget = new chat;
        this->hide();
        chat_widget->show();
    }else{
        show_message(QString("您的账户不存在或者密码不正确"),1);
    }
}

//槽函数-注册按钮
void Widget::on_pushButton_register_clicked()
{
    QString user_id=ui->lineEdit_id->text();            //账号
    QString user_password=ui->lineEdit_password->text();//密码
                                                        //发送到服务器进行注册
                                                        //接收服务器返回的状态,并更新state
    bool state=false;
    if(!state){
        show_message(QString("该账号已被注册,请重新输入账号"),0);
    }else{
        show_message(QString("您的账户已经成功注册"),0);
    }
}


