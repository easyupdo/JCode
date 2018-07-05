#include "faultsearchdialog.h"
#include "ui_faultsearchdialog.h"
#include <QDebug>

faultSearchDialog::faultSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faultSearchDialog)
{
    ui->setupUi(this);
    ui->tableView->verticalScrollBar()->setEnabled(false);
    ui->tableView->verticalScrollBar()->setVisible(false);

    ui->lineEdit->setText("0");

    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    queryModel = new QSqlQueryModel;

    setComboBox();
    setFaultType();
    setComboBoxAllInit();




}

faultSearchDialog::~faultSearchDialog()
{
    delete ui;
}

void faultSearchDialog::setComboBox()
{
    QList<QString>items;
    items<<QString::fromLocal8Bit("设备")<<QString::fromLocal8Bit("故障类型");
    ui->comboBox_6->addItems(items);
    ui->comboBox_7->setEnabled(false);
    ui->label_7->setEnabled(false);
}


void faultSearchDialog::on_comboBox_6_activated(const QString &arg1)
{
    if(arg1 == QString::fromLocal8Bit("设备"))
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->comboBox_5->setEnabled(true);
        ui->comboBox_6->setEnabled(true);

        ui->label->setEnabled(true);
        ui->label_2->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->label_4->setEnabled(true);
        ui->label_5->setEnabled(true);

        ui->label_7->setEnabled(false);
        ui->comboBox_7->setEnabled(false);
    }else if(arg1 == QString::fromLocal8Bit("故障类型"))
    {
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);

        ui->label->setEnabled(false);
        ui->label_2->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->label_5->setEnabled(false);

        ui->label_7->setEnabled(true);
        ui->comboBox_7->setEnabled(true);
    }
}


void faultSearchDialog::setFaultType()
{
    QList<QString>items;
    items<<QString::fromLocal8Bit("网络连接失败")<<QString::fromLocal8Bit("网络连接成功了");
    ui->comboBox_7->addItems(items);
}


void faultSearchDialog::on_comboBox_7_activated(const QString &arg1)
{

}

//搜索
void faultSearchDialog::on_pushButton_clicked()
{
    QSqlQuery query;
    queryModel->clear();

    if(ui->comboBox_6->currentText() == QString::fromLocal8Bit("故障类型"))
    {
        QString sql = QString::fromLocal8Bit("select * from log where operation = '%1'").arg(ui->comboBox_7->currentText());
        if(ui->comboBox_7->currentText() == QString::fromLocal8Bit("网络连接失败"))
        {
            qDebug()<<QString::fromLocal8Bit("SQL:")<<sql;
            queryModel->setQuery(sql);
        }

        if(ui->comboBox_7->currentText() == QString::fromLocal8Bit("网络连接成功了"))
        {
            queryModel->setQuery(sql);
        }

    }

    //需要建故障信息表 包括 duan jian qu station deviceid
    if(ui->comboBox_6->currentText() == QString::fromLocal8Bit("设备"))
    {
        QString sql;
        if(ui->comboBox->currentText() == QString::fromLocal8Bit("全部"))
                sql = QString::fromLocal8Bit("select * from fault where opertype = 2");
        else if(ui->comboBox_2->currentText() == QString::fromLocal8Bit("全部"))
            sql = QString::fromLocal8Bit("select * from fault where duan = '%1' and opertype = 2").arg(ui->comboBox->currentText());
        else if(ui->comboBox_3->currentText() == QString::fromLocal8Bit("全部"))
            sql = QString::fromLocal8Bit("select * from fault where duan = '%1' and jian = '%2' and opertype = 2").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText());
        else if(ui->comboBox_4->currentText() == QString::fromLocal8Bit("全部"))
            sql = QString::fromLocal8Bit("select * from fault where duan = '%1' and jian = '%2' and qu = '%3' and opertype = 2").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText());
        else if(ui->comboBox_5->currentText() == QString::fromLocal8Bit("全部"))
            sql = QString::fromLocal8Bit("select * from fault where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4' and opertype = 2").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText());
        else
            sql = QString::fromLocal8Bit("select * from fault where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4' and deviceid = '%5' and opertype = 2").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText(),ui->comboBox_5->currentText());

        qDebug()<<"SSQQLL:"<<sql;
        queryModel->setQuery(sql);
    }
    ui->label_9->setText(QString::number(queryModel->rowCount()));
    setTableviewHeadview();
    ui->tableView->setModel(queryModel);

    int lPage = queryModel->rowCount()/(ui->tableView->verticalHeader()->height()/30);
    qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
    ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage+1) + QString::fromLocal8Bit("页"));
    if(lPage+1>0)
        ui->lineEdit->setText(QString::number(1));
}


void faultSearchDialog::setDevice_Duan_Jian_Qu_Station(QString what)
{
    QString sql;
    QComboBox *combox_ptr;
    if(what == "Duan")
    {
        sql = "select duan from duan";
        combox_ptr = ui->comboBox;
    }
    if(what == "Jian")
    {
        sql = QString::fromLocal8Bit("select jian from jian where duan = '%1'").arg(ui->comboBox->currentText());
        combox_ptr = ui->comboBox_2;
    }
    if(what == "Qu")
    {
        sql = QString::fromLocal8Bit("select qu from qu where duan = '%1' and jian = '%2'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText());
        combox_ptr  = ui->comboBox_3;
    }
    if(what == "Station")
    {
        sql = QString::fromLocal8Bit("select station from station where duan = '%1' and jian = '%2' and qu = '%3'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText());
        combox_ptr = ui->comboBox_4;
    }
    if(what == "Deviceid")
    {
        sql = QString::fromLocal8Bit("select deviceid from device where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText());
        combox_ptr = ui->comboBox_5;
    }

    combox_ptr->addItem(QString::fromLocal8Bit("全部"));
    QSqlQuery query;
    query.prepare(sql);
    int ret = query.exec();
    if(ret)
    {
        while(query.next())
        {
            combox_ptr->addItem(query.value(0).toString());
            qDebug()<<query.value(0).toString();
        }
    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("数据库错误:'%1'").arg(query.lastError().nativeErrorCode() + query.lastError().text()),"prompt");
        box.exec();
    }
}

void faultSearchDialog::setComboBoxAllInit()
{
    setDevice_Duan_Jian_Qu_Station("Duan");
    setDevice_Duan_Jian_Qu_Station("Jian");
    setDevice_Duan_Jian_Qu_Station("Qu");
    setDevice_Duan_Jian_Qu_Station("Station");
    setDevice_Duan_Jian_Qu_Station("Deviceid");
}

void faultSearchDialog::on_comboBox_activated(const QString &arg1)
{
    {
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_4->clear();
        ui->comboBox_5->clear();
    }
    setDevice_Duan_Jian_Qu_Station("Jian");
    setDevice_Duan_Jian_Qu_Station("Qu");
    setDevice_Duan_Jian_Qu_Station("Station");
    setDevice_Duan_Jian_Qu_Station("Deviceid");
}

void faultSearchDialog::on_comboBox_2_activated(const QString &arg1)
{
    {
        ui->comboBox_3->clear();
        ui->comboBox_4->clear();
        ui->comboBox_5->clear();
    }
    setDevice_Duan_Jian_Qu_Station("Qu");
    setDevice_Duan_Jian_Qu_Station("Station");
    setDevice_Duan_Jian_Qu_Station("Deviceid");
}


void faultSearchDialog::on_comboBox_3_activated(const QString &arg1)
{
    {
        ui->comboBox_4->clear();
        ui->comboBox_5->clear();
    }
    setDevice_Duan_Jian_Qu_Station("Station");
    setDevice_Duan_Jian_Qu_Station("Deviceid");
}

void faultSearchDialog::on_comboBox_4_activated(const QString &arg1)
{
    {
        ui->comboBox_5->clear();
    }
    setDevice_Duan_Jian_Qu_Station("Deviceid");
}

void faultSearchDialog::setDevice_Talveview()
{

//    queryModel->setQuery(sql);
//    ui->tableView->setModel(queryModel);
}

//显示全部
void faultSearchDialog::on_pushButton_2_clicked()
{
    QString sql = QString::fromLocal8Bit("select * from log ");
    queryModel->setQuery(sql);
    setTableviewHeadview();
    ui->tableView->setModel(queryModel);
    ui->label_9->setText(QString::number(queryModel->rowCount()));
//更新总页码
   int lPage = queryModel->rowCount()/(ui->tableView->verticalHeader()->height()/30);

    qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
    ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));
    if(lPage+1>0)
        ui->lineEdit->setText(QString::number(1));
}

void faultSearchDialog::setTableviewHeadview()
{
    queryModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("电务段"));
    queryModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("车间"));
    queryModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("工区"));
    queryModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("车站"));
    queryModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备id"));
    queryModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("操作内容"));
    queryModel->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("操作代码"));
    queryModel->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit("记录时间"));

    queryModel->insertColumn(8);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    queryModel->setHeaderData(8,Qt::Horizontal,QString::fromLocal8Bit(" "));


}

//后一页
void faultSearchDialog::on_pushButton_5_clicked()
{
        ui->tableView->verticalScrollBar()->setValue(ui->tableView->verticalScrollBar()->value() + ui->tableView->verticalHeader()->height()/30);
        QString string = ui->label_11->text().mid(1);
        int stringLength = string.length();
        QString pageNum = string.left(stringLength - 1);
        qDebug()<<QString::fromLocal8Bit("HHH")<<pageNum;
        qDebug()<<ui->lineEdit->text().toInt()<<ui->label_11->text().mid(1).toInt();

        if(ui->lineEdit->text().toInt() >= pageNum.toInt())
        {
            iMessageBox box;
            box.setUserMessage(QString::fromLocal8Bit("已经是最后一页了!"),"prompt");
            box.exec();
        }else
        ui->lineEdit->setText(QString::number(ui->lineEdit->text().toInt() + 1));

        //更新总页码
           int lPage = queryModel->rowCount()/(ui->tableView->verticalHeader()->height()/30);

            qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
            ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));

}

//前一页
void faultSearchDialog::on_pushButton_4_clicked()
{
    ui->tableView->verticalScrollBar()->setValue(ui->tableView->verticalScrollBar()->value() - ui->tableView->verticalHeader()->height()/30);

    if(ui->lineEdit->text().toInt() <= 1)
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("已经是第一页了!"),"prompt");
        box.exec();
    }else
    ui->lineEdit->setText(QString::number(ui->lineEdit->text().toInt() - 1));

    //更新总页码
       int lPage = queryModel->rowCount()/(ui->tableView->verticalHeader()->height()/30);

        qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
        ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));
}

//跳转
void faultSearchDialog::on_pushButton_7_clicked()
{

    int lPageNum = ui->lineEdit->text().toInt();
    qDebug()<<QString::fromLocal8Bit("跳转page")<<lPageNum;
    ui->tableView->verticalScrollBar()->setValue( ui->tableView->verticalHeader()->height()/30* lPageNum);
}

//首页
void faultSearchDialog::on_pushButton_3_clicked()
{
    ui->tableView->verticalScrollBar()->setValue( 0);
    ui->lineEdit->setText("1");

    //更新总页码
       int lPage = queryModel->rowCount()/(ui->tableView->verticalHeader()->height()/30);

        qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
        ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));
}

//尾页
void faultSearchDialog::on_pushButton_6_clicked()
{
    //更新总页码
    int lPage = queryModel->rowCount()/(ui->tableView->verticalHeader()->height()/30);
    ui->tableView->verticalScrollBar()->setValue( ui->tableView->verticalHeader()->height()/30* (lPage + 1));
    ui->lineEdit->setText(QString::number(lPage));

    qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
    ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));
}


void faultSearchDialog::fromMainWindowForDeviceInfo(QString *deviceInfo)
{
    for(int i = 0;i<5;i++)
        qDebug()<<"DeviceInfo:"<<deviceInfo[i];

    ui->comboBox->setCurrentText(deviceInfo[0]);
    on_comboBox_activated(deviceInfo[0]);

    ui->comboBox_2->setCurrentText(deviceInfo[1]);
    on_comboBox_2_activated(deviceInfo[1]);

    ui->comboBox_3->setCurrentText(deviceInfo[2]);
    on_comboBox_3_activated(deviceInfo[2]);

    ui->comboBox_4->setCurrentText(deviceInfo[3]);
    on_comboBox_4_activated(deviceInfo[3]);

    ui->comboBox_5->setCurrentText(deviceInfo[4]);

}


