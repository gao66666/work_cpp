#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include<QListWidgetItem>
#include<invite_join_group.h>
#include<new_friends_group.h>
#include<QTableWidgetItem>
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
    void get_friend(QListWidgetItem* item);
    void get_group(QListWidgetItem* item);
    void reset_ui();
    void anyStateChanged();
    void friend_right_menu();
    void FriRightMenu(const QPoint& pos);
    void ReNameFri();
    void paintEvent(QPaintEvent *e) override;
    void show_chatBox();
    void insert_chat(std::vector<QString>name,std::vector<QString>num,std::vector<QString>time,std::vector<QString>history);
    void click_emoj(QTableWidgetItem* item);
    void init_emoj();
    QString cur_friend_num;
    QString cur_group_num;
    std::vector<QString>group_delete_num;
    invite_join_group* inv;
    new_friends_group*nfg;
    QMenu * m_Fri;
    QAction* m_renamegrp;
    QAction* m_delgrp;
    QAction* m_invitegrp;
    bool draw_chatbox;
    ~chat();

private slots:

    void on_pushButton_friend_delete_clicked();

    //void on_pushButton_clicked();

    void on_pushButton_group_clicked();

    void on_pushButton_del_group_mem_clicked();

    void on_pushButton_friend_invite_clicked();

    //void on_pushButton_insert_clicked();

    void on_pushButton_add_clicked();

    //void on_pushButton_group_2_clicked();

    void on_pushButton_message_clicked();


    void on_pushButton_sendFile_clicked();

    void on_pushButton_sendPic_clicked();

    void on_pushButton_sendEmoj_clicked();

private:
    Ui::chat *ui;
};

#endif // CHAT_H
