#include "chat.h"
#include "ui_chat.h"
#include<vector>
#include<string>
#include<QMessageBox>
#include<QCheckBox>
#include<QTreeWidgetItem>
#include<QMenu>
#include<QPainter>
#include<QPaintEvent>
#include<QPainterPath>
#include<QFileDialog>
#include<QHBoxLayout>
#include<QTableWidget>
//只支持单行文本展示，多行文本不想写了
void chat::paintEvent(QPaintEvent *e){
    if(draw_chatbox){
        QPainter p;
        p.begin(this);
        qDebug()<<"执行画图";
        QFont f;
        f.setPointSize(12);
        p.setFont(f);
        //p.save();
        QFontMetrics fm = p.fontMetrics();
        int topx_left=ui->listWidget_chatbox-> pos().x();//聊天框左边界
        int topy_up=ui->listWidget_chatbox->pos().y()+20;//聊天框上边界
        int box_witdh=ui->listWidget_chatbox->size().width();//聊天框长度
        int text_height=fm.height();//文字高度
        int gap_kuang_icon=20;//icon和文字的间隔
        int gap_kuang_text=10;//icon和文字的间隔
        int H=25;
        int icon_size=30;//头像的大小
         for (int i = 0; i < ui->listWidget_chatbox->count(); ++i) {
//            p.restore();
             QListWidgetItem *item = ui->listWidget_chatbox->item(i);
             QString message=item->data(Qt::UserRole+3).toString();
             int reverse=item->data(Qt::UserRole+4).toInt();
             int text_width = fm.horizontalAdvance(message);//获取文字的大小
             int new_x=0;
             int icon_x=0;
            //绘制文本框、文本和头像
             if(reverse==0){//放在左边
                 icon_x=topx_left;
                 new_x=topx_left+icon_size+gap_kuang_icon;
                 p.setBrush(QColor(255,255,255));
                 p.setPen(QPen(Qt::black));
                 p.drawRoundedRect(new_x,topy_up-text_height,text_width+2*gap_kuang_text,text_height+5,5,5);
                 new_x=new_x+gap_kuang_text;
                 p.drawText(new_x, topy_up, message);

             }else{        //放在右边
                 p.setBrush(QColor(0, 153, 255));
                 p.setPen(QPen(Qt::white));
                 new_x=topx_left+(box_witdh-text_width)-icon_size-gap_kuang_icon-2*gap_kuang_text;
                 p.drawRoundedRect(new_x,topy_up-text_height,text_width+2*gap_kuang_text,text_height+5,5,5);
                 new_x=new_x+gap_kuang_text;
                 p.drawText(new_x, topy_up, message);
                 icon_x=topx_left+box_witdh-icon_size;
             }
            //绘制头像
            QPixmap pixmap(":/src_pic/QQ.jpg");
            p.drawPixmap(icon_x,topy_up-(icon_size/2)-5,icon_size,icon_size,pixmap);
            topy_up=topy_up+H;


         }
         p.end();

    }
    draw_chatbox=false;

}

//将数据插入到chatbox
void chat::insert_chat(std::vector<QString>name,std::vector<QString>num,std::vector<QString>time,std::vector<QString>history){
    QFont font;
    font.setPointSize(14);
    int reverse=0;
    ui->listWidget_chatbox->clear();
    for(int i=0;i<name.size();i++){
        QListWidgetItem* t=new QListWidgetItem;
        t->setData(Qt::UserRole,name[i]);//名字
        t->setData(Qt::UserRole+1,num[i]);//账号
        t->setData(Qt::UserRole+2,time[i]);//时间
        t->setData(Qt::UserRole+3,history[i]);//消息
        t->setFont(font);
        if(i!=0&&num[i]!=num[i-1]){
            reverse=1-reverse;
        }
        t->setData(Qt::UserRole+4,reverse);//消息顺序
        //t->setData(Qt::UserRole+5,0);//消息类型，文字还是图片
        //qDebug()<<history[i]<<reverse;
        ui->listWidget_chatbox->insertItem(i,t);
    };
    draw_chatbox=true;
    this->update();
}


//在联系人界面展示该账号加入的所有群
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
        t->setIcon(QIcon(":/src_pic/QQ.jpg"));//群头像
        t->setData(Qt::UserRole,name_user);
        t->setData(Qt::UserRole+1,num_user);
        ui->listWidget->insertItem(i,t);
    };
    ui->listWidget->show();
    //connect(ui->listWidget,&QListWidget::clicked,this,&chat::get_group);
    connect(ui->listWidget,&QListWidget::itemClicked,this,&chat::get_group);
};



//在联系人界面点击了一个群组,进入群聊
void chat::get_group(QListWidgetItem* item){
    QString name = ui->listWidget->currentItem()->data(Qt::UserRole).toString();
    QString num = ui->listWidget->currentItem()->data(Qt::UserRole+1).toString();//获取点击的群号
    //根据群号展示群成员的信息
    // qDebug() << "Name : " << name;
    // qDebug() << "Num : " << num;
    reset_ui();
    cur_group_num=num;
    ui->textEdit->resize(532,241);
    ui->listWidget->show();
    ui->label_showName->setText(name);
    ui->listWidget_group_member->show();
    ui->pushButton_del_group_mem->show();
    draw_chatbox=true;
    show_chatBox();
    //ui->listWidget_chatbox->show();
    show_groups_member({"张三","李四","王五","赵金","钱成","张三","李四","王五","赵金","钱成","王五","赵金","钱成"},
                       {"123","456","234","832","223","123","456","234","832","223","234","832","223"});
}


//在联系人界面的群界面进行群成员展示
void chat::show_groups_member(std::vector<std::string> name,std::vector<std::string> num)
{
    //name:从服务器接收到的群所有成员名字
    //num:从服务器接收到的群所有成员账号
    QFont font;
    font.setPixelSize(20);
    ui->listWidget_group_member->clear();
    ui->listWidget_group_member->setSpacing(5);//间距
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
        ui->listWidget_group_member->insertItem(i,t);
    };
    ui->listWidget_group_member->show();


};


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
        ui->listWidget->insertItem(i,t);
    };
    ui->listWidget->show();
    connect(ui->listWidget,&QListWidget::itemClicked,this,&chat::get_friend);
    connect(ui->listWidget,&QListWidget::customContextMenuRequested,this,&chat::FriRightMenu);
};

void chat::FriRightMenu(const QPoint& pos){
    qDebug()<<"右键dianji";
    QListWidgetItem* sitem = nullptr;
    sitem = ui->listWidget->itemAt(pos);
    cur_friend_num=sitem->data(Qt::UserRole+1).toString();
    qDebug()<<cur_friend_num;
    m_Fri->exec(QCursor::pos());
}


//从消息页面点击了好友，进入私聊
void chat::get_friend(QListWidgetItem* item){
    reset_ui();
    QString name = ui->listWidget->currentItem()->data(Qt::UserRole).toString();
    QString num = ui->listWidget->currentItem()->data(Qt::UserRole+1).toString();
    QString cls = ui->listWidget->currentItem()->data(Qt::UserRole+2).toString();//用于辨别是群还是好友
    // qDebug() << "siliao : " << name;
    // qDebug() << "Num : " << num;

    cur_friend_num=num;//好友的账号
    ui->listWidget_group_member->hide();
    ui->listWidget->show();
    ui->textEdit->resize(781,241);
    //ui->listWidget_chatbox->show();
    ui->label_showName->setText(name);
    draw_chatbox=true;
    show_chatBox();
    //show_chatBox({"张三","李四","王五"},{"2014-1-1","2014-1-1","2014-1-1"},{"hello","hi","ok"});
    insert_chat({"张三","李四","张三","李四"},{"1","2","1","2"},{"2014-1-1","2014-1-1","2014-1-1","2014-1-1"},{"你好张三","你好啊，李四","我很好，谢谢，非常感谢你了，太棒了！","不用谢哦，谢谢，非啊啊啊啊啊啊常感谢你了"});
}







//槽函数-添加图标
//添加好友和创建群聊
void chat::on_pushButton_add_clicked()
{
    nfg= new new_friends_group();
    nfg->show();
}

//槽函数-重命名好友
void chat::ReNameFri(){

}

//槽函数-消息图标
void chat::on_pushButton_message_clicked()
{
    reset_ui();
    //发送账号到服务器，获取好友数据
    //进行展示
    show_friends({"张三","李四","王五","赵金","钱成","张三","李四","王五","赵金","钱成","王五","赵金","钱成"},
                 {"123","456","234","832","223","123","456","234","832","223","234","832","223"});
}


//槽函数-邀请好友加入群聊
void chat::on_pushButton_friend_invite_clicked()
{
    inv =new invite_join_group();
    inv->show();
}


//槽函数-删除好友
void chat::on_pushButton_friend_delete_clicked()
{

    QString delete_num=cur_friend_num;
    //发送delete_num 到服务器
    //服务器重传好友列表到本地进行刷新
    QMessageBox::information(NULL, "Warning", "已删除该好友", QMessageBox::Yes );

}


//槽函数-群图标
void chat::on_pushButton_group_clicked()
{
    //发送账号到服务器，获取账号加入的群数据
    //进行展示
    reset_ui();
    show_groups({"1群","2群","3群","4群","5群",},
                 {"123","456","234","832","223"});
}



//槽函数-群界面内移除群聊内的群成员
void chat::on_pushButton_del_group_mem_clicked()
{
    //遍历所有的CheckBox，把所有选中的CheckBox索引号都记录到QStringList selectedItems中
    for(int i = 0; i < ui->listWidget_group_member->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget_group_member->item(i);//先获取QListWidgetItem

        if(item->checkState()==Qt::Checked){
            QString num =item->data(Qt::UserRole+1).toString();
            group_delete_num.push_back(num);
            qDebug()<<"select:"<<num;
        }
    }
}


//槽函数-发送文件
void chat::on_pushButton_sendFile_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,tr("open a file."),"D:/",tr("text files(*.txt *.dat);;All files(*.*)"));
    ui->textEdit->setText(filePath);
}

//槽函数-发送图片
void chat::on_pushButton_sendPic_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,tr("open a file."),"D:/",tr("pic files(*.png *.jpg)"));
    ui->textEdit->setText(filePath);
}


//槽函数-点击了emoj表格中的具体emoj
void chat:: click_emoj(QTableWidgetItem* item){
    QString t=item->text();
    ui->tableWidget->hide();
    ui->textEdit->insertPlainText(t);
}
//槽函数-点击了emoj按钮
void chat::on_pushButton_sendEmoj_clicked()
{

    ui->tableWidget->show();
}


//初始化Ui
void chat::reset_ui(){
    ui->listWidget->hide();
    ui->textEdit->hide();
    ui->label_showName->hide();
    ui->listWidget_group_member->hide();
    ui->pushButton_del_group_mem->hide();
    ui->listWidget_chatbox->hide();
    ui->pushButton_sendEmoj->hide();
    ui->pushButton_sendFile->hide();
    ui->pushButton_sendPic->hide();
    ui->label_chatbox_bg->hide();
    ui->tableWidget->hide();
    draw_chatbox=false;
}

void chat::show_chatBox(){

    ui->textEdit->show();
    ui->label_showName->show();
    ui->pushButton_sendEmoj->show();
    ui->pushButton_sendFile->show();
    ui->pushButton_sendPic->show();
    ui->label_chatbox_bg->show();
}


//初始化好友右键菜单
void chat::friend_right_menu(){
    m_Fri = new QMenu(this);

    m_renamegrp = new QAction("重命名", this);
    connect(m_renamegrp, &QAction::triggered, this, &chat::ReNameFri);

    m_delgrp = new QAction("删除好友", this);
    connect(m_delgrp, &QAction::triggered, this, &chat::on_pushButton_friend_delete_clicked);

    m_invitegrp = new QAction("邀请加入群聊", this);
    connect(m_invitegrp, &QAction::triggered, this, &chat::on_pushButton_friend_invite_clicked);

    m_Fri->addAction(m_renamegrp);
    m_Fri->addAction(m_delgrp);
    m_Fri->addAction(m_invitegrp);


}

void chat::init_emoj(){
    QString cur_emoj="";
    ui->tableWidget->setRowCount(4);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->horizontalHeader()->hide();//取消列号
    ui->tableWidget->verticalHeader()->hide();//取消行号
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setIconSize(QSize(32,32));
    QFont f;
    f.setPointSize(17);
    ui->tableWidget->setFont(f);
    char32_t  emoj[] = {0x1F601,0x0};
    char32_t start = 0x1F601 ;
    for(int row=0;row<=4;row++){
        for(int col=0;col<=6;col++){
            int index=row*10+col;
            QString t=QString::number(index);
            QTableWidgetItem* item=new QTableWidgetItem();
            emoj[0]=start;
            t=QString::fromUcs4(emoj);
            item->setText(t);
            start++;
            ui->tableWidget->setItem(row,col,item);
        }
    }
    ui->tableWidget->resizeRowsToContents(); // 自动调整所有行的高度以适应内容
    ui->tableWidget->resizeColumnsToContents(); // 自动调整所有列的宽度以适应内容
    connect(ui->tableWidget,&QTableWidget::itemClicked,this,&chat::click_emoj);
}
chat::chat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chat)
{
    ui->setupUi(this);
    reset_ui();
    init_emoj();
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_group_member->setSpacing(10);
    friend_right_menu();
    cur_friend_num="";
    cur_group_num="";
    group_delete_num={};//存储一个群里需要删除的成员
    draw_chatbox=false;
    ui->listWidget_chatbox->setSpacing(5);

    show_friends({"张三","李四","王五","赵金","钱成","张三","李四","王五","赵金","钱成","王五","赵金","钱成"},
                 {"123","456","234","832","223","123","456","234","832","223","234","832","223"});
};

chat::~chat()
{
    delete ui;
}






