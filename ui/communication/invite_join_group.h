#ifndef INVITE_JOIN_GROUP_H
#define INVITE_JOIN_GROUP_H

#include <QWidget>

namespace Ui {
class invite_join_group;
}

class invite_join_group : public QWidget
{
    Q_OBJECT

public:
    explicit invite_join_group(QWidget *parent = nullptr);
    void show_groups(std::vector<std::string> name,std::vector<std::string> num);
    std::vector<QString>group_join_num;
    ~invite_join_group();

private slots:
    void on_pushButton_clicked();

private:
    Ui::invite_join_group *ui;
};

#endif // INVITE_JOIN_GROUP_H
