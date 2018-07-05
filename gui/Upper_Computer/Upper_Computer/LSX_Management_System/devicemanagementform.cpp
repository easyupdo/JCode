#include "devicemanagementform.h"
#include "ui_devicemanagementform.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include "alterdevicedialog.h"
#include "app/qmsqlquerymodel.h"
#include "app/qmtableviewdelegate.h"
#include <QSpacerItem>


DeviceManagementForm::DeviceManagementForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceManagementForm)
{
    delSelectText = "NULL";
    deviceReopsitoryShowSqlControl = 1;
    alterNoSelectFlag = false;
    tableviewClickedControl = false;
    userAccessControl = false;
    tabBarCliicked[0] = false;
    tabBarCliicked[1] = false;
    tabBarCliicked[2] = false;
    tabBarCliicked[3] = false;
   for(int i = 0 ; i<4 ; i++ )
   {
       clickedTabBrTextStatus[i] = 0;
   }
    ui->setupUi(this);
    sqlModel=new QMSqlQueryModel;//
       model_TableView = new QMSqlQueryModel;//设备库管理数据模型
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_5->setSelectionMode ( QAbstractItemView::SingleSelection);

    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_5->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    ui->tableView_2->horizontalHeader()->setSectionsClickable(false);
    ui->tableView_3->horizontalHeader()->setSectionsClickable(false);
    ui->tableView_4->horizontalHeader()->setSectionsClickable(false);
    ui->tableView_5->horizontalHeader()->setSectionsClickable(false);

    QMTableviewDelegate * delegate = new QMTableviewDelegate;
    ui->tableView->setItemDelegateForColumn(4,delegate);
    ui->tableView_2->setItemDelegateForColumn(0,delegate);
    ui->tableView_3->setItemDelegateForColumn(1,delegate);
    ui->tableView_4->setItemDelegateForColumn(2,delegate);
    ui->tableView_5->setItemDelegateForColumn(3,delegate);


    qDebug()<<"Device Station:"<<ui->tabWidget_2->tabText(0);
    QString tmpText=ui->tabWidget_2->tabText(0);//dianduan
    ui->pushButton_16->setText(add+tmpText);
    ui->pushButton_18->setText(alter+tmpText);
    ui->pushButton_17->setText(del+tmpText);
    setDeviceDuan();
    setDeviceJian();
    setDeviceQu();
    setDeviceStation();
    setTableViewStart();


        addDuan  = new addDuan_Dialog;
        connect(addDuan,&addDuan_Dialog::toDeviceManagementForUpdateTableview_2_Show,this,&DeviceManagementForm::ForUpdateTableview_2_Show);
       alterDuan = new addDuan_Dialog;
       connect(this,&DeviceManagementForm::toDialogForJudgeAddOrAlter,alterDuan,&addDuan_Dialog::fromDeviceManagementFormForJudgeAddOrAlter);
       connect(alterDuan,&addDuan_Dialog::toDeviceManagementForUpdateTableview_2_Show,this,&DeviceManagementForm::ForUpdateTableview_2_Show);


        addJian =new addOrAlterJianDialog;
        connect(this,&DeviceManagementForm::toAddOrAlterJianDialogForAlterJian,addJian,&addOrAlterJianDialog::fromDeviceManagementFormForAlterJian);
        alterJian = new addOrAlterJianDialog;
        connect(this,&DeviceManagementForm::toAddOrAlterJianDialogForAlterJian,alterJian,&addOrAlterJianDialog::fromDeviceManagementFormForAlterJian);
        connect(alterJian,&addOrAlterJianDialog::toDeviceManagementForUpdateTableview_2_Show,this,&DeviceManagementForm::ForUpdateTableview_2_Show);
//        connect(alterJian,);

        addQu = new addQuOrAlterDialog;
        connect(this,&DeviceManagementForm::toDialogForJudgeAddOrAlter,addQu,&addQuOrAlterDialog::fromDeviceManagementFormForAlterQu);
        connect(addQu,&addQuOrAlterDialog::toDeviceManagementForUpdateTableview_2_Show,this,&DeviceManagementForm::ForUpdateTableview_2_Show);

        alterQu = new addQuOrAlterDialog;
        connect(this,&DeviceManagementForm::toDialogForJudgeAddOrAlter,alterQu,&addQuOrAlterDialog::fromDeviceManagementFormForAlterQu);
        connect(alterQu,&addQuOrAlterDialog::toDeviceManagementForUpdateTableview_2_Show,this,&DeviceManagementForm::ForUpdateTableview_2_Show);

        addStation = new addStationOrAlterDialog;
        connect(this,&DeviceManagementForm::toDialogForJudgeAddOrAlter,addStation,&addStationOrAlterDialog::fromDeviceManagementFormForAlterStation);
        connect(addStation,&addStationOrAlterDialog::toDeviceManagementForUpdateTableview_2_Show,this,&DeviceManagementForm::ForUpdateTableview_2_Show);

        alterStation = new addStationOrAlterDialog;
        connect(this,&DeviceManagementForm::toDialogForJudgeAddOrAlter,alterStation,&addStationOrAlterDialog::fromDeviceManagementFormForAlterStation);
        connect(alterStation,&addStationOrAlterDialog::toDeviceManagementForUpdateTableview_2_Show,this,&DeviceManagementForm::ForUpdateTableview_2_Show);

        //添加设备ui
        addDevice = new AddDeviceDialog();
        addDevice->setModal(Qt::ApplicationModal);
        connect(addDevice,&AddDeviceDialog::toDeviceManagementFormForSentAddInfo,this,&DeviceManagementForm::fromAddDeviceDialogForSentAddInfo);

        alterDevice = new AlterDeviceDialog();





}

DeviceManagementForm::~DeviceManagementForm()
{
    delete ui;
}

void DeviceManagementForm::on_pushButton_clicked()
{
    if(userAccessControl)// 1:admin 0:public
    {
        addDevice->setCombobox();
        addDevice->exec();

        tableviewClickedControl = false;
//        this->reFreshTableview();
//        this->reFreshTableview_X();
    }else
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }
}

void DeviceManagementForm::on_pushButton_2_clicked()
{
    if(userAccessControl)// 1:admin 0:public
    {

        if(!tableviewClickedControl)
        {
            iMessageBox box;
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("请选择一个设备进行修改!"));
            box.exec();
        }else
        {
            alterDevice->setCombobox(this->tableviewClickedText);
            alterDevice->exec();
            this->reFreshTableview(2);
        }
        tableviewClickedControl = false;
//        this->reFreshTableview();
//        this->reFreshTableview_X();
    }else
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }

}

void DeviceManagementForm::on_tabWidget_2_tabBarClicked(int index)
{
    delSelectText = "NULL";
    if(index == 0)
    {
        deviceReopsitoryShowSqlControl = 1;
        qDebug()<<"Device Station:"<<ui->tabWidget_2->tabText(0);
        QString tmpText=ui->tabWidget_2->tabText(index);//dianduan
        ui->pushButton_16->setText(add+tmpText);
        ui->pushButton_18->setText(alter+tmpText);
        ui->pushButton_17->setText(del+tmpText);
        setDeviceDuan();


    }else if(index ==1)
    {
        deviceReopsitoryShowSqlControl = 2;
        qDebug()<<"Device Station:"<<ui->tabWidget_2->tabText(1);
        QString tmpText=ui->tabWidget_2->tabText(index);//dianduan
        ui->pushButton_16->setText(add+tmpText);
        ui->pushButton_18->setText(alter+tmpText);
        ui->pushButton_17->setText(del+tmpText);

//        if(tabBarCliicked[0])
//        {
            setDeviceJian();
            tabBarCliicked[0] = false;
//        }

    }else if(index == 2)
    {
        deviceReopsitoryShowSqlControl = 3;
        qDebug()<<"Device Station:"<<ui->tabWidget_2->tabText(2);
        QString tmpText=ui->tabWidget_2->tabText(index);//dianduan
        ui->pushButton_16->setText(add+tmpText);
        ui->pushButton_18->setText(alter+tmpText);
        ui->pushButton_17->setText(del+tmpText);

        setDeviceQu();

    }else if(index == 3)
    {
        deviceReopsitoryShowSqlControl = 4;
        qDebug()<<"Device Station:"<<ui->tabWidget_2->tabText(3);
        QString tmpText=ui->tabWidget_2->tabText(index);//dianduan
        ui->pushButton_16->setText(add+tmpText);
        ui->pushButton_18->setText(alter+tmpText);
        ui->pushButton_17->setText(del+tmpText);

        setDeviceStation();

    }
}



void DeviceManagementForm::on_tableView_5_doubleClicked(const QModelIndex &index)
{
//    int nx = ui->tableView->currentIndex().row();//获取行
//    ui->label->setText(QString::number(nx));
//    //ui->tableView->currentIndex().data().toString();//直接获取tableview鼠标点击位置的内容
//    QModelIndex indexMusicName= model->index(nx,1);
//    musicName = indexMusicName.data().toString();
//    ui->label_11->setText(musicName);
}

/*
 XXXIndex:各个段的计数
*/
void DeviceManagementForm::setDeviceDuan()
{
    deviceDuanModel = new QStandardItemModel();

    deviceDuanModel->insertColumns(1,6);
    QSqlQuery query;
    query.prepare("select duan,telephone,contact from duan;");
    query.exec();
    int index = 0;
    while(query.next())//duan
    {
        deviceDuanModel->setItem(index,0,new QStandardItem(query.value(0).toString()));
        deviceDuanModel->setItem(index,5,new QStandardItem(query.value(1).toString()));
        deviceDuanModel->setItem(index,6,new QStandardItem(query.value(2).toString()));
        deviceDuanModel->item(index,0)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->item(index,5)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->item(index,6)->setTextAlignment(Qt::AlignCenter);


//***
        QSqlQuery queryJian;//jian
        queryJian.prepare(QObject::tr("select jian from jian where duan = '%1' ;").arg(query.value(0).toString()));
        qDebug()<<"DEDED:"<<query.value(0).toString();
        qDebug()<<QObject::tr("select jian from jian where duan = %1 ;").arg(query.value(0).toString());
        queryJian.exec();
        int jianIndex = 0;
        while(queryJian.next())
        {
           qDebug()<<"*******:"<< queryJian.value(0).toString();

             jianIndex +=1;           
        }
        deviceDuanModel->setItem(index,1,new QStandardItem(QString::number(jianIndex)));//jian
        deviceDuanModel->item(index,1)->setTextAlignment(Qt::AlignCenter);
//****
        QSqlQuery queryQu;//qu
        queryQu.prepare(QObject::tr("select qu from qu where duan = '%1' ;").arg(query.value(0).toString()));
        qDebug()<<QObject::tr("select qu from qu where duan = %1 ;").arg(query.value(0).toString());
        queryQu.exec();
        int quIndex = 0;
        while(queryQu.next())
        {
           qDebug()<<"*******:"<< queryQu.value(0).toString();
             quIndex +=1;

          //  deviceDuanModel->setItem(index,4,new QStandardItem(QString::number(stationIndex)));//device

        }
        deviceDuanModel->setItem(index,2,new QStandardItem(QString::number(quIndex)));//qu
        deviceDuanModel->item(index,2)->setTextAlignment(Qt::AlignCenter);



//***
        QSqlQuery queryStation;//station
        queryStation.prepare(QObject::tr("select station from station where duan = '%1' ;").arg(query.value(0).toString()));
        qDebug()<<QObject::tr("select qu from qu where duan = %1 ;").arg(query.value(0).toString());
        queryStation.exec();
        int stationIndex = 0;
        while(queryStation.next())
        {
           qDebug()<<"*******:"<< queryStation.value(0).toString();
            stationIndex +=1;
        }
        deviceDuanModel->setItem(index,3,new QStandardItem(QString::number(stationIndex)));
        deviceDuanModel->item(index,3)->setTextAlignment(Qt::AlignCenter);
//***
        QSqlQuery queryDevice;//device
        queryDevice.prepare(QObject::tr("select deviceid from device where duan = '%1' ;").arg(query.value(0).toString()));
        qDebug()<<QObject::tr("select qu from qu where duan = %1 ;").arg(query.value(0).toString());
        queryDevice.exec();
        int deviceAccount = 0;
        while(queryDevice.next())
        {
           qDebug()<<"*******:"<< queryDevice.value(0).toString();
            deviceAccount +=1;
        }
        deviceDuanModel->setItem(index,4,new QStandardItem(QString::number(deviceAccount)));//device
        deviceDuanModel->item(index,4)->setTextAlignment(Qt::AlignCenter);
        index += 1;
    }

    deviceDuanModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("电务段"));
    deviceDuanModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("车间数量"));
    deviceDuanModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("工区数量"));
    deviceDuanModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("车站数量"));
    deviceDuanModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备数量"));


    deviceDuanModel->insertColumn(7);
    deviceDuanModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("联系人"));
    deviceDuanModel->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("联系电话"));
    deviceDuanModel->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit(""));
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);





    ui->tableView_2->setModel(deviceDuanModel);
    modelindex = deviceDuanModel;


}



//JIAN
void DeviceManagementForm::setDeviceJian()
{
    deviceDuanModel = new QStandardItemModel();
    deviceDuanModel->insertColumns(1,6);
    QSqlQuery query;
    if(clickedTabBrTextStatus[0] ==1 )
    query.prepare(QObject::tr("SELECT jian,Telephone,contact from jian where duan = '%1';").arg(sqlTextWhereString[0]));
    else
        query.prepare(QObject::tr("select jian,telephone,contact from jian;"));
    qDebug()<<"++++++++++++++++++++++++++++++++"<<QObject::tr("select jian from jian where daun = '%1';").arg(sqlTextWhereString[0]);
    query.exec();
    qDebug()<<"clickedTabBrTextStatus"<<clickedTabBrTextStatus[0];
    qDebug()<<"clickedTabBrTextForSql"<<clickedTabBrTextForSql;
    int index = 0;
    while(query.next())//jian
    {
        deviceDuanModel->setItem(index,1,new QStandardItem(query.value(0).toString()));
        deviceDuanModel->item(index,1)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->setItem(index,5,new QStandardItem(query.value(2).toString()));
        deviceDuanModel->setItem(index,6,new QStandardItem(query.value(1).toString()));
        deviceDuanModel->item(index,5)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->item(index,6)->setTextAlignment(Qt::AlignCenter);
 //ADD jianFrom
        setDeviceJianFromWhat(deviceDuanModel ,index,query.value(0).toString());


        QSqlQuery queryQu;//qu
        queryQu.prepare(QObject::tr("select qu from qu where jian = '%1' ;").arg(query.value(0).toString()));
        qDebug()<<"DEDED:"<<query.value(0).toString();
        qDebug()<<QObject::tr("select qu from qu where jian = '%1';").arg(query.value(0).toString());
        queryQu.exec();
        int quIndex = 0;
        while(queryQu.next())
        {
           qDebug()<<"*******:"<< queryQu.value(0).toString();
       quIndex +=1;

        }
        deviceDuanModel->setItem(index,2,new QStandardItem(QString::number(quIndex)));//qu
        deviceDuanModel->item(index,2)->setTextAlignment(Qt::AlignCenter);
//***


//***
        QSqlQuery queryStation;//station
        queryStation.prepare(QObject::tr("select station from station where jian = '%1' ;").arg(query.value(0).toString()));
        qDebug()<<QObject::tr("select station from station where jian = '%1';").arg(query.value(0).toString());
        queryStation.exec();
        int stationIndex = 0;

        while(queryStation.next())
        {
           qDebug()<<"*******:"<< queryStation.value(0).toString();
            stationIndex +=1;

        }
        deviceDuanModel->setItem(index,3,new QStandardItem(QString::number(stationIndex)));//station
        deviceDuanModel->item(index,3)->setTextAlignment(Qt::AlignCenter);

//***
        QSqlQuery queryDevice;//device
        queryDevice.prepare(QObject::tr("select deviceid from device where jian = '%1' ;").arg(query.value(0).toString()));
        qDebug()<<QObject::tr("select qu from qu where duan = %1 ;").arg(query.value(0).toString());
        queryDevice.exec();
        int deviceAccount = 0;
        while(queryDevice.next())
        {
           qDebug()<<"*******:"<< queryDevice.value(0).toString();
            deviceAccount +=1;
        }
        deviceDuanModel->setItem(index,4,new QStandardItem(QString::number(deviceAccount)));//device
        deviceDuanModel->item(index,4)->setTextAlignment(Qt::AlignCenter);
         index += 1;
    }

    deviceDuanModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("所属电段"));
    deviceDuanModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("车间名称"));
    deviceDuanModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("工区数量"));
    deviceDuanModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("车站数量"));
    deviceDuanModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备数量"));
    deviceDuanModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("联系人"));
    deviceDuanModel->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("联系电话"));

    deviceDuanModel->insertColumn(7);
    deviceDuanModel->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit(""));
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);


    ui->tableView_3->setModel(deviceDuanModel);


}



//qu
void DeviceManagementForm::setDeviceQu()
{
    deviceDuanModel = new QStandardItemModel();
    deviceDuanModel->insertColumns(1,6);
    QSqlQuery query;
    while(1)
    {
        if(clickedTabBrTextStatus[1])
        {
            query.prepare(QObject::tr("select * from qu where jian = '%1' and duan ='%2';").arg(sqlTextWhereString[1],sqlTextWhereString[0]));
            break;
        }
        else if(clickedTabBrTextStatus[0])
        {
            query.prepare(QObject::tr("select * from qu where duan = '%1';").arg(sqlTextWhereString[0]));
            break;
        }
        else
         {
             query.prepare("select * from qu;");
             break;
        }
    }


    query.exec();
    //qDebug()<<"jian_tableviewClicked"<<jian_tableviewClicked;
    int index=0;
    while(query.next())
    {
        deviceDuanModel->setItem(index,0,new QStandardItem(query.value(0).toString()));
        deviceDuanModel->setItem(index,2,new QStandardItem(query.value(2).toString()));
        deviceDuanModel->setItem(index,1,new QStandardItem(query.value(1).toString()));

        deviceDuanModel->setItem(index,5,new QStandardItem(query.value(4).toString()));//联系人
        deviceDuanModel->setItem(index,6,new QStandardItem(query.value(3).toString()));//电话
        deviceDuanModel->item(index,0)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->item(index,1)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->item(index,2)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->item(index,5)->setTextAlignment(Qt::AlignCenter);
        deviceDuanModel->item(index,6)->setTextAlignment(Qt::AlignCenter);

//***
        QSqlQuery queryStation;//station
        queryStation.prepare(QObject::tr("select station from station where duan = '%1' and jian = '%2' and qu = '%3' ;").arg(query.value(0).toString(),query.value(1).toString(),query.value(2).toString()));
        qDebug()<<QObject::tr("select station from station where qu = '%1';").arg(query.value(2).toString());
        queryStation.exec();
        int stationIndex = 0;

        while(queryStation.next())
        {
           qDebug()<<"*******:"<< queryStation.value(1).toString();
            stationIndex +=1;

        }
        deviceDuanModel->setItem(index,3,new QStandardItem(QString::number(stationIndex)));//station
        deviceDuanModel->item(index,3)->setTextAlignment(Qt::AlignCenter);

//***
        QSqlQuery queryDevice;//device
        queryDevice.prepare(QObject::tr("select deviceid from device where duan = '%1' and jian = '%2' and qu = '%3' ;").arg(query.value(0).toString(),query.value(1).toString(),query.value(2).toString()));
        qDebug()<<QObject::tr("select qu from qu where qu = %1 ;").arg(query.value(1).toString());
        queryDevice.exec();
        int deviceAccount = 0;
        while(queryDevice.next())
        {
           qDebug()<<"*******:"<< queryDevice.value(0).toString();
            deviceAccount +=1;
        }
        deviceDuanModel->setItem(index,4,new QStandardItem(QString::number(deviceAccount)));//device
        deviceDuanModel->item(index,4)->setTextAlignment(Qt::AlignCenter);
        index += 1;
    }

    deviceDuanModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("所属电段"));
    deviceDuanModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("所属车间"));
    deviceDuanModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("工区名称"));
    deviceDuanModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("车站数量"));
    deviceDuanModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备数量"));
    deviceDuanModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("联系人"));
    deviceDuanModel->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("联系电话"));


    deviceDuanModel->insertColumn(7);
    deviceDuanModel->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit(""));
    ui->tableView_4->horizontalHeader()->setStretchLastSection(true);


    ui->tableView_4->setModel(deviceDuanModel);
}

//station
void DeviceManagementForm::setDeviceStation()
{
   deviceDuanModel = new QStandardItemModel();
    deviceDuanModel->insertColumns(1,6);
    QSqlQuery query;

    while(1)
    {
        if(clickedTabBrTextStatus[2]==1)
        {
            query.prepare(QObject::tr("select * from station where qu = '%1' and jian = '%2' and duan = '%3';").arg(sqlTextWhereString[2],sqlTextWhereString[1],sqlTextWhereString[0]));
            break;
        }
        else if(clickedTabBrTextStatus[1] == 1)
        {
            query.prepare(QObject::tr("select * from station where jian = '%1' and duan = '%2';").arg(sqlTextWhereString[1],sqlTextWhereString[0]));
            break;
        }
        else if(clickedTabBrTextStatus[0] ==1 )
        {
            query.prepare(QObject::tr("select * from station where duan = '%1';").arg(sqlTextWhereString[0]));
            break;
        }
        else
        {
            query.prepare("select * from station;");
            break;
        }
    }

    query.exec();
    int index = 0;
    while(query.next())//station
    {
       deviceDuanModel->setItem(index,0,new QStandardItem(query.value(0).toString()));//deviceon
       deviceDuanModel->setItem(index,1,new QStandardItem(query.value(1).toString()));//deviceon
       deviceDuanModel->setItem(index,2,new QStandardItem(query.value(2).toString()));//deviceon
       deviceDuanModel->setItem(index,3,new QStandardItem(query.value(3).toString()));//deviceon
       deviceDuanModel->setItem(index,5,new QStandardItem(query.value(5).toString()));
       deviceDuanModel->setItem(index,6,new QStandardItem(query.value(4).toString()));
       deviceDuanModel->item(index,0)->setTextAlignment(Qt::AlignCenter);
       deviceDuanModel->item(index,1)->setTextAlignment(Qt::AlignCenter);
       deviceDuanModel->item(index,2)->setTextAlignment(Qt::AlignCenter);
       deviceDuanModel->item(index,3)->setTextAlignment(Qt::AlignCenter);
       deviceDuanModel->item(index,5)->setTextAlignment(Qt::AlignCenter);
       deviceDuanModel->item(index,6)->setTextAlignment(Qt::AlignCenter);
//***
       QSqlQuery queryDevice;//device
       queryDevice.prepare(QObject::tr("select deviceid from device where duan = '%1' and jian = '%2' and qu = '%3' and station ='%4';").arg(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString()));
       qDebug()<<QObject::tr("select qu from qu where jian = %1 ;").arg(query.value(1).toString());
       queryDevice.exec();
       int deviceAccount = 0;
       while(queryDevice.next())
       {
          qDebug()<<"*******:"<< queryDevice.value(0).toString();
           deviceAccount +=1;
       }
       deviceDuanModel->setItem(index,4,new QStandardItem(QString::number(deviceAccount)));//device
       deviceDuanModel->item(index,4)->setTextAlignment(Qt::AlignCenter);
        index += 1;
    }

    deviceDuanModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("所属电务段"));
    deviceDuanModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("所属车间"));
    deviceDuanModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("所属工区"));
    deviceDuanModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("车站名称"));
    deviceDuanModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备数量"));
    deviceDuanModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("联系人"));
    deviceDuanModel->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("联系电话"));
    deviceDuanModel->insertColumn(7);
    deviceDuanModel->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit(""));
    ui->tableView_5->horizontalHeader()->setStretchLastSection(true);

    ui->tableView_5->setModel(deviceDuanModel);

}


//jianFromWhat
void DeviceManagementForm::setDeviceJianFromWhat(QStandardItemModel *model,int index,QString Jian)
{
    QSqlQuery queryDuanFrom;
    queryDuanFrom.prepare(QObject::tr("select duan from jian where jian = '%1';").arg(Jian));
    queryDuanFrom.exec();
    while(queryDuanFrom.next())
    {
        model->setItem(index,0,new QStandardItem(queryDuanFrom.value(0).toString()));
        deviceDuanModel->item(index,0)->setTextAlignment(Qt::AlignCenter);
    }
}

//This is the first tab from tablewidget
void DeviceManagementForm::on_tableView_2_clicked(const QModelIndex &index)//1
{
    reFreshIndex = index;
    setDeviceRepositoryShow(index);
    tabBarCliicked[0] = true;
    tabBarCliicked[1] = false;
    tabBarCliicked[2] = false;
    tabBarCliicked[3] = false;
   // duan_tableviewClicked = true;

}

//
/*
 * device Management Control  for 4 tableview show from talbewidget
 * deviceReopsitoryShowSqlControl: tab control
 * sqlTextWhereString: sql control
 * sqlTextAll: exe sql
 *
*/
void DeviceManagementForm::setDeviceRepositoryShow(const QModelIndex &index)
{
    QString musicName;//代表当前TabBar对应的名字（电段，电间，电区，电站）
    QModelIndex modelindex;
    modelindex = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-1);// select current tableview cell thing
    qDebug()<<QString::fromLocal8Bit("行:")<<index.row();
    musicName = modelindex.data().toString();
    delSelectText = musicName;
    qDebug()<<QString::fromLocal8Bit("当前索引值:")<<musicName;

    QString sqlTextAll;
    if(deviceReopsitoryShowSqlControl ==1)//duan
    {
        sqlTextWhereString[0]=musicName;
        sqlTextWhereString[1] = "";
        sqlTextWhereString[2] = "";
        sqlTextWhereString[3] = "";
        sqlTextWhereString[4] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+4).data().toString();
        sqlTextWhereString[5] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+5).data().toString();

        clickedTabBrTextForSql[0]=sqlTextWhereString[0];
        clickedTabBrTextStatus[0] = 1;//代表段
        clickedTabBrTextStatus[1] = 0;
        clickedTabBrTextStatus[2] = 0;
        clickedTabBrTextStatus[3] = 0;
        whereText = sqlTextWhereString[0];
        sqlTextAll =QObject::tr("select duan,jian,qu,station,deviceid,ip,port from device where duan = '%1'").arg(sqlTextWhereString[0]);
    }
      else if(deviceReopsitoryShowSqlControl == 2)
    {
        sqlTextWhereString[1]=musicName;
        clickedTabBrTextForSql[1]=sqlTextWhereString[1];
        clickedTabBrTextStatus[1] = 1;//代表间
        clickedTabBrTextStatus[2] = 0;
        clickedTabBrTextStatus[3] = 0;
        sqlTextWhereString[0] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-2).data().toString();

        sqlTextWhereString[2] = "";
        sqlTextWhereString[3] = "";
        sqlTextWhereString[4] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+3).data().toString();
        sqlTextWhereString[5] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+4).data().toString();
        whereText = sqlTextWhereString[1];

         sqlTextAll =QObject::tr("select duan,jian,qu,station,deviceid,ip,port from device where duan = '%1' and jian = '%2'").arg(deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-2).data().toString(),sqlTextWhereString[1]);
    }
    else if(deviceReopsitoryShowSqlControl == 3)
    {
        sqlTextWhereString[0] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-3).data().toString();
        sqlTextWhereString[1]=deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-2).data().toString();;
        sqlTextWhereString[4] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+2).data().toString();
        sqlTextWhereString[5] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+3).data().toString();
        sqlTextWhereString[2]=musicName;

        sqlTextWhereString[3] = "";
        clickedTabBrTextForSql[2]=sqlTextWhereString[2];
        clickedTabBrTextStatus[2] = 1;//代表区
        clickedTabBrTextStatus[3] = 0;
        whereText = sqlTextWhereString[2];
         sqlTextAll =QObject::tr("select duan,jian,qu,station,deviceid,ip,port from device where duan = '%1' and jian ='%2' and qu = '%3'").arg(deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-3).data().toString(),deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-2).data().toString(),sqlTextWhereString[2]);
    }
    else if(deviceReopsitoryShowSqlControl == 4)
    {
        sqlTextWhereString[0]=deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-4).data().toString();;
        sqlTextWhereString[1] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-3).data().toString();
        sqlTextWhereString[2] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-2).data().toString();
        sqlTextWhereString[4] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+1).data().toString();
        sqlTextWhereString[5] = deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl+2).data().toString();
        sqlTextWhereString[3]=musicName;
        clickedTabBrTextForSql[3]=sqlTextWhereString[3];
        clickedTabBrTextStatus[3] = 1;//代表station
        whereText = sqlTextWhereString[3];
         sqlTextAll =QObject::tr("select duan,jian,qu,station,deviceid,ip,port from device where duan = '%1' and jian ='%2' and qu = '%3' and station = '%4'").arg(deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-4).data().toString(),deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-3).data().toString(),deviceDuanModel->index(index.row(),deviceReopsitoryShowSqlControl-2).data().toString(),sqlTextWhereString[3]);
    }


   qDebug()<<"musicName:"<<musicName;
   qDebug()<<"delSelectText:"<<delSelectText;
   qDebug()<<"deviceRepositoryShowSqlControl:"<<deviceReopsitoryShowSqlControl;

   qDebug()<<"sqlTextWhereString1:"<<sqlTextWhereString[0];
   qDebug()<<"sqlTextWhereString2:"<<sqlTextWhereString[1];
   qDebug()<<"sqlTextWhereString3:"<<sqlTextWhereString[2];
   qDebug()<<"sqlTextWhereString4:"<<sqlTextWhereString[3];
   qDebug()<<QString::fromLocal8Bit("联系人X:")<<sqlTextWhereString[4]<<sqlTextWhereString[5];

   qDebug()<<"sql:"<<sqlTextAll;


   model_TableView->setQuery(sqlTextAll);
   model_TableView->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("电务段"));
   model_TableView->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("车间"));
   model_TableView->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("工区"));
   model_TableView->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("车站"));
   model_TableView->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备号"));
   model_TableView->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("IP地址"));
   model_TableView->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("端口号码"));

   model_TableView->insertColumn(7);
   model_TableView->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit(" "));
   ui->tableView->horizontalHeader()->setStretchLastSection(true);


   ui->tableView->setModel(model_TableView);
}




void DeviceManagementForm::device_duan_dialog(QString buttonText)
{
    dialog = new QDialog();
    dialog->setWindowFlags(Qt::FramelessWindowHint);
    dialog->setWindowTitle(buttonText);
    dialog->setMaximumSize(400,230);
    dialog->setMinimumSize(400,230);

    box = new QGroupBox();
//    box->resize(380,160);
    box->setMinimumSize(380,160);

    QString boxText = QString::fromLocal8Bit("电段信息(*号项为必填项)");
    box->setTitle(boxText);
    button1 = new QPushButton();
     button2 = new QPushButton();
     layout = new QGridLayout();//窗体主布局
     QWidget *addDuan = new QWidget(dialog);//窗体主布局控件//局部布局样式
     addDuan->setGeometry(0,30,400,200);


     QWidget * addDuan_Title  = new QWidget(dialog);
//     addDuan_Title->setStyleSheet("background:#1077A0;");//标题widget背景
     addDuan_Title->setMinimumSize(400,30);
//     QPushButton * addDuanCloseButton = new QPushButton(addDuan_Title);
     addDuanCloseButton.setParent(addDuan_Title);
     addDuanCloseButton.setText("x");
     addDuanCloseButton.setGeometry(370,0,30,30);
     addDuanCloseButton.setStyleSheet("background:#9400D3;");



    layout2 = new QGridLayout(addDuan);


    QString okButton = buttonText.mid(0,2);

    button1->setText(okButton);
    button1->setMinimumHeight(25);
    button2->setText(QString::fromLocal8Bit("取消"));
    button2->setMinimumHeight(25);
    button1->setFixedWidth(80);
    button2->setFixedWidth(80);

    layout3 = new QGridLayout(addDuan);
    QLabel * vLabel = new QLabel;
    vLabel->setText("SSSSS");
//    layout3->addWidget(vLabel,2,1);
    layout3->addWidget(button1,1,1,1,1);
    layout3->addWidget(button2,1 ,2,1,1);
    QLabel * label =new QLabel;
    label->setText(QString::fromLocal8Bit("电  段:"));

    QLabel * label2 =new QLabel;
    label2->setText(QString::fromLocal8Bit("联系人:"));
    QLabel * label3 =new QLabel;
    label3->setText(QString::fromLocal8Bit("电  话:"));
    lineEdit = new QLineEdit();
    lineEdit2 = new QLineEdit();
    lineEdit3 = new QLineEdit();
    label->setFixedWidth(50);
    label2->setFixedWidth(50);
    label3->setFixedWidth(50);
    lineEdit->setFixedWidth(200);
    lineEdit2->setFixedWidth(200);
    lineEdit3->setFixedWidth(200);

     label4  = new QLabel;
    label4->setText(QObject::tr("  * "));
    label4->setMinimumWidth(10);
    layout2->addWidget(label4,1,4,1,1);


    layout2->addWidget(label,1,1,1,1,Qt::AlignVCenter);//The first label
    layout2->addWidget(label2,2,1,1,1);//联系人
    layout2->addWidget(label3,3,1,1,1);//tel
    layout2->addWidget(lineEdit,1,2,1,2);//The first lineEdit
    layout2->addWidget(lineEdit2,2,2,1,2);
    layout2->addWidget(lineEdit3,3,2,1,2);
    qDebug()<<"alterNoSelectFlag"<<alterNoSelectFlag;
    if(alterNoSelectFlag)//duan 选择标志
    {
        lineEdit->setText(sqlTextWhereString[0]);
        lineEdit->setEnabled(false);

        QSqlQuery query;
        query.prepare(QObject::tr("select telephone,contact from duan where duan = '%1'").arg(sqlTextWhereString[0]));
        query.exec();
        while(query.next())
        {
            lineEdit2->setText(query.value(0).toString());
            lineEdit3->setText(query.value(1).toString());
        }
        connect(button1,SIGNAL(clicked()),this,SLOT(okAlterAndCancelInfomation()));//alter
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//cancel

    }else
    {
        connect(button1,SIGNAL(clicked()),this,SLOT(okAddAndCancelInfomation()));//add
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//cancel
    }




   layout2->setHorizontalSpacing(0);
   layout2->setVerticalSpacing(5);
   layout2->setContentsMargins(50,5,5,5);
   layout2->setColumnStretch(10,1);
   // layout2->setr
     box->setLayout(layout2);
     layout->setHorizontalSpacing(0);
//     layout->setVerticalSpacing(10);

     layout->setContentsMargins(5,5,5,5);
     layout->addWidget(box, 0,0);

     layout->addWidget(vLabel,1,0);

     layout->addLayout(layout3,2,0);




//    dialog->setLayout(layout);
      addDuan->setLayout(layout);
    dialog->exec();
    alterNoSelectFlag = false;
   // dialog->show();
}
//******************添加****************
//*************************************
//*************************************
void DeviceManagementForm::on_pushButton_16_clicked()//duan_jian_qu_station-Button 添加
{
    if(userAccessControl)// 1:admin    0:public
    {
        QString buttonText = ui->pushButton_16->text();
        qDebug()<<"currentIndex"<<ui->tabWidget_2->tabBar()->currentIndex();
        if(ui->tabWidget_2->tabBar()->currentIndex() == 0)
        {
//            device_duan_dialog(buttonText);
            emit toDialogForJudgeAddOrAlter(false,sqlTextWhereString);
            addDuan->exec();
        }
         else if(ui->tabWidget_2->tabBar()->currentIndex() == 1)
        {
//            device_jian_dialog(buttonText);
            emit toAddOrAlterJianDialogForAlterJian(false,sqlTextWhereString);
            addJian->exec();
        }
        else if(ui->tabWidget_2->tabBar()->currentIndex() == 2)
        {
            emit toDialogForJudgeAddOrAlter(false,sqlTextWhereString);
            addQu->exec();
        }
        else if(ui->tabWidget_2->tabBar()->currentIndex() == 3)
        {
            emit toDialogForJudgeAddOrAlter(false,sqlTextWhereString);
            addStation->exec();
        }
    }else
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }


}
void DeviceManagementForm::device_jian_dialog(QString buttonText)//JIAN
{
    dialog = new QDialog();
    dialog->setWindowTitle(buttonText);
    dialog->setMaximumSize(400,200);
    dialog->setMinimumSize(400,200);
    box = new QGroupBox();
    box->resize(380,160);
    box->setMinimumSize(380,160);

    QString boxText = QString::fromLocal8Bit("电间信息(*号项为必填项)");
    box->setTitle(boxText);
    button1 = new QPushButton();
     button2 = new QPushButton();
     layout = new QGridLayout();
    layout2 = new QGridLayout();

    QString okButton = buttonText.mid(0,2);//截取

    button1->setText(okButton);
    button2->setText(QString::fromLocal8Bit("取消"));
    button1->setFixedWidth(80);
    button2->setFixedWidth(80);

    layout3 = new QGridLayout();

    layout3->addWidget(button1,2,1,1,1);
    layout3->addWidget(button2,2 ,2,1,1);
    QLabel * label =new QLabel;
    label->setText(QString::fromLocal8Bit("电  间:"));
    QLabel * label2 =new QLabel;
    label2->setText(QString::fromLocal8Bit("联系人:"));
    QLabel * label3 =new QLabel;
    label3->setText(QString::fromLocal8Bit("电  话:"));
    lineEdit = new QLineEdit();
    lineEdit2 = new QLineEdit();
    lineEdit3 = new QLineEdit();
    label->setFixedWidth(50);
    label2->setFixedWidth(50);
    label3->setFixedWidth(50);
    lineEdit->setFixedWidth(200);
    lineEdit2->setFixedWidth(200);
    lineEdit3->setFixedWidth(200);


    combobox = new QComboBox;
    QLabel * label5 = new QLabel;

    label5->setText(QString::fromLocal8Bit("电  段:"));

    QMSqlQueryModel * model = new QMSqlQueryModel;
    model->setQuery("select duan from duan");
    combobox->setModel(model);
    combobox->setMinimumWidth(200);

     label4  = new QLabel;
    label4->setText(QObject::tr("  * "));

    layout2->addWidget(label5,0,1,1,1);
    layout2->addWidget(combobox,0,2,1,1);
    layout2->addWidget(label,1,1,1,1);//Jian
    layout2->addWidget(label2,2,1,1,1);
    layout2->addWidget(label3,3,1,1,1);

    layout2->addWidget(lineEdit,1,2,1,2);// jianlineEdit

    layout2->addWidget(lineEdit2,2,2,1,2);
    layout2->addWidget(lineEdit3,3,2,1,2);
    layout2->addWidget(label4,1,3,1,1);
    if(alterNoSelectFlag)//修改
    {
        combobox->setCurrentText(sqlTextWhereString[0]);
        lineEdit->setText(sqlTextWhereString[1]);

        combobox->setEnabled(false);
        lineEdit->setEnabled(false);

        QSqlQuery query;
        query.prepare(QObject::tr("select telephone,contact from jian where duan = '%1' and jian = '%2'").arg(sqlTextWhereString[0],sqlTextWhereString[1]));
        query.exec();
        while(query.next())
        {
            lineEdit2->setText(query.value(0).toString());
            lineEdit3->setText(query.value(1).toString());
        }
        connect(button1,SIGNAL(clicked()),this,SLOT(okAlterAndCancelInfomation()));//alter
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//cancel
    }else//添加
    {
        QString sql_Tmp = lineEdit->text();
        connect(button1,SIGNAL(clicked()),this,SLOT(okAddAndCancelInfomation()));//add
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//cancel


    }





   layout2->setHorizontalSpacing(0);
   layout2->setVerticalSpacing(5);
   layout2->setContentsMargins(50,5,5,1);
   // layout2->setr
     box->setLayout(layout2);
     layout->setHorizontalSpacing(0);
     layout->setContentsMargins(5,5,5,5);
     layout->addWidget(box, 0,0);
     layout->addLayout(layout3,1,0);


    dialog->setLayout(layout);
    dialog->exec();
    alterNoSelectFlag = false;
}

void DeviceManagementForm::device_qu_dialog(QString buttonText)//qu
{
    dialog = new QDialog();
    dialog->setWindowTitle(buttonText);
    dialog->setMaximumSize(400,200);
    dialog->setMinimumSize(400,200);
    box = new QGroupBox();
    box->resize(380,160);
    box->setMinimumSize(380,160);

    QString boxText = QString::fromLocal8Bit("电区信息(*号项为必填项)");
    box->setTitle(boxText);
    button1 = new QPushButton();
     button2 = new QPushButton();
     layout = new QGridLayout();
    layout2 = new QGridLayout();

    QString okButton = buttonText.mid(0,2);

    button1->setText(okButton);
    button2->setText(QString::fromLocal8Bit("取消"));
    button1->setFixedWidth(80);
    button2->setFixedWidth(80);

    layout3 = new QGridLayout();

    layout3->addWidget(button1,2,1,1,1);
    layout3->addWidget(button2,2 ,2,1,1);
    QLabel * label =new QLabel;
    label->setText(QString::fromLocal8Bit("电  区:"));
    QLabel * label2 =new QLabel;
    label2->setText(QString::fromLocal8Bit("联系人:"));
    QLabel * label3 =new QLabel;
    label3->setText(QString::fromLocal8Bit("电  话:"));
    lineEdit = new QLineEdit();
    lineEdit2 = new QLineEdit();
    lineEdit3 = new QLineEdit();
    label->setFixedWidth(50);
    label2->setFixedWidth(50);
    label3->setFixedWidth(50);
    lineEdit->setFixedWidth(200);
    lineEdit2->setFixedWidth(200);
    lineEdit3->setFixedWidth(200);
    combobox = new QComboBox;
    QLabel * label5 = new QLabel;

    label5->setText(QString::fromLocal8Bit("电  段:"));

    QMSqlQueryModel * model = new QMSqlQueryModel;
    model->setQuery("select duan from duan");
    combobox->setModel(model);
    combobox->setMinimumWidth(200);

    combobox_jian = new QComboBox;
    QLabel * label_jian = new QLabel;
    label_jian->setText(QString::fromLocal8Bit("电  间:"));
    combobox_jian->setMinimumWidth(200);


     label4  = new QLabel;
    label4->setText(QObject::tr("  * "));
    layout2->addWidget(label5,0,1,1,1);
    layout2->addWidget(label_jian,1,1,1,1);

    layout2->addWidget(combobox,0,2,1,1);
    layout2->addWidget(combobox_jian,1,2,1,1);


    layout2->addWidget(label,3,1,1,1,Qt::AlignVCenter);
    layout2->addWidget(label2,4,1,1,1);
    layout2->addWidget(label3,5,1,1,1);
    layout2->addWidget(lineEdit,3,2,1,2);
    layout2->addWidget(lineEdit2,4,2,1,2);
    layout2->addWidget(lineEdit3,5,2,1,2);
    layout2->addWidget(label4,3,3,1,1);//***
    if(alterNoSelectFlag)
    {
        combobox->setCurrentText(sqlTextWhereString[0]);
        combobox_jian->addItem(sqlTextWhereString[1]);
        qDebug()<<sqlTextWhereString[1];
        lineEdit->setText(sqlTextWhereString[2]);

        combobox->setEnabled(false);
        combobox_jian->setEnabled(false);
        lineEdit->setEnabled(false);

//****************
        QSqlQuery query;
        query.prepare(QObject::tr("select telephone,contact from qu where duan = '%1' and jian = '%2' and qu = '%3'").arg(sqlTextWhereString[0],sqlTextWhereString[1],sqlTextWhereString[2]));
        query.exec();
        while(query.next())
        {
            lineEdit2->setText(query.value(0).toString());
            lineEdit3->setText(query.value(1).toString());
        }
        connect(button1,SIGNAL(clicked()),this,SLOT(okAlterAndCancelInfomation()));//alter
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//cancel

    }else
    {
        connect(button1,SIGNAL(clicked()),this,SLOT(okAddAndCancelInfomation()));//add
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//cancel

        connect(this->combobox,SIGNAL(currentTextChanged(QString)),SLOT(tab_Qu_Add_For_Jian(QString)));
    }


   layout2->setHorizontalSpacing(0);
   layout2->setVerticalSpacing(5);
   layout2->setContentsMargins(50,5,5,5);
   //layout2->columnStretch(1,3,1);
   // layout2->setr
     box->setLayout(layout2);
     layout->setHorizontalSpacing(0);
     layout->setContentsMargins(5,5,5,5);
     layout->addWidget(box, 0,0);
     layout->addLayout(layout3,1,0);


    dialog->setLayout(layout);
    dialog->exec();
    alterNoSelectFlag = false;
}


void DeviceManagementForm::device_station_dialog(QString buttonText)//station  // There are have a BIG BUG no solve
{
    dialog = new QDialog();
    dialog->setWindowTitle(buttonText);
    dialog->setMaximumSize(450,250);
    dialog->setMinimumSize(450,250);
    box = new QGroupBox();
    box->resize(420,210);
    box->setMinimumSize(420,210);

    QString boxText = QString::fromLocal8Bit("电站信息(*号项为必填项)");
    box->setTitle(boxText);
    QPushButton *  button1 = new QPushButton();
     QPushButton * button2 = new QPushButton();
     layout = new QGridLayout();
    layout2 = new QGridLayout();

    QString okButton = buttonText.mid(0,2);

    button1->setText(okButton);
    button2->setText(QString::fromLocal8Bit("取消"));
    button1->setFixedWidth(80);
    button2->setFixedWidth(80);

    layout3 = new QGridLayout();

    layout3->addWidget(button1,2,1,1,1);
    layout3->addWidget(button2,2 ,2,1,1);
    QLabel * label =new QLabel;
    label->setText(QString::fromLocal8Bit("电  站:"));
    QLabel * label2 =new QLabel;
    label2->setText(QString::fromLocal8Bit("联系人:"));
    QLabel * label3 =new QLabel;
    label3->setText(QString::fromLocal8Bit("电  话:"));
    lineEdit = new QLineEdit();
    lineEdit2 = new QLineEdit();
    lineEdit3 = new QLineEdit();
    label->setFixedWidth(50);
    label2->setFixedWidth(50);
    label3->setFixedWidth(50);
    lineEdit->setFixedWidth(200);
    lineEdit2->setFixedWidth(200);
    lineEdit3->setFixedWidth(200);
    QLabel * label5 = new QLabel;

    combobox_station = new QComboBox;
    label5->setText(QString::fromLocal8Bit("电  段:"));

    QMSqlQueryModel * model = new QMSqlQueryModel;
    model->setQuery("select duan from duan");
    combobox_station->setModel(model);
    combobox_station->setMinimumWidth(200);

    combobox_jian = new QComboBox;
    QLabel * label_jian = new QLabel;
    label_jian->setText(QString::fromLocal8Bit("电  间:"));
    combobox_jian->setMinimumWidth(200);


    combobox_qu = new QComboBox;
    QLabel * label_qu = new QLabel;
    label_qu->setText(QString::fromLocal8Bit("电  区:"));
    combobox_qu->setMinimumWidth(200);

    label4  = new QLabel;
    label4->setText(QObject::tr("  * "));
    layout2->addWidget(label5,0,1,1,1);
    layout2->addWidget(label_jian,1,1,1,1);
    layout2->addWidget(label_qu,2,1,1,1);
    layout2->addWidget(combobox_station,0,2,1,1);
    layout2->addWidget(combobox_jian,1,2,1,1);
    layout2->addWidget(combobox_qu,2,2,1,1);

    layout2->addWidget(label,3,1,1,1,Qt::AlignVCenter); //电站
    layout2->addWidget(label2,4,1,1,1);//联系人
    layout2->addWidget(label3,5,1,1,1);//电话
    layout2->addWidget(lineEdit,3,2,1,2);
    layout2->addWidget(lineEdit2,4,2,1,2);
    layout2->addWidget(lineEdit3,5,2,1,2);
    layout2->addWidget(label4,3,3,1,1);//***
    if(alterNoSelectFlag)//修改标志
    {
        combobox_station->setCurrentText(sqlTextWhereString[0]);
        combobox_jian->addItem(sqlTextWhereString[1]);
         combobox_qu->addItem(sqlTextWhereString[2]);
        lineEdit->setText(sqlTextWhereString[3]);

        combobox_station->setEnabled(false);
        combobox_jian->setEnabled(false);
        combobox_qu->setEnabled(false);
        lineEdit->setEnabled(false);


//****************
        QSqlQuery query;
        query.prepare(QObject::tr("select telephone,contact from station where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4'").arg(sqlTextWhereString[0],sqlTextWhereString[1],sqlTextWhereString[2],sqlTextWhereString[3]));
        query.exec();
        while(query.next())
        {
            lineEdit2->setText(query.value(0).toString());//默认显示 lineEdit
            lineEdit3->setText(query.value(1).toString());
        }


        connect(button1,SIGNAL(clicked()),this,SLOT(okAlterAndCancelInfomation()));//修改
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//修改取消
    }else
    {
        connect(button1,SIGNAL(clicked()),this,SLOT(okAddAndCancelInfomation()));//add
        connect(button2,SIGNAL(clicked()),this,SLOT(cancelAddDuanInfomation()));//cancel

        combobox_jian->addItem("TTTTT");
        combobox_qu->addItem("QQQQQ");
///////////*********************BUG*****************////////////
      connect(this->combobox_station,SIGNAL(currentTextChanged(QString)),SLOT(tab_Station_Add_For_comboBox(QString)));//QU_ComboBOx_TO_DUAN
      QComboBox * boxT = new QComboBox;
      connect(this->combobox_jian,SIGNAL(currentTextChanged(QString)),SLOT(tab_Station_Add_For_Qu_comboBox(QString)));//QU_ComboBox_TO_JIAN
    }


   layout2->setHorizontalSpacing(0);
   layout2->setVerticalSpacing(5);
   layout2->setContentsMargins(65,5,5,5);
   //layout2->columnStretch(1,3,1);
   // layout2->setr
     box->setLayout(layout2);
     layout->setHorizontalSpacing(0);
     layout->setContentsMargins(5,5,5,5);
     layout->addWidget(box, 0,0);
     layout->addLayout(layout3,1,0);



    dialog->setLayout(layout);
    dialog->exec();
    alterNoSelectFlag = false;

}

void DeviceManagementForm::on_pushButton_18_clicked()//修改电段
{
    if(userAccessControl)//1 :admin  0:public
    {
        QString buttonText = ui->pushButton_18->text();
        qDebug()<<"delSelectText:"<<delSelectText;
        //delSelectText
        if(delSelectText == "NULL")//复用delSelectText
        {
            iMessageBox box;
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("请选择一条记录!"));
            box.exec();
        }else
        {
            //qDebug()<<"设置选择："<<;
            //**********There is del all of data what is select**************

            if(ui->tabWidget_2->tabBar()->currentIndex() == 0)
            {
                emit toDialogForJudgeAddOrAlter(true,sqlTextWhereString);  //
                alterNoSelectFlag = true;

//                device_duan_dialog(buttonText);
                alterDuan->exec();
            }
            else if(ui->tabWidget_2->tabBar()->currentIndex() == 1)
            {
                emit toAddOrAlterJianDialogForAlterJian(true,sqlTextWhereString);
                alterJian->exec();
                alterNoSelectFlag = true;
//                device_jian_dialog(buttonText);
            }
            else if(ui->tabWidget_2->tabBar()->currentIndex() == 2)
            {
                 alterNoSelectFlag = true;
                 emit toDialogForJudgeAddOrAlter(true,sqlTextWhereString);
                 alterQu->exec();
//                 device_qu_dialog(buttonText);
            }
            else if(ui->tabWidget_2->tabBar()->currentIndex() == 3)
            {
                 alterNoSelectFlag = true;
                 emit toDialogForJudgeAddOrAlter(true,sqlTextWhereString);
                 alterStation->exec();
//                 device_station_dialog(buttonText);
            }
        }
    }else
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }

}

void DeviceManagementForm::on_pushButton_17_clicked()//删除
{
    if(userAccessControl)
    {
        if(delSelectText == "NULL")
        {
            iMessageBox box;
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("请选择一条记录!"));
            box.exec();
        }else
        {
            iMessageBox box;
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("该操作将删除该级以下所有数据!!!"));
            box.exec();

            //**********There is del all of data what is select**************
        }
        //*******************删除sql*******************
        QSqlQuery query;
        iMessageBox box;
        if(ui->tabWidget_2->tabBar()->currentIndex() == 0)//
        {
            query.prepare(QObject::tr("delete from duan where duan = '%1'").arg(sqlTextWhereString[0]));
            if(query.exec())
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"prompt");
                box.exec();
            }else
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"error");
                box.exec();
            }
            setDeviceDuan();
        }else if(ui->tabWidget_2->tabBar()->currentIndex() == 1)
        {
            query.prepare(QObject::tr("delete from jian where jian = '%1'").arg(sqlTextWhereString[1]));
            if(query.exec())
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"prompt");
                box.exec();
            }else
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"error");
                box.exec();
            }
            setDeviceJian();
        }else if(ui->tabWidget_2->tabBar()->currentIndex() == 2)
        {
            query.prepare(QObject::tr("delete from qu where qu = '%1'").arg(sqlTextWhereString[2]));
            if(query.exec())
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"prompt");
                box.exec();
            }else
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"error");
                box.exec();
            }
            setDeviceQu();
        }else if(ui->tabWidget_2->tabBar()->currentIndex() == 3)
        {
            query.prepare(QObject::tr("delete from station where station = '%1'").arg(sqlTextWhereString[3]));
            if(query.exec())
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"prompt");
                box.exec();
            }else
            {
                box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"error");
                box.exec();
            }
            setDeviceStation();
        }
    } else
        {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
        }


}


/*
 * All tableview control direct to **on_tableView_2_clicked()**
*/
//Now  tab 3 and tab 4

//This is the second tab from tablewidget
void DeviceManagementForm::on_tableView_3_clicked(const QModelIndex &index)//2
{
    on_tableView_2_clicked(index);
    //jian_tableviewClicked = true;
}

void DeviceManagementForm::on_tableView_4_clicked(const QModelIndex &index)
{
     on_tableView_2_clicked(index);
     //qu_tableviewClicked = true;
}

void DeviceManagementForm::on_tableView_5_clicked(const QModelIndex &index)
{
     on_tableView_2_clicked(index);
}


void DeviceManagementForm::okAddAndCancelInfomation()//ok add slot 添加
{
    QString tabName;
    QString boxMessageText;
    QString sqlText;
    QString sqlInsertText;
    QString sqlTabBarSelectText;
    tabName =  ui->tabWidget_2->tabBar()->tabText(ui->tabWidget_2->tabBar()->currentIndex());
    if(tabName == QString::fromLocal8Bit("电段"))
        sqlTabBarSelectText ="duan";
    else if(tabName == QString::fromLocal8Bit("电间"))
    {
        sqlTabBarSelectText ="jian";

    }
    else if(tabName == QString::fromLocal8Bit("电区"))
        sqlTabBarSelectText = "qu";
    else if(tabName == QString::fromLocal8Bit("电站"))
        sqlTabBarSelectText = "station";
    qDebug()<<"tabName"<<tabName;
    boxMessageText = QString::fromLocal8Bit("请输入") + tabName + QString::fromLocal8Bit("名字！");
    bool duanYes = false;
    QSqlQuery query;
    QString lineEditText = this->lineEdit->text();
    qDebug()<<"lineEditText"<<lineEditText;
    //sqlText 存在不存在
     sqlText = QString::fromLocal8Bit("select ")+ sqlTabBarSelectText + QString::fromLocal8Bit(" from ") + sqlTabBarSelectText +QString::fromLocal8Bit(" where ")+sqlTabBarSelectText+QObject::tr(" = '%1'").arg(lineEditText);
     qDebug()<<"ssssssssssssssssssssssssssssssss";
     qDebug()<<"ui->tabWidget_2->tabBar()->currentIndex()"<<ui->tabWidget_2->tabBar()->currentIndex();
//    if(ui->tabWidget_2->tabBar()->currentIndex() == 0)
//    {
//     //   sqlInsertText = QString::fromLocal8Bit("insert into ")+sqlTabBarSelectText+QObject::tr(" (%1) ").arg(sqlTabBarSelectText)+QString::fromLocal8Bit(" values ")+QObject::tr(" ('%1') ").arg(lineEditText);
//        qDebug()<<"---------------------------------:"<<this->combobox->currentText();
//    }

     //选择不同标签的sql语句
     if(ui->tabWidget_2->tabBar()->currentIndex() == 0)
     {
         sqlInsertText = QObject::tr("insert into duan(duan,telephone,contact) values('%1','%2','%3');").arg(lineEditText,this->lineEdit2->text(),this->lineEdit3->text());
     }else if(ui->tabWidget_2->tabBar()->currentIndex() == 1)
     {
         sqlInsertText = QObject::tr("insert into jian(duan,jian,telephone,contact) values('%1','%2','%3','%4');").arg(this->combobox->currentText(),this->lineEdit->text(),this->lineEdit2->text(),this->lineEdit3->text());
     }else if(ui->tabWidget_2->tabBar()->currentIndex() == 2)
     {
         sqlInsertText = QObject::tr("insert into qu(duan,jian,qu,telephone,contact) values('%1','%2','%3','%4','%5');").arg(this->combobox->currentText(),this->combobox_jian->currentText(),this->lineEdit->text(),this->lineEdit2->text(),this->lineEdit3->text());
     }else if(ui->tabWidget_2->tabBar()->currentIndex() == 3)
     {
         sqlInsertText = QObject::tr("insert into station(duan,jian,qu,station,telephone,contact) values('%1','%2','%3','%4','%5','%6');").arg(this->combobox_station->currentText(),this->combobox_jian->currentText(),this->combobox_qu->currentText(),this->lineEdit->text(),this->lineEdit2->text(),this->lineEdit3->text());
     }
/*
 *There have a BIG BUG  please
 *
 *这里设置combobox选择
 *
 ******************************
*/


    qDebug()<<"length:"<<lineEditText.length();
    qDebug()<<"sql"<<sqlText;
    qDebug()<<"sqlInsertText:"<<sqlInsertText;
    if(lineEditText=="")// 为空
    {
        QMessageBox * box = new QMessageBox;
        box->setText(boxMessageText);
        box->exec();
    }
    else//数据库已经存在
    {
      query.prepare(sqlText);
      query.exec();
      while(query.next())
      {
          QMessageBox * box = new QMessageBox;
          QString boxMessageText2 = tabName +QString::fromLocal8Bit("名已存在,请输入其他名字！");

          box->setText(boxMessageText2);
          duanYes = true;
          box->exec();
      }
      if(!duanYes)//如果已经存在 该变量已经扩展到适用 段 间 区 站
      {
            query.prepare(sqlInsertText);
            query.exec();
            QMessageBox * box = new QMessageBox;
            box->setText(QString::fromLocal8Bit("添加成功"));
            qDebug()<<"ddddddddddd"<<sqlInsertText;
            int status = box->exec();
            if(status == QMessageBox::Ok)
            {
                dialog->close();
                if(ui->tabWidget_2->tabBar()->currentIndex() == 0)
                {
                    setDeviceDuan();
                }else if(ui->tabWidget_2->tabBar()->currentIndex() == 1)
                {
                    setDeviceJian();
                }else if(ui->tabWidget_2->tabBar()->currentIndex() == 2)
                {
                    setDeviceQu();
                }else if(ui->tabWidget_2->tabBar()->currentIndex() == 3)
                {
                   setDeviceStation();
                }
            }
      }
    }
    qDebug()<<lineEditText;
}
void DeviceManagementForm::cancelAddDuanInfomation()//cancel slot
{
dialog->close();
}


void DeviceManagementForm::okAlterAndCancelInfomation()
{

    qDebug()<<"lineEdit2:"<<this->lineEdit2->text();
    qDebug()<<"lineEdit3:"<<this->lineEdit3->text();
    sqlOperation(this->lineEdit2->text(),this->lineEdit3->text());

    QMessageBox * box = new QMessageBox;
    box->setText(QString::fromLocal8Bit("修改成功"));
    int status = box->exec();
    if(status == QMessageBox::Ok)
    {
        dialog->close();
    }
    dialog->close();

}

void DeviceManagementForm::sqlOperation(QString newTel,QString newContact)
{
    QSqlQuery query;
    setAlterUpdateSql(newTel,newContact);
    qDebug()<<"sql:"<<sql;
    query.prepare(sql);
    query.exec();
}

void DeviceManagementForm::setAlterUpdateSql(QString newTel,QString newContact)
{
    sql_duan = QObject::tr("update duan set telephone ='%1',contact = '%2' where duan = '%3'").arg(newTel,newContact,whereText);
    sql_jian = QObject::tr("update jian set telephone ='%1',contact = '%2' where jian = '%3'").arg(newTel,newContact,whereText);
    sql_qu = QObject::tr("update qu set telephone ='%1',contact = '%2' where qu = '%3'").arg(newTel,newContact,whereText);
    sql_station = QObject::tr("update station set telephone ='%1',contact = '%2' where station = '%3'").arg(newTel,newContact,whereText);
    if(ui->tabWidget_2->tabBar()->currentIndex() == 0)
        sql=sql_duan;
    if(ui->tabWidget_2->tabBar()->currentIndex() == 1)
        sql=sql_jian;
    if(ui->tabWidget_2->tabBar()->currentIndex() == 2)
        sql=sql_qu;
    if(ui->tabWidget_2->tabBar()->currentIndex() == 3)
        sql=sql_station;
}


void DeviceManagementForm::tab_Qu_Add_For_Jian(QString string)
{
    this->combobox_jian->clear();
    QSqlQuery query;
    QString sql_tmp = QObject::tr("select jian from jian where duan = '%1';").arg(this->combobox->currentText());
    query.prepare(sql_tmp);//加入间combobox_jian (区添加)
    qDebug()<<"3-----------1"<<sql_tmp;
    qDebug()<<"JJJJJJJJJJJJ:"<<query.exec();
    while(query.next())
    {
        qDebug()<<"string:"<<query.value(0).toString();
        combobox_jian->addItem(query.value(0).toString());
    }
}


void DeviceManagementForm::tab_Station_Add_For_comboBox(QString)
{
    this->combobox_jian->clear();
    QSqlQuery query;
    QString sql_tmp = QObject::tr("select jian from jian where duan = '%1';").arg(this->combobox_station->currentText());
    query.prepare(sql_tmp);//加入间combobox_jian (区添加)
    qDebug()<<"3-----------1"<<sql_tmp;
    qDebug()<<"JJJJJJJJJJJJ:"<<query.exec();
    while(query.next())
    {
        qDebug()<<"string:"<<query.value(0).toString();
        combobox_jian->addItem(query.value(0).toString());
    }
}



void DeviceManagementForm::tab_Station_Add_For_Qu_comboBox(QString)
{
    this->combobox_qu->clear();
    QSqlQuery query;
    query.prepare(QObject::tr("select qu from qu where duan = '%1' and jian = '%2';").arg(this->combobox_station->currentText(),this->combobox_jian->currentText()));//加入间combobox_jian (区添加)
    query.exec();
    while(query.next())
    {
        qDebug()<<"string:"<<query.value(0).toString();
        combobox_qu->addItem(query.value(0).toString());
    }
}




//void DeviceManagementForm::clickedToTavleview_3()
//{
//        QMSqlQueryModel * queryModel = new QMSqlQueryModel;
//        queryModel->setQuery(QObject::tr("select "));
//}

//NOW del button



void DeviceManagementForm::on_tableView_clicked(const QModelIndex &index)
{
    tableviewClickedControl = true;
    QMSqlQueryModel modelQ;
    QAbstractItemModel  * model = ui->tableView->model();//获取当前tableview数据模型
    tableviewClickedText[0] = model->index(index.row(),0).data().toString();
    tableviewClickedText[1] = model->index(index.row(),1).data().toString();
    tableviewClickedText[2] = model->index(index.row(),2).data().toString();
    tableviewClickedText[3] = model->index(index.row(),3).data().toString();
    tableviewClickedText[4] = model->index(index.row(),4).data().toString();

      //  qDebug()<<index.row();
      //  qDebug()<<"zichuan "<<index.data().toString();
        //qDebug()<<"QQQQ"<<model->index(1,0).data().toString();
        qDebug()<<"TTTTT:"<<tableviewClickedText[0];
}


void DeviceManagementForm::setTableViewStart()
{
    QString sql = QObject::tr("select duan,jian,qu,station,deviceid,ip,port from device where duan = '%1'").arg("");
    model_TableView->setQuery(sql);
    model_TableView->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("电务段"));
    model_TableView->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("车间"));
    model_TableView->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("工区"));
    model_TableView->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("车站"));
    model_TableView->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备号"));
    model_TableView->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("IP地址"));
    model_TableView->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("端口号"));
    ui->tableView->setModel(model_TableView);
    setDeviceDuan();
}

void DeviceManagementForm::on_pushButton_3_clicked()
{
    iMessageBox box;
    if(userAccessControl)//1:admin  0:public
    {
        QString sql;
        if(!tableviewClickedControl)
        {

            box.setUserMessage(QString::fromLocal8Bit("请选择要删除的设备!"),"error");
            box.exec();
        }else
        {
            QSqlQuery * delDeviceQuery = new QSqlQuery;
            //获取sql路径
            global *getDelSql = new global;
            sql = getDelSql->delDeviceFromMysql(tableviewClickedText);
            qDebug()<<"delDeviceSql:"<<sql;
            box.setUserMessage(QString::fromLocal8Bit("删除成功!"),"prompt");
            delDeviceQuery->prepare(sql);
            delDeviceQuery->exec();
            box.exec();
             reFreshTableview(3);
        }
            tableviewClickedControl = false;
//            this->reFreshTableview();
//            this->reFreshTableview_X();
    }else
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }

}




void DeviceManagementForm::reFreshTableview_X()
{
//    on_tabWidget_2_tabBarClicked(0);
}


void DeviceManagementForm::fromMainWindowForAccessControl(bool userAccessType)
{
    userAccessControl = userAccessType;
//   {//用来调试权限控制初期的
//        if(!userAccessType)//1:admin 0:public
//        {
//            ui->pushButton->setEnabled(false);
//            ui->pushButton_2->setEnabled(false);
//            ui->pushButton_3->setEnabled(false);

//            ui->pushButton_16->setEnabled(false);
//            ui->pushButton_17->setEnabled(false);
//            ui->pushButton_18->setEnabled(false);
//        }
//    }

}

//添加和修改用同一个槽
void DeviceManagementForm::ForUpdateTableview_2_Show(QString type)
{
    qDebug()<<QString::fromLocal8Bit("刷新tableview");
     delSelectText = "NULL";
     if(type == "duan")
     setDeviceDuan();
     else if(type =="jian")
     setDeviceJian();
     else if(type == "qu")
     setDeviceQu();
     else if(type == "station")
     setDeviceStation();
}


void DeviceManagementForm::on_pushButton_4_clicked()
{
    setDeviceDuan();
    setDeviceJian();
    setDeviceQu();
    setDeviceStation();
}

void DeviceManagementForm::on_pushButton_5_clicked()
{
    QSqlQuery query;
    QString sql = "select duan,jian,qu,station,deviceid,ip,port from device ";
    if(query.exec(sql))
    {
        while(query.next())
        {
            qDebug()<<"Successful!";
                model_TableView->setQuery(sql);
                ui->tableView->setModel(model_TableView);
        }
    }else
    {

    }
}


void DeviceManagementForm::fromAddDeviceDialogForSentAddInfo(QString string[])
{
    for(int i = 0;i<7;i++)
    {
        reFlushString[i] = string[i];

        qDebug()<<QString::fromLocal8Bit("传递过来:")<<string[i];
    }
    reFreshTableview(1);
}

void DeviceManagementForm::reFreshTableview(int Type)
{
     QString sql ;
    if(Type ==1)
    sql = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid,ip,`port` from device  where duan ='%1' and jian = '%2' and qu = '%3' and station = '%4'").arg(reFlushString[0],reFlushString[1],reFlushString[2],reFlushString[3]);
    else if(Type == 2 || Type  == 3)
        sql = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid,ip,`port` from device  where duan ='%1' and jian = '%2' and qu = '%3' and station = '%4'").arg(tableviewClickedText[0],tableviewClickedText[1],tableviewClickedText[2],tableviewClickedText[3]);

   qDebug()<<"SSQL:"<<sql;
    ui->tableView->setModel(model_TableView);
    model_TableView->setQuery(sql);
}
