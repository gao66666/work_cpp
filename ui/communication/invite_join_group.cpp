#include "invite_join_group.h"
#include "ui_invite_join_group.h"

invite_join_group::invite_join_group(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::invite_join_group)
{
    ui->setupUi(this);
    group_join_num={};
    show_groups({"1群","2群","3群","4群","5群",},
                {"123","456","234","832","223"});
}

invite_join_group::~invite_join_group()
{
    delete ui;
}
//在联系人界面的群界面进行群成员展示
void invite_join_group::show_groups(std::vector<std::string> name,std::vector<std::string> num)
{
    //name:从服务器接收到的群所有成员名字
    //num:从服务器接收到的群所有成员账号
    QFont font;
    font.setPixelSize(20);
    ui->listWidget->clear();
    ui->listWidget->setSpacing(5);//间距
    for(int i=0;i<name.size();i++){
        QListWidgetItem* t=new QListWidgetItem;
        std::string text="   "+name[i];
        QString name_user=QString::fromStdString(name[i]);
        QString num_user=QString::fromStdString(num[i]);
        QString  te=QString::fromStdString(text);
        t->setFlags(t->flags()|Qt::ItemIsUserCheckable);
        t->setCheckState(Qt::Unchecked);
        t->setText(te);
        t->setFont(font);
        t->setIcon(QIcon(":/src_pic/QQ.jpg"));
        t->setData(Qt::UserRole,name_user);
        t->setData(Qt::UserRole+1,num_user);
        t->setData(Qt::UserRole+2,2);//2代表展示的是群

        ui->listWidget->insertItem(1,t);

        //connect(checkBox, &QCheckBox::checkStateChanged, this, &chat::anyStateChanged);
    };
    ui->listWidget->show();
};

void invite_join_group::on_pushButton_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);//先获取QListWidgetItem

        if(item->checkState()==Qt::Checked){
            QString num =item->data(Qt::UserRole+1).toString();
            group_join_num.push_back(num);
            qDebug()<<"select:"<<num;
        }
    }
    this->hide();
}

