#ifndef USERINFOFORM_H
#define USERINFOFORM_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "adduserform.h"
#include "alteruserform.h"
#include "deluserdialog.h"

namespace Ui {
class userInfoForm;
}

class userInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit userInfoForm(QWidget *parent = 0);
    ~userInfoForm();

signals:
    void toAlterUser(QString);
    void toAddUser();
    void toDelUser(QString);
    void toLoginDialogForReLogin();

public slots:
    void fromMainWindow(QString);
    void alterUserInfo();
    void addUserInfo();
    void delUserInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::userInfoForm *ui;
    QPushButton * button1;
    QPushButton * button2;
    QPushButton * button3;
    QPushButton * button4;

    QWidget *adminWidget;
    QWidget *publicWidget;
    QGridLayout *adminLayout;
    QGridLayout *publicLayout;

    alterUserForm * alterUser;

    addUserForm * addUser;

    delUserDialog * delUser;




};

#endif // USERINFOFORM_H
