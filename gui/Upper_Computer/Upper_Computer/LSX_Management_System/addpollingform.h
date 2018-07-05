#ifndef ADDPOLLINGFORM_H
#define ADDPOLLINGFORM_H


#include <QWidget>
#include <QMouseEvent>
#include "app/imessagebox.h"


//extern  QString addVlues[5];
namespace Ui {
class addPollingForm;
}

class addPollingForm : public QWidget
{
    Q_OBJECT

public:
    explicit addPollingForm(QWidget *parent = 0);
    ~addPollingForm();

public:
    void showCurrentTime();
    void addToMysql();
    QString readyAddDateSql();
signals:
    void toDevicePolling_addOK();
public slots:
    void fromPollingDevice(QString *string);

private slots:


    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_addPollingCloseButton_clicked();

private:
    Ui::addPollingForm *ui;
    bool checkNetFlag;
    bool checkVoiceFlag;

    QString insertPositionQstring[5];
    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // ADDPOLLINGFORM_H
