#ifndef SETUI_H
#define SETUI_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include <EngineDefine.h>

#define UNLOCK 1
#define LOCK 0

namespace Ui {
class SetUi;
}

class SetUi : public QDialog
{
    Q_OBJECT

public:
    explicit SetUi(QWidget *parent = 0);
    ~SetUi();
     void showCode();
     MN_ECODE getCode();

     QSettings *getSettings();
     void setAllLineEdit(bool status);


private slots:
     void on_pushButton_clicked();

     void on_pushButton_2_clicked();

     void on_pushButton_3_clicked();

private:
    Ui::SetUi *ui;

    MN_ECODE btcode;

    bool codeEditStatus;

};

#endif // SETUI_H
