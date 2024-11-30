#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include<QListWidgetItem>
#include<invite_join_group.h>
#include<new_friends_group.h>
namespace Ui {
class chat;
}

class chat : public QWidget
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    void show_friends(std::vector<std::string> name,std::vector<std::string> num);
    void show_groups(std::vector<std::string> name,std::vector<std::string> num);
    void show_groups_member(std::vector<std::string> name,std::vector<std::string> num);
    void get_friend(QModelIndex pos);
    void get_group(QModelIndex pos);
    void reset_ui();
    void anyStateChanged();
    QString cur_friend_num;
    QString cur_group_num;
    std::vector<QString>group_delete_num;
    invite_join_group* inv;
    new_friends_group*nfg;
    ~chat();

private slots:

    void on_pushButton_friend_delete_clicked();

    void on_pushButton_clicked();

    void on_pushButton_group_clicked();

    void on_pushButton_del_group_mem_clicked();

    void on_pushButton_friend_invite_clicked();

    void on_pushButton_insert_clicked();

private:
    Ui::chat *ui;
};

#endif // CHAT_H
