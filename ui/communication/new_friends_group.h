#ifndef NEW_FRIENDS_GROUP_H
#define NEW_FRIENDS_GROUP_H

#include <QWidget>

namespace Ui {
class new_friends_group;
}

class new_friends_group : public QWidget
{
    Q_OBJECT

public:
    explicit new_friends_group(QWidget *parent = nullptr);
    ~new_friends_group();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::new_friends_group *ui;
};

#endif // NEW_FRIENDS_GROUP_H
