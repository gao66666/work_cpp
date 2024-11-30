#include "chat.h"
#include "ui_chat.h"
#include<vector>
#include<string>
#include<QMessageBox>
#include<QCheckBox>
typedef struct user{
    QString name;
    QString num;
}user;
//用户点击

chat::chat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chat)
{
    ui->setupUi(this);
    reset_ui();
    cur_friend_num="";
    cur_group_num="";
    group_delete_num={};//存储一个群里需要删除的成员
};
//从消息页面点击了好友
void chat::get_friend(QModelIndex pos){
    int row=pos.row();
    row=row;
    //QVariant x=ui->listWidget->currentItem()->data(Qt::UserRole);
    QString name = ui->listWidget->currentItem()->data(Qt::UserRole).toString();
    QString num = ui->listWidget->currentItem()->data(Qt::UserRole+1).toString();
    QString cls = ui->listWidget->currentItem()->data(Qt::UserRole+2).toString();//用于辨别是群还是好友
    qDebug() << "Name : " << name;
    qDebug() << "Num : " << num;
    if(cls=="1"){
        cur_friend_num=num;
        ui->textEdit->show();
        ui->pushButton_friend_delete->show();
        ui->pushButton_friend_invite->show();
        ui->label_friend->show();
        ui->label_friend->setText(name);
    };

}
//从联系人页面点击了群组
void chat::get_group(QModelIndex pos){
    int row=pos.row();
    row=row;
    QString name = ui->listWidget->currentItem()->data(Qt::UserRole).toString();
    QString num = ui->listWidget->currentItem()->data(Qt::UserRole+1).toString();
    QString cls = ui->listWidget->currentItem()->data(Qt::UserRole+2).toString();//用于辨别是群还是好友
    qDebug() << "Name : " << name;
    qDebug() << "Num : " << num;
    if(cls=="1"){
        cur_friend_num=num;
        ui->textEdit->show();
        ui->pushButton_friend_delete->show();
        ui->pushButton_friend_invite->show();
        ui->label_friend->show();
        ui->label_friend->setText(name);
    }else{
        cur_group_num=num;
        ui->textEdit->show();
        ui->pushButton_friend_delete->hide();
        ui->pushButton_friend_invite->hide();
        ui->label_friend->show();
        ui->label_friend->setText(name);
        ui->listWidget_group->show();
        show_groups_member({"张三","李四","王五","赵金","钱成","张三","李四","王五","赵金","钱成","王五","赵金","钱成"},
                           {"123","456","234","832","223","123","456","234","832","223","234","832","223"});
    }
        ;

}



//在消息界面进行好友展示

void chat::show_friends(std::vector<std::string> name,std::vector<std::string> num)
{
    //name:从服务器接收到的好友名字
    //num:从服务器接收到的好友账号
    QFont font;
    font.setPixelSize(20);
    ui->listWidget->clear();
    ui->listWidget->setSpacing(10);//间距
    for(int i=0;i<name.size();i++){
        QListWidgetItem* t=new QListWidgetItem;
        std::string text="   "+name[i];
        QString name_user=QString::fromStdString(name[i]);
        QString num_user=QString::fromStdString(num[i]);
        QString  te=QString::fromStdString(text);
        t->setText(te);
        t->setFont(font);
        t->setIcon(QIcon(":/src_pic/QQ.jpg"));
        t->setData(Qt::UserRole,name_user);
        t->setData(Qt::UserRole+1,num_user);
        t->setData(Qt::UserRole+2,1);//1代表展示的是好友
        ui->listWidget->insertItem(1,t);
    };
    ui->listWidget->show();
    connect(ui->listWidget,&QListWidget::clicked,this,&chat::get_friend);
};

//在联系人界面进行群展示
void chat::show_groups(std::vector<std::string> name,std::vector<std::string> num)
{
    //name:从服务器接收到的群名字
    //num:从服务器接收到的群账号
    QFont font;
    font.setPixelSize(20);
    ui->listWidget->clear();
    ui->listWidget->setSpacing(10);//间距
    for(int i=0;i<name.size();i++){
        QListWidgetItem* t=new QListWidgetItem;
        std::string text="   "+name[i];
        QString name_user=QString::fromStdString(name[i]);
        QString num_user=QString::fromStdString(num[i]);
        QString  te=QString::fromStdString(text);
        t->setText(te);
        t->setFont(font);
        t->setIcon(QIcon(":/src_pic/QQ.jpg"));
        t->setData(Qt::UserRole,name_user);
        t->setData(Qt::UserRole+1,num_user);
        t->setData(Qt::UserRole+2,2);//2代表展示的是群
        ui->listWidget->insertItem(1,t);
    };
    ui->listWidget->show();
    connect(ui->listWidget,&QListWidget::clicked,this,&chat::get_group);
};


void chat::anyStateChanged()
{

    ;
};

//在联系人界面的群界面进行群成员展示
void chat::show_groups_member(std::vector<std::string> name,std::vector<std::string> num)
{
    //name:从服务器接收到的群所有成员名字
    //num:从服务器接收到的群所有成员账号
    QFont font;
    font.setPixelSize(20);
    ui->listWidget_group->clear();
    ui->listWidget_group->setSpacing(5);//间距
    for(int i=0;i<name.size();i++){
        QListWidgetItem* t=new QListWidgetItem;
        std::string text="   "+name[i];
        QString name_user=QString::fromStdString(name[i]);
        QString num_user=QString::fromStdString(num[i]);
        QString  te=QString::fromStdString(text);
        //QCheckBox *checkBox= new QCheckBox ();
        //ui->listWidget_group->setItemWidget(t,checkBox);
        t->setFlags(t->flags()|Qt::ItemIsUserCheckable);
        t->setCheckState(Qt::Unchecked);
        t->setText(te);
        t->setFont(font);
        t->setIcon(QIcon(":/src_pic/QQ.jpg"));
        t->setData(Qt::UserRole,name_user);
        t->setData(Qt::UserRole+1,num_user);
        t->setData(Qt::UserRole+2,2);//2代表展示的是群

        ui->listWidget_group->insertItem(1,t);

        //connect(checkBox, &QCheckBox::checkStateChanged, this, &chat::anyStateChanged);
    };
    //connect(ui->listWidget_group,&QListWidget::itemSelectionChanged,this,&chat::anyStateChanged);
    ui->listWidget_group->show();

};


chat::~chat()
{
    delete ui;
}

void chat::reset_ui(){
    ui->listWidget->hide();
    ui->textEdit->hide();
    ui->label_friend->hide();
    ui->pushButton_friend_delete->hide();
    ui->pushButton_friend_invite->hide();
    ui->listWidget_group->hide();
}



//在联系人界面的好友界面产生了删除好友事件
void chat::on_pushButton_friend_delete_clicked()
{
    QString delete_num=cur_friend_num;
    //发送delete_num 到服务器
    //服务器重传好友列表到本地进行刷新
    QMessageBox::information(NULL, "Warning", "已删除该好友", QMessageBox::Yes );

}

//点击了消息图标
void chat::on_pushButton_clicked()
{
    reset_ui();
    show_friends({"张三","李四","王五","赵金","钱成","张三","李四","王五","赵金","钱成","王五","赵金","钱成"},
                 {"123","456","234","832","223","123","456","234","832","223","234","832","223"});
}

//点击了群号图标
void chat::on_pushButton_group_clicked()
{
    reset_ui();
    show_groups({"1群","2群","3群","4群","5群",},
                 {"123","456","234","832","223"});
}


void chat::on_pushButton_del_group_mem_clicked()
{
    //遍历所有的CheckBox，把所有选中的CheckBox索引号都记录到QStringList selectedItems中
    for(int i = 0; i < ui->listWidget_group->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget_group->item(i);//先获取QListWidgetItem

        if(item->checkState()==Qt::Checked){
            QString num =item->data(Qt::UserRole+1).toString();
            group_delete_num.push_back(num);
            qDebug()<<"select:"<<num;
        }
    }
    // for(auto k:group_delete_num){
    //     qDebug()<<k<<Qt::endl;
    // }
    //ui->listWidget_group->selectedItems().clear();
}


void chat::on_pushButton_friend_invite_clicked()
{
    inv =new invite_join_group();
    inv->show();
}


void chat::on_pushButton_insert_clicked()
{
    nfg= new new_friends_group();
    nfg->show();

}

