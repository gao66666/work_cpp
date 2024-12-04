#ifndef EMOJ_H
#define EMOJ_H
#include <QWidget>
#include<QTableWidgetItem>
namespace Ui {
class emoj;
}

class emoj : public QWidget
{
    Q_OBJECT

public:
    explicit emoj(QWidget *parent = nullptr);
    void click_emoj(QTableWidgetItem* item);
    QString cur_emoj;
    ~emoj();

private:
    Ui::emoj *ui;
};

#endif // EMOJ_H
