#include "new_friends_group.h"
#include "ui_new_friends_group.h"

new_friends_group::new_friends_group(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::new_friends_group)
{
    ui->setupUi(this);

}

new_friends_group::~new_friends_group()
{
    delete ui;
}

void new_friends_group::on_pushButton_clicked()
{
    this->hide();
}


void new_friends_group::on_pushButton_2_clicked()
{
    this->hide();
}

