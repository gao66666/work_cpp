#include "emoj.h"
#include "ui_emoj.h"
emoj::emoj(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::emoj)
{
    cur_emoj="";
    ui->setupUi(this);
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
    connect(ui->tableWidget,&QTableWidget::itemClicked,this,&emoj::click_emoj);
}
 void emoj:: click_emoj(QTableWidgetItem* item){
    QString t=item->text();
    //this->hide();
    cur_emoj=t;
}

emoj::~emoj()
{
    delete ui;
}
