#ifndef USERLOGFORM_H
#define USERLOGFORM_H

#include <QWidget>
#include <QString>
#include <app/global.h>
#include <QDateTime>
#include <QMessageBox>
#include <QTime>
#include <QScrollBar>
#include "app/imessagebox.h"
#include "app/qmsqlquerymodel.h"

#define LOG_OPE_NUM 34
#define  localQString(QString)   QString::fromLocal8Bit(QString)



namespace Ui {
class userLogForm;
}

class userLogForm : public QWidget
{
    Q_OBJECT

public:
    explicit userLogForm(QWidget *parent = 0);
    ~userLogForm();

public:
    void initUserSelect_ComboBox();
    void setInitStyle();

    void setTableviewHeadview();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void initUserOperationSelect_comboBox();

    void on_comboBox_3_currentTextChanged(const QString &arg1);
    void initDefaultShow();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::userLogForm *ui;
    QString log_UserOperationSelect[4];//0:userid 1:operation 2:poertype  3 time
    global *logGlobal;
    int searchControlFlag;
    QString stringLogOperation[LOG_OPE_NUM];

    QMSqlQueryModel * model;

};
/*
 *   QString stringLogOperation[LOG_OPE_NUM]
    {

    };
*/

#endif // USERLOGFORM_H
