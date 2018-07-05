#ifndef DEVICEMANAGEMENTFORM_H
#define DEVICEMANAGEMENTFORM_H

#include <QWidget>
#include "adddevicedialog.h"
#include "alterdevicedialog.h"
#include <QStandardItemModel>
#include <QString>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QComboBox>
#include <QTime>
#include <QSqlQueryModel>
#include "app/qmsqlquerymodel.h"
#include "app/imessagebox.h"
#include <QPushButton>
#include  "addduan_dialog.h"
#include  "addoralterjiandialog.h"
#include "addquoralterdialog.h"
#include "addstationoralterdialog.h"

namespace Ui {
class DeviceManagementForm;
}

class DeviceManagementForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceManagementForm(QWidget *parent = 0);
    ~DeviceManagementForm();
QStandardItemModel * deviceDuanModel;

    signals:
    void toDialogForJudgeAddOrAlter(bool,QString *);
    void toAddOrAlterJianDialogForAlterJian(bool,QString[]);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_2_tabBarClicked(int index);


    void on_tableView_5_doubleClicked(const QModelIndex &index);
    void setDeviceDuan();
    void setDeviceJian();
    void setDeviceQu();
    void setDeviceStation();
    void setDeviceJianFromWhat(QStandardItemModel *,int index,QString Jian);

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void device_duan_dialog(QString);
    void device_jian_dialog(QString);
    void device_qu_dialog(QString);
    void device_station_dialog(QString);


    void on_pushButton_17_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);

    void setDeviceRepositoryShow(const QModelIndex &index);

    void on_tableView_4_clicked(const QModelIndex &index);

    void on_tableView_5_clicked(const QModelIndex &index);
    void cancelAddDuanInfomation();
    void okAddAndCancelInfomation();

    void okAlterAndCancelInfomation();
    void sqlOperation(QString,QString);
    void setAlterUpdateSql(QString,QString );
    void tab_Qu_Add_For_Jian(QString);
    void tab_Station_Add_For_comboBox(QString);
    void tab_Station_Add_For_Qu_comboBox(QString);

    void on_tableView_clicked(const QModelIndex &index);

    void setTableViewStart();

    void on_pushButton_3_clicked();
    void reFreshTableview(int Type);//1:add    2:alter   3:del
    void reFreshTableview_X();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

public slots:
    void fromMainWindowForAccessControl(bool userAccessType);
    void ForUpdateTableview_2_Show(QString type);
    void fromAddDeviceDialogForSentAddInfo(QString string[]);

private:
    Ui::DeviceManagementForm *ui;

    AddDeviceDialog * addDevice;

    AlterDeviceDialog * alterDevice;
    QString add= QString::fromLocal8Bit("添加");
    QString alter =QString::fromLocal8Bit("修改");
    QString del = QString::fromLocal8Bit("删除");
    bool select;
    QStandardItemModel * modelindex;
    QString delSelectText;
    int deviceReopsitoryShowSqlControl;
    QString sqlTextWhereString[6]; //点击tablview后会将获取的  段 间 区 站 保存在 这里

    QString clickedTabBrTextForSql[4];//[0]:Text  [1]: status; 0:duan/1:jian/2:qu/3:station
    int clickedTabBrTextStatus[4];


    QDialog * dialog;
    QPushButton * button1;
    QPushButton * button2;
    QGridLayout * layout;
    QGridLayout * layout2;
    QGroupBox * box;
    QGridLayout * layout3;
    QLabel * label;
    QLabel * label2;
    QLabel * label3;
    QLabel * label4;
    QLineEdit * lineEdit;
    QLineEdit * lineEdit2;
    QLineEdit * lineEdit3;
    QComboBox * combobox;
    QComboBox* combobox_jian;
    QComboBox* combobox_qu;
    QComboBox* combobox_station;//添加中为段combobox设计  必须
    QComboBox* combobox_Jian_from_duan;

    bool alterNoSelectFlag;
    bool currentTableViewSelectFalg;

    QString whereText;// 修改更新 where 字段
    QString sql;//修改跟新sql语句
    QString sql_duan;
    QString sql_jian;
    QString sql_qu;
    QString sql_station;

    QMSqlQueryModel *sqlModel;

    int T;
    bool tableviewClickedControl;

    QMSqlQueryModel * model_TableView;
    QString tableviewClickedText[5];

    QModelIndex reFreshIndex;
    bool userAccessControl;

    QPushButton  addDuanCloseButton;


    //新更新 修改
    addDuan_Dialog * addDuan;
    addDuan_Dialog * alterDuan;
    addOrAlterJianDialog * addJian;
    addOrAlterJianDialog * alterJian;
    addQuOrAlterDialog * addQu;
    addQuOrAlterDialog * alterQu;

    addStationOrAlterDialog * addStation;
    addStationOrAlterDialog * alterStation;

    bool tabBarCliicked[4];
    QString reFlushString[7];


};


/*
 * 删除是使用联级删除 删除表中的字段 那么在其他表中引用的该字段 全部会自动给删除
*/
#endif // DEVICEMANAGEMENTFORM_H
