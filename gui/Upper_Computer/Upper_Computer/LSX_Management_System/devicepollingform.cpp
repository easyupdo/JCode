
#include "devicepollingform.h"
#include "ui_devicepollingform.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>
#include <QSqlRecord>
#include <QComboBox>
#include <app/mysqlsupport.h>
#include <app/global.h>
#include "app/delegateaddiconforsqlqyery.h"
#include "addpollingform.h"
#include <QMessageBox>
#include "alterpollingform.h"
#include "app/qmsqlquerymodel.h"
#include "app/qmtableviewdelegate.h"
DevicePollingForm::DevicePollingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevicePollingForm)
{
    ui->setupUi(this);
    userAccessControl = false;
    checkOver = false;
    checkPollingOneTimes = 0;
    startPollingControlFlag = 0;
    globalSql = new global();
    queryModel = new QMSqlQueryModel;
    first = 0;
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    defaultInitAllComboBox();
    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    QMTableviewDelegate * delegate = new QMTableviewDelegate;

    ui->tableView->setItemDelegateForColumn(5,delegate);
    ui->tableView->setItemDelegateForColumn(7,delegate);
    ui->tableView->setItemDelegateForColumn(11,delegate);

    initCombobox();

    allControlFlag = 1;
    allControlTableViewFlag = 0;
    cleckedFlag = false;

    //巡查 添加 修改 双击
    addPollingdevice = new addPollingForm();
    connect(addPollingdevice,SIGNAL(toDevicePolling_addOK()),this,SLOT(fromAddpolling_addOk()));
    alterPollingdevice = new alterPollingForm;
    connect(alterPollingdevice,&alterPollingForm::toDevicePollingForClearUserSelectConotrol,this,&DevicePollingForm::fromAlterPollingForClearUserSelectConotrol);

    //*************************************************************************************************************************
    //第一版双击显示故障信息
//    doubleClecked = new doubleCleckedForm;

    /*三个ui的combobox string*/
//    connect(this,SIGNAL(toDoubleClecked(QString *)),doubleClecked,SLOT(fromPollingDevice(QString*)));//双击显示故障
    connect(this,SIGNAL(toAddPolling(QString *)),addPollingdevice,SLOT(fromPollingDevice(QString*)));
    connect(this,SIGNAL(toAlterPolling(QString *)),alterPollingdevice,SLOT(fromPollingDevice(QString*)));

    ui->checkBox->setChecked(true);
    setTableviewRightClikedMenu();


//    //voicePlay
//    voice = new RealTimeDeviceControlForm;
//    connect(this,&DevicePollingForm::toRealTimeDeviceControlForm,voice,&RealTimeDeviceControlForm::fromDevicePollingForm);
//    voice->setWindowModality(Qt::ApplicationModal);
//    voice->setWindowTitle(QString::fromLocal8Bit("语音调听"));
    setTableView();
}

DevicePollingForm::~DevicePollingForm()
{
    delete ui;
}

void DevicePollingForm::addComboboxString()
{
    QStringList stringList;
    stringList<<"TestPolling";
    stringList.append("HHH");
    ui->comboBox->addItems(stringList);
    QSqlQuery  query("select duan from duan");
    query.exec();
    QString currentData;
    while(query.next())
    {
        QString forCombobox= query.value(0).toString();
        if(currentData!=forCombobox)
        ui->comboBox->addItem(forCombobox);
        currentData=forCombobox;
    }
}

void DevicePollingForm::addComboboxString(QString selectText,QComboBox*box,int indexComboBox)
{
    QSqlQuery  query(globalSql->returenComBoxCurrentText(selectText,indexComboBox));
    qDebug()<<"NOW:"<<globalSql->returenComBoxCurrentText(selectText,indexComboBox);
    query.exec();
    qDebug()<<"last:"<<query.lastQuery();
    QString currentData;
    box->clear();
    while(query.next())
    {
        QString forCombobox= query.value(0).toString();
        qDebug()<<"what"<<forCombobox;
        if(currentData!=forCombobox)
             box->addItem(forCombobox);
        currentData=forCombobox;
    }
   // queryModel = new QMSqlQueryModel();
    QString whereText;
    if(indexComboBox == 0)
        whereText = "duan";
    else if(indexComboBox == 1)
        whereText = "jian";
    else if(indexComboBox == 2)
        whereText = "qu";
    else if(indexComboBox == 3)
        whereText = "station";
    QString test =  QObject::tr ("select * from `check` where %1 = '%2'").arg(whereText,selectText);//BUG选择查询条件不够
    qDebug()<<"test:"<<test;
    queryModel->setQuery(test);
    ui->tableView->setModel(queryModel);



}



void DevicePollingForm::defaultInitAllComboBox()
{
   // QMSqlQueryModel *queryModel = new QMSqlQueryModel;
    queryModel->setQuery("select duan,jian,qu,station,deviceid,currentstate,content,checkstate,starttime,span,historytime,errorcount from `check`");

  // queryModel->setQuery(sql);
    queryModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("电务段"));
    queryModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("车间"));
    queryModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工区"));
    queryModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("车站"));
    queryModel->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("设备"));
    queryModel->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("设备状态"));
    queryModel->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("巡检内容"));
    queryModel->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("上次巡检结果"));
    queryModel->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("巡检设置时间"));
    queryModel->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("巡检间隔"));
    queryModel->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("下次巡检时间"));
    queryModel->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("俄日查看故障次数"));
    queryModel->insertColumn(12);
    queryModel->setHeaderData(12, Qt::Horizontal, QString::fromLocal8Bit(""));
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->tableView->setModel(queryModel);
//comboBox_2
}

void DevicePollingForm::initOtherComboBom_Jian(QString duanSelect)
{
    ui->comboBox_2->clear();
    QString comboBoxText=QString::fromLocal8Bit("*")+QString::fromLocal8Bit("全部")+QString::fromLocal8Bit("*");
    ui->comboBox_2->addItem(comboBoxText);
    QSqlQuery query;
    QString sqlText = QObject::tr("SELECT jian FROM jian  WHERE duan ='%1';").arg(duanSelect);
    qDebug()<<sqlText;
    query.prepare(sqlText);
    query.exec();
    QStringList stringList;
    int index = 0;
    while(query.next())
    {
        index+=1;
        stringList<<query.value(0).toString();
        if(index == 1)
        forQu_Jian = query.value(0).toString();

    }
    ui->comboBox_2->addItems(stringList);

}

void DevicePollingForm::initOtherComboBom_Qu(QString duanSelect)
{
    ui->comboBox_3->clear();
    QString comboBoxText=QString::fromLocal8Bit("*")+QString::fromLocal8Bit("全部")+QString::fromLocal8Bit("*");
    ui->comboBox_3->addItem(comboBoxText);
    QSqlQuery query;
    QString sqlText = QObject::tr("SELECT qu FROM qu  WHERE duan ='%1' and jian = '%2';").arg(forJian_Duan,duanSelect);
    qDebug()<<sqlText;
    query.prepare(sqlText);
    query.exec();
    QStringList stringList;
    int index = 0;
    while(query.next())
    {
        index+=1;
        stringList<<query.value(0).toString();
        if(index == 1)
        forStation_Qu = query.value(0).toString();
    }
    ui->comboBox_3->addItems(stringList);

}

void DevicePollingForm::initOtherComboBom_Station(QString duanSelect)
{
    ui->comboBox_4->clear();
    QString comboBoxText=QString::fromLocal8Bit("*")+QString::fromLocal8Bit("全部")+QString::fromLocal8Bit("*");
    ui->comboBox_4->addItem(comboBoxText);
    QSqlQuery query;
    QString sqlText = QObject::tr("SELECT station FROM station  WHERE duan ='%1' and jian = '%2' and qu ='%3';").arg(forJian_Duan,forQu_Jian,duanSelect);
    qDebug()<<sqlText;
    query.prepare(sqlText);
    query.exec();
    QStringList stringList;
    int index = 0;
    while(query.next())
    {
        index+=1;
        stringList<<query.value(0).toString();
        if(index == 1)
        forDevice_Station =query.value(0).toString();
    }
    ui->comboBox_4->addItems(stringList);
}

void DevicePollingForm::initOtherComboBom_Device(QString duanSelect)//not used NOW
{
    ui->comboBox_5->clear();
    QString comboBoxText=QString::fromLocal8Bit("*")+QString::fromLocal8Bit("全部")+QString::fromLocal8Bit("*");
    ui->comboBox_5->addItem(comboBoxText);
    QSqlQuery query;
    QString sqlText = QObject::tr("SELECT deviceid FROM device  WHERE duan ='%1' and jian = '%2' and qu ='%3' and station ='%4' ").arg(forJian_Duan,forQu_Jian,forStation_Qu,duanSelect);
    qDebug()<<sqlText;
    query.prepare(sqlText);
    query.exec();
    QStringList stringList;
    int index = 0;
    while(query.next())
    {
        index+=1;
        stringList<<query.value(0).toString();
       // forDevice_Station =query.value(0).toString();

    }
    ui->comboBox_5->addItems(stringList);

    qDebug()<<"GG:"<<forJian_Duan;
    comBox = QObject::tr("SELECT duan,jian,qu,station,deviceid,currentState,content,checkstate,starttime,span,historytime,errorcount FROM `check` ");
    comBox1 = QObject::tr("SELECT duan,jian,qu,station,deviceid,currentState,content,checkstate,starttime,span,historytime,errorcount FROM `check`where duan = '%1'").arg(forJian_Duan);
    comBox2 =QObject::tr("SELECT duan,jian,qu,station,deviceid,currentState,content,checkstate,starttime,span,historytime,errorcount FROM `check`where duan = '%1' and jian = '%2'").arg(forJian_Duan,forQu_Jian);
    comBox3 = QObject::tr("SELECT duan,jian,qu,station,deviceid,currentState,content,checkstate,starttime,span,historytime,errorcount FROM `check`where duan = '%1' and jian = '%2' and qu = '%3'").arg(forJian_Duan,forQu_Jian,forStation_Qu);
    comBox4 = QObject::tr("SELECT duan,jian,qu,station,deviceid,currentState,content,checkstate,starttime,span,historytime,errorcount FROM `check`where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4'").arg(forJian_Duan,forQu_Jian,forStation_Qu,forDevice_Station);
    comBox5 = QObject::tr("SELECT duan,jian,qu,station,deviceid,currentState,content,checkstate,starttime,span,historytime,errorcount FROM `check`where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4' and deviceid = '%5'").arg(forJian_Duan,forQu_Jian,forStation_Qu,forDevice_Station,forDevice);
}


QString DevicePollingForm::flushOperation()
{
    cleckedFlag = false;
    qDebug()<<"******:"<<allControlFlag;
    QString string;
    if(allControlFlag == 1)
        string = ui->comboBox->currentText();
    else if(allControlFlag == 2)
            string =  ui->comboBox_2->currentText();
    else if(allControlFlag == 3)
        string = ui-> comboBox_3->currentText();
    else if(allControlFlag == 4)
        string = ui->comboBox_4->currentText();
    else
        string = ui->comboBox_5->currentText();

    return string;
}


void DevicePollingForm::setTableView(QString string)//update not used NOW
{
    QString sqlText;
    cleckedFlag = false; //改变既需重点

    qDebug()<<"string；"<<string;
    qDebug()<<"allControlFlag:"<<allControlFlag;
    if(allControlFlag == 1)
    {
       if(string == allControlString)
       {
           sqlText = comBox;
           allControlTableViewFlag = 1;
       }else
       {
            sqlText = comBox1;
            allControlTableViewFlag = 0;
       }
    }
    else if(allControlFlag == 2)
    {
        if(allControlTableViewFlag != 1)
        {
            if(string == allControlString)
            {
                sqlText = comBox1;
                qDebug()<<"dddddddddddd";
            }else
            sqlText = comBox2;
        }else
        {
            qDebug()<<"swweee";
            sqlText = comBox;
        }
    }
    else if(allControlFlag == 3)
    {
        if(allControlTableViewFlag != 1)
        {
            if(string == allControlString)
            {
                sqlText = comBox2;
            }else
            sqlText = comBox3;
        }else
            sqlText = comBox;
    }
    else if (allControlFlag == 4)
    {
        if(allControlTableViewFlag != 1)
        {
            if(string == allControlString)
            {
                sqlText = comBox3;
            }else
            sqlText = comBox4;
         }else
            sqlText = comBox;
     }else
    {
        if(string == allControlString)
        {
            sqlText = comBox4;
        }
    }
//重写 选择 业务逻辑
    queryModel->setQuery(sqlText);
    ui->tableView->setModel(queryModel);
qDebug()<<"time test 1";
/*time test 1 --time test 2中间点击选择全部时间需要优化*/
    queryModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("电务段"));
    queryModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("车间"));
    queryModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工区"));
    queryModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("车站"));
    queryModel->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("设备"));
    queryModel->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("设备状态"));
    queryModel->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("巡检内容"));
    queryModel->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("上次巡检结果"));
    queryModel->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("巡检设置时间"));
    queryModel->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("巡检间隔"));
    queryModel->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("下次巡检时间"));
    queryModel->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("未查看故障次数"));
   qDebug()<<"time test2 ";
    queryModel->insertColumn(12);
    queryModel->setHeaderData(12, Qt::Horizontal, QString::fromLocal8Bit(""));
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//最后一列自适应
    qDebug()<<"sdsdddd:"<<allControlTableViewFlag;
    qDebug()<<sqlText;


}






void DevicePollingForm::on_pushButton_2_clicked()//add
{
    if(userAccessControl)//1:admin  0:public
    {
        qDebug()<<"源"<< ui->comboBox->currentText();
        QString addVlues[5];
        addVlues[0] = ui->comboBox->currentText();
        addVlues[1] = ui->comboBox_2->currentText();
        addVlues[2] = ui->comboBox_3->currentText();
        addVlues[3] = ui->comboBox_4->currentText();
        addVlues[4] = ui->comboBox_5->currentText();

        emit toAddPolling(addVlues);
        addPollingdevice->show();

         this->setTableView();
    }else
    {

        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }
}


void DevicePollingForm::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex modelIndex;

    for(int i = 0 ;i<5;i++)
    {
        modelIndex  =  queryModel->index(index.row(),i);
        toDoubleCleckedString[i] = modelIndex.data().toString();

        qDebug()<<modelIndex.data().toString();
    }

//    doubleClecked->show();
//    emit toDoubleClecked(toDoubleCleckedString);
}

void DevicePollingForm::on_pushButton_3_clicked()//alter
{
    if(userAccessControl)//1:admin   0:public
    {
        if(cleckedFlag)//user select control
        {
            alterPollingdevice->show();
            emit toAlterPolling(toCleckedString);

        }else
        {
            iMessageBox box;
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("请选择一个巡检项进行修改!"));
            box.exec();
        }
    }else
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }

}

void DevicePollingForm::on_tableView_pressed(const QModelIndex &index)
{
    cleckedFlag  =  true;
    QModelIndex modelIndex;

    for(int i = 0 ;i<8;i++)
    {
        if(i == 5 )
        {
            modelIndex  =  queryModel->index(index.row(),i+1);
            toCleckedString[i] = modelIndex.data().toString();//toCleckedString[5] =内容,toCleckedString[6] == 开始时间toCleckedString[7] == 时间间隔
            qDebug()<<"i == 5:"<<modelIndex.data().toString();
        }else if(i == 6 || i == 7)
        {
            modelIndex  =  queryModel->index(index.row(),i+2);
            toCleckedString[i] = modelIndex.data().toString();//toCleckedString[5] =内容,toCleckedString[6] == 开始时间toCleckedString[7] == 时间间隔
            qDebug()<<"i == 6 / 7:"<<modelIndex.data().toString();
        }else
        {
            modelIndex  =  queryModel->index(index.row(),i);
            toCleckedString[i] = modelIndex.data().toString();//toCleckedString[5] =内容,toCleckedString[6] == 开始时间toCleckedString[7] == 时间间隔
            qDebug()<<"i ='%1':"<<modelIndex.data().toString();
        }
    }
}

void DevicePollingForm::on_pushButton_clicked()//Delete
{
    if(userAccessControl) //1:admin  0:public
    {
        if(!cleckedFlag)
        {
            iMessageBox box;
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("请选择要删除的巡检项!"));
            box.exec();
        }else
        {
            iMessageBox box;
            box.setMessageType("ask");
            box.setMessageText(QString::fromLocal8Bit("确认要删除所选巡检项吗?"));
            QString sql = QString::fromLocal8Bit("delete from `check` where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4' and deviceid = '%5' and content = '%6'").arg(toCleckedString[0],toCleckedString[1],toCleckedString[2],toCleckedString[3],toCleckedString[4],toCleckedString[5]);
            if(box.exec() == 1)
            {
                QSqlQuery query;
                query.prepare(sql);
                iMessageBox box;
                box.setMessageType("error");
                if(!query.exec())
                {
                    box.setMessageText(QString::fromLocal8Bit("数据库操作错误！"));
                }else
                {
                    qDebug()<<"Polling delete sql:"<<sql;
                    box.setMessageText(QString::fromLocal8Bit("已删除!"));
                    box.exec();
                }
            }
        }
        this->setTableView();
    }else
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("当前登录用户非管理员,仅具备查看权限! 如需修改,请使用管理员账户登录!"));
        box.exec();
    }
}



//void DevicePollingForm::on_pushButton_4_clicked()
//{
//    qDebug()<<allControlFlag;
//   QString string = this->flushOperation();
//   qDebug()<<"S______T:"<<string;
//    this->setTableView();
//}


void DevicePollingForm::initCombobox()//toCombobox
{

    QString initCombobox_X_data =QString::fromLocal8Bit("*全部*");
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();

    ui->comboBox->addItem(initCombobox_X_data);
    ui->comboBox_2->addItem(initCombobox_X_data);
    ui->comboBox_3->addItem(initCombobox_X_data);
    ui->comboBox_4->addItem(initCombobox_X_data);
    ui->comboBox_5->addItem(initCombobox_X_data);
    QString sql = QString::fromLocal8Bit("select duan from duan ");
    addCombobox_X_data(ui->comboBox,sql,0);
    setTableView();

}



void DevicePollingForm::on_comboBox_activated(const QString &arg1)
{
    QString sql = QString::fromLocal8Bit("select jian from jian where duan ='%1'").arg(arg1);
    addCombobox_X_data(ui->comboBox_2,sql,1);
    setTableView();
}

void DevicePollingForm::on_comboBox_2_activated(const QString &arg1)//toCombobox_3
{
    QString sql = QString::fromLocal8Bit("select qu from qu where duan ='%1'and jian ='%2'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText());
    addCombobox_X_data(ui->comboBox_3,sql,2);
    setTableView();
}

void DevicePollingForm::on_comboBox_3_activated(const QString &arg1)//toCombobox_4
{
    QString sql = QString::fromLocal8Bit("select station from station where duan ='%1'and jian ='%2' and qu ='%3'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText());
    addCombobox_X_data(ui->comboBox_4,sql,3);
    setTableView();
}

void DevicePollingForm::on_comboBox_4_activated(const QString &arg1)//toCombobox_5
{
    QString sql = QString::fromLocal8Bit("select deviceid from device where duan ='%1'and jian ='%2' and qu ='%3'and station = '%4'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText());
    addCombobox_X_data(ui->comboBox_5,sql,4);
    setTableView();
}

void DevicePollingForm::on_comboBox_5_activated(const QString &arg1)
{
    QString sql = QString::fromLocal8Bit("select deviceid from device where duan ='%1'and jian ='%2' and qu ='%3'and station = '%4' and deviceid = '%5'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText(),ui->comboBox_5->currentText() );
   // addCombobox_X_data(ui->comboBox_5,sql,5);
    setTableView();
}

void DevicePollingForm::addCombobox_X_data(QComboBox * combox,QString sql,int whichCombobox)
{

    qDebug()<<"whichCombobox"<<whichCombobox;
    if(whichCombobox == 1)
    {


            ui->comboBox_2->clear();
            ui->comboBox_3->clear();
            ui->comboBox_4->clear();
            ui->comboBox_5->clear();

            ui->comboBox_2->addItem(QString::fromLocal8Bit("*全部*"));
            ui->comboBox_3->addItem(QString::fromLocal8Bit("*全部*"));
            ui->comboBox_4->addItem(QString::fromLocal8Bit("*全部*"));
            ui->comboBox_5->addItem(QString::fromLocal8Bit("*全部*"));

    }else if(whichCombobox==2)
    {
        if(ui->comboBox_2->currentText() == QString::fromLocal8Bit("*全部*"))
        {
            ui->comboBox_3->clear();
            ui->comboBox_3->addItem(QString::fromLocal8Bit("*全部*"));
            ui->comboBox_4->clear();
            ui->comboBox_4->addItem(QString::fromLocal8Bit("*全部*"));
            ui->comboBox_5->clear();
            ui->comboBox_5->addItem(QString::fromLocal8Bit("*全部*"));
        }
    }else if(whichCombobox == 3)
    {
        if(ui->comboBox_3->currentText() == QString::fromLocal8Bit("*全部*"))
        {
            ui->comboBox_4->clear();
            ui->comboBox_4->addItem(QString::fromLocal8Bit("*全部*"));
            ui->comboBox_5->clear();
            ui->comboBox_5->addItem(QString::fromLocal8Bit("*全部*"));
        }
    }else if(whichCombobox == 4)
    {
        if(ui->comboBox_4->currentText() == QString::fromLocal8Bit("*全部*"))
        {
            ui->comboBox_5->clear();
            ui->comboBox_5->addItem(QString::fromLocal8Bit("*全部*"));
        }
    }


    QMessageBox box;
    QSqlQuery query;
    query.prepare(sql);
    int status  = query.exec();
    if(!status)
    {
        box.setText(QString::fromLocal8Bit("数据库错误！"));
        int bStatus = box.exec();
        if(bStatus == QMessageBox::Ok)
            box.close();
    }
    combox->clear();
    combox->addItem(QString::fromLocal8Bit("*全部*"));
    while(query.next())
    {
        combox->addItem(query.value(0).toString());
    }
}

// next add tableview

void DevicePollingForm::setTableView()
{
    this->cleckedFlag =false;
    QString sql;
    QString selectWhat = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid,currentstate,content,currentState,checkstate,starttime,span,historytime,errorcount ");
    if(ui->comboBox->currentText() == QString::fromLocal8Bit("*全部*"))
    {
        sql = selectWhat + QString::fromLocal8Bit("from `check`");
    }else if(ui->comboBox_2->currentText()==QString::fromLocal8Bit("*全部*"))
    {
        sql = selectWhat + QString::fromLocal8Bit("from `check` where duan = '%1'").arg(ui->comboBox->currentText());
    }else if(ui->comboBox_3->currentText()==QString::fromLocal8Bit("*全部*"))
    {
        sql = selectWhat + QString::fromLocal8Bit("from `check` where duan = '%1' and jian = '%2'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText());
    }else if(ui->comboBox_4->currentText()==QString::fromLocal8Bit("*全部*"))
    {
         sql = selectWhat + QString::fromLocal8Bit("from `check` where duan = '%1' and jian = '%2' and qu ='%3'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText());
    }else if(ui->comboBox_5->currentText()==QString::fromLocal8Bit("*全部*"))
    {
        sql = selectWhat + QString::fromLocal8Bit("from `check` where duan = '%1' and jian = '%2' and qu ='%3' and station = '%4'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText());
    }else
    {
        sql = selectWhat + QString::fromLocal8Bit("from `check` where duan = '%1' and jian = '%2' and qu ='%3' and station = '%4' and deviceid = '%5'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText(),ui->comboBox_5->currentText());
    }

    qDebug()<<"setTableView:"<<sql;
    queryModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("电务段"));
    queryModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("车间"));
    queryModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工区"));
    queryModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("车站"));
    queryModel->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("设备"));
    queryModel->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("设备状态"));
    queryModel->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("巡检内容"));
    queryModel->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("上次巡检结果"));
    queryModel->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("巡检设置时间"));
    queryModel->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("巡检间隔"));
    queryModel->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("下次巡检时间"));
    queryModel->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("未查看故障次数"));
    qDebug()<<"time test2 ";
    queryModel->insertColumn(12);
    queryModel->setHeaderData(12, Qt::Horizontal, QString::fromLocal8Bit(""));
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//最后一列自适应
    queryModel->setQuery(sql);


    ui->tableView->setModel(queryModel);
}

void DevicePollingForm::fromAddpolling_addOk()
{
    this->setTableView();
}


void DevicePollingForm::fromMainWindowForAccessControl(bool userAccessType)
{
    userAccessControl = userAccessType;
//    {
    // 用来调试权限控制初期使用
    //    if(!userAccessType)// 1:admin  0:public
    //    {
    //        qDebug()<<QString::fromLocal8Bit("Public user");
    //        ui->pushButton->setEnabled(false);
    //        ui->pushButton_2->setEnabled(false);
    //        ui->pushButton_3->setEnabled(false);
    //    }
//}

}

void DevicePollingForm::fromAlterPollingForClearUserSelectConotrol()
{
    cleckedFlag = false;
    this->setTableView();
}




//开启巡查 后开始按照starttime尝试连接设备 测试 网络连接 是否完好
void DevicePollingForm::on_checkBox_clicked(bool checked)
{
//    checkPollingOneTimer.start(20000);//20 second 触发检测连接
    if(checked)
    {
        ui->checkBox->setEnabled(false);
        startPolling();
        qDebug()<<QString::fromLocal8Bit("开启巡检!");
    }
    else
    {
        ui->checkBox->setEnabled(false);
        qDebug()<<QString::fromLocal8Bit("触发终止信号");
        emit toReadyPollingListForStopThread();//终止列表线程信号
        emit toGroupWorkStopPollingDevice();//终止work线程信号
        qDebug()<<QString::fromLocal8Bit("等待终止信号");

        qDebug()<<QString::fromLocal8Bit("主线程收到清楚完毕信号");
    }
}


void DevicePollingForm::startPolling()
{
    //准备列表>>挑选其一个>>执行检查（执行完循环此操作）
    listThread = new QThread;
    readyWork = new readypollinglistwork;//列表线程
    readyWork->moveToThread(listThread);
//    readyWork.readyPollingList();
    listThread->start();//readyThreadList   准备ok
    //取消巡查 触发退出线程信号
    connect(listThread,&QThread::started,readyWork,&readypollinglistwork::readyPollingList);
    connect(listThread,&QThread::finished,this,&DevicePollingForm::clearListThread);
    connect(this,&DevicePollingForm::toReadyPollingListForStopThread,readyWork,&readypollinglistwork::fromDevicePollingFormForStopThread,Qt::DirectConnection);

    qDebug()<<QString::fromLocal8Bit("主线程:")<<this->thread();

//工作线程
    workThread = new  QThread;
    work = new groupwork;
    work->moveToThread(workThread);
    connect(readyWork,&readypollinglistwork::toGroupWorkForSentGroupSanmeDevice,work,&groupwork::fromReadyPollingListWorkForRecvGroupSanmeDevice);
    connect(this,&DevicePollingForm::toGroupWorkStopPollingDevice,work,&groupwork::fromDevicePollingForGroupWorkStopPollingDevice,Qt::DirectConnection);
    connect(workThread,&QThread::finished,this,&DevicePollingForm::clearWorkThread);
    workThread->start();

    ui->checkBox->setEnabled(true);

}



void DevicePollingForm::sleep(unsigned int msec)  //延时
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void DevicePollingForm::fromReadyPollingListForChoiceOK()
{
//    delete listThread;
//    delete readyWork;
}

void DevicePollingForm::clearListThread()
{
    listThread->wait();
    qDebug()<<"Clear ListThread";
    startPollingControlFlag += 1;
    disconnect(readyWork,0,0,0);
    disconnect(listThread,0,0,0);

    delete readyWork;
    delete listThread;

    if(startPollingControlFlag == 2 )
    {
        ui->checkBox->setEnabled(true);
        startPollingControlFlag = 0;
    }
    qDebug()<<QString::fromLocal8Bit("List Thread 清除完毕");

}

void DevicePollingForm::clearWorkThread()
{
    workThread->wait();
    qDebug()<<"Clear WorkThread";
    startPollingControlFlag += 1;
//    disconnect(listThread,0,0,0);
    delete work;
    delete workThread;

    if(startPollingControlFlag == 2 )
    {
        ui->checkBox->setEnabled(true);
        startPollingControlFlag = 0;
    }
    if(ui->checkBox->checkState() == Qt::Checked)
    {
        qDebug()<<QString::fromLocal8Bit("巡检状态,继续开始巡检");
        startPolling();
    }
}



void DevicePollingForm::fromMainWindowForStartPolling()
{
    startPolling();
}


void DevicePollingForm::setTableviewRightClikedMenu()
{
    playDeviceVoice = new QAction(this);
    faultDeviceInfo = new QAction(this);
    playDeviceVoice->setText(QString::fromLocal8Bit("语音调听"));
    faultDeviceInfo->setText(QString::fromLocal8Bit("故障查询"));
    ui->tableView->addAction(playDeviceVoice);
    ui->tableView->addAction(faultDeviceInfo);
    connect(playDeviceVoice,&QAction::triggered,this,&DevicePollingForm::playVoice);
    connect(faultDeviceInfo,&QAction::triggered,this,&DevicePollingForm::faultInfo);
}

//也要将当前socket地址发送给语音调听ui realtimedevicecontrolform
void DevicePollingForm::playVoice()
{

    /******************************************************************************************************
    * 测试实时监控 片段 已经改版
//从Map中获取该设备的socket 传送给语音调听直接使用
//    QTcpSocket * voiceSocket;
//    voiceSocket = getVoiceDeviceSocekt(toCleckedString[0],toCleckedString[1],toCleckedString[2],toCleckedString[3],toCleckedString[4]);
//    qDebug()<<QString::fromLocal8Bit("获取到的socket为:")<<voiceSocket;
//    system("pause");
//    emit toRealTimeDeviceControlForm(voiceSocket,toCleckedString);
********************************************************************************************************/
    emit toMainWindowForDeviceInfo(toCleckedString,LISTEN);//1:设备信息  2:调听界面
//    voice->show();
}

void DevicePollingForm::faultInfo()
{
    emit toMainWindowForDeviceInfo(toCleckedString,FAULT);//1:设备信息  2:调听界面
}


/************************************************************************************************************************************
 * 实时监控 用于为每一个设备开辟一个线程 一个socket
//为所有的 ·check·表中的设备分配socket，用于所有设备实时监控
void DevicePollingForm::startThreadForEveryCheckDevice()
{
    QString sql = QString::fromLocal8Bit("select `index`,duan,jian,qu,station,deviceid,currentstate,content,checkstate,starttime,span,historytime,errorcount from `check`where duan = 'ceshi'");
    QSqlQuery query;
    query.prepare(sql);
    int ret  = query.exec();
    qDebug()<<"SQL:"<<sql;
    int accout = 1;
    if(ret)
    {
        while(query.next())
        {
            int index = query.value(0).toInt();
            QString duan = query.value(1).toString();
            QString jian = query.value(2).toString();
            QString qu = query.value(3).toString();
            QString station = query.value(4).toString();
            QString deviceid = query.value(5).toString();
            qDebug()<<"Index value:"<<query.value(0).toInt()<<"account:"<<accout<<"index"<<index;


            Device_Socket_Key = {index,query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString()};

            accout+=1;

            deviceInfo = getCheckDeviceInfo(duan,jian,qu,station,deviceid);//获取check表中的设备的ip和port
//            deviceInfo.Socket = socket;
            qDebug()<<"deviceInfo:"<<deviceInfo.Ip<<deviceInfo.Port;
            qDebug()<<QString::fromLocal8Bit("主线程:")<<this->thread();


            //为一个设备开启线程  创建socket
//            RealTimeWork * realTimeWork =  new RealTimeWork();

//            connect(realTimeWork,&RealTimeWork::toDevicePollingFormForRecordSocketToMap,this,&DevicePollingForm::fromRealTimeWorkForRecordSocketToMap);
           //从realtimework发送过来socket和继续发送realtimeForm信号
//            connect(realTimeWork,&RealTimeWork::toDevicePollingForGotoRealTimeFrom,this,&DevicePollingForm::fromRealTimeWorkForGotoRealTimeForm);
            connect(this,&DevicePollingForm::toRealTimeDeviceControlFormForGotoProtocolMessage,voice,&RealTimeDeviceControlForm::fromDevicePollingFormForGotProtocolMessage);
            QThread * realTimeWorkThread = new QThread();
            realTimeWork->moveToThread(realTimeWorkThread);

            realTimeWorkThread->start();

            qDebug()<<QString::fromLocal8Bit("测试阻塞where!");
            realTimeWork->setDeviceConnectInfo(deviceInfo.Ip,deviceInfo.Port);//发送device的ip,port 并在该方法中分配该设备的socket
//            system("pause");
            qDebug()<<QString::fromLocal8Bit("执行一个设备完成!");

        }
    }
    qDebug()<<QString::fromLocal8Bit("执行完毕!");
    //    socket->connectToHost();
}
****************************************************************************************************************************************/
/***************************************************************************************************************************************
 * 用于实时监控  获取设备 ip 和 port信息
A_DEVICE_INFO DevicePollingForm::getCheckDeviceInfo(QString duan,QString jian,QString qu,QString station,QString deviceid)
{
    A_DEVICE_INFO device_Info;
    QSqlQuery query;
    QString sql = QString::fromLocal8Bit("select ip,port from device where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4' and deviceid = '%5'").arg(duan,jian,qu,station,deviceid);
    query.prepare(sql);
    int ret = query.exec();
    qDebug()<<"getCheckDeviceInfo exec sql";
    if(ret)
    {
        while(query.next())
        {
            device_Info.Ip = query.value(0).toString();
            device_Info.Port = query.value(1).toString();
            qDebug()<<"successful!";
        }
    }
    return device_Info;
}
******************************************************************************************************************************************/
/*****************************************************************
//测试实时监控
*****************************************************************/
/*****************************************************************************************************************************************
void DevicePollingForm::on_pushButton_4_clicked()
{
    startThreadForEveryCheckDevice();
}


//测试用于遍历
void DevicePollingForm::on_pushButton_5_clicked()
{
    //遍历Map
    QMap<A_DEVICE_SOCKET,QTcpSocket*>::Iterator it;
    int i = 0;
    for(it = Device_Socket_Map.begin();it!=Device_Socket_Map.end();++it)
    {

        qDebug()<<QString::fromLocal8Bit("Socket地址和大小:")<<it.value()<<Device_Socket_Map.size();
        qDebug()<<"Device_Socket_Map:"<<Device_Socket_Map.keys().at(i).Duan<<Device_Socket_Map.keys().at(i).Jian<<Device_Socket_Map.keys().at(i).Qu<<Device_Socket_Map.keys().at(i).Station<<Device_Socket_Map.keys().at(i).Deviceid;
        //        qDebug()<<"Device_Socket_MapBegin:"<Device_Socket_Map.keyBegin();
        i++;
    }
    sleep(3000);

            //    //key查询value
            //    A_DEVICE_SOCKET comKey;
            //    comKey.type = 188;//在结构中得有 type 用于定位整个所在的位置
            //    comKey.Duan = "ceshi";
            //    comKey.Jian = "s";
            //    comKey.Qu = "s";
            //    comKey.Station = "s";
            //    comKey.Deviceid = "0001";
            //    qDebug()<<QString::fromLocal8Bit("SC:")<<Device_Socket_Map[comKey];//Like arrary operation way


    qDebug()<<QString::fromLocal8Bit("输出完毕!");

}



void DevicePollingForm::on_pushButton_6_clicked()
{
//    emit toRealTimeWorkForDeviceInfo(deviceInfo.Socket,deviceInfo.Ip,deviceInfo.Port);
    qDebug()<<QString::fromLocal8Bit("发送信号");
}


QTcpSocket * DevicePollingForm::getVoiceDeviceSocekt(QString duan, QString jian, QString qu, QString station, QString deviceid)
{
    QMap<A_DEVICE_SOCKET,QTcpSocket*>::Iterator it;
    int i = 0;
    for(it = Device_Socket_Map.begin();it!=Device_Socket_Map.end();++it)
    {
        if(Device_Socket_Map.keys().at(i).Duan == duan &&
                Device_Socket_Map.keys().at(i).Jian == jian &&
                Device_Socket_Map.keys().at(i).Qu == qu &&
                Device_Socket_Map.keys().at(i).Station == station &&
                Device_Socket_Map.keys().at(i).Deviceid == deviceid)
        {
            qDebug()<<"Device_Socket_Map:"<<Device_Socket_Map.keys().at(i).Duan<<Device_Socket_Map.keys().at(i).Jian<<Device_Socket_Map.keys().at(i).Qu<<Device_Socket_Map.keys().at(i).Station<<Device_Socket_Map.keys().at(i).Deviceid;
            qDebug()<<QString::fromLocal8Bit("Socket地址和Map大小:")<<it.value()<<Device_Socket_Map.size();
            return Device_Socket_Map.value(Device_Socket_Map.keys().at(i));
        }
        i++;
    }
}


void DevicePollingForm::fromRealTimeWorkForRecordSocketToMap(QTcpSocket *socket)
{
    qDebug()<<QString::fromLocal8Bit("DevicePollingForm收到子线程发送来的socket");
    Device_Socket_Map.insert(Device_Socket_Key,socket);//To Map
}


void DevicePollingForm::fromRealTimeWorkForGotoRealTimeForm(QTcpSocket *socket)
{
    //发送给realtimeForm  信号
    qDebug()<<QString::fromLocal8Bit("PolingFrom接收到第一步信号");
    qDebug()<<QString::fromLocal8Bit("发送第二步信号");
    emit toRealTimeDeviceControlFormForGotoProtocolMessage(socket);
}

**************************************************************************************************************************************/
