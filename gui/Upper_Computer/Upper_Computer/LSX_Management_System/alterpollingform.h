#ifndef ALTERPOLLINGFORM_H
#define ALTERPOLLINGFORM_H

#include <QWidget>
#include <QMouseEvent>
#include <QSqlQuery>
#include "app/imessagebox.h"

namespace Ui {
class alterPollingForm;
}

class alterPollingForm : public QWidget
{
    Q_OBJECT

public:
    explicit alterPollingForm(QWidget *parent = 0);
    ~alterPollingForm();
    void setComboBox_6AndSetComboBOx_7();

signals:
    void toDevicePollingForClearUserSelectConotrol();



public slots:
    void fromPollingDevice(QString *string);

private:
    Ui::alterPollingForm *ui;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
    bool checkNetFlag;
    bool checkVoiceFlag;


protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_alterPollingCloseButton_clicked();
};

#endif // ALTERPOLLINGFORM_H
