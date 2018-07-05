#include "doublecleckedform.h"
#include "ui_doublecleckedform.h"
#include <QDebug>
#include <QSqlQuery>
#include "app/qmtableviewdelegate.h"

doubleCleckedForm::doubleCleckedForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doubleCleckedForm)
{
    ui->setupUi(this);
    this->mousePressed =false;
    this->setWindowFlags(Qt::FramelessWindowHint);
    queryModel = new QSqlQueryModel;
    initTableviewHeader();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    QMTableviewDelegate * delegate = new QMTableviewDelegate;
    ui->tableView->setItemDelegateForColumn(2,delegate);
    this->setWindowTitle(QString::fromLocal8Bit("故障信息"));
    this->setWindowModality(Qt::ApplicationModal);
}

doubleCleckedForm::~doubleCleckedForm()
{
    delete ui;
}

void doubleCleckedForm::fromPollingDevice(QString *string)
{
    qDebug()<<"sss"<<string[0];
    qDebug()<<"sss"<<string[1];
    qDebug()<<"sss"<<string[2];
    qDebug()<<"sss"<<string[3];
    qDebug()<<"sss"<<string[4];

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();

    ui->comboBox->addItem(string[0]);
    ui->comboBox_2->addItem(string[1]);
    ui->comboBox_3->addItem(string[2]);
    ui->comboBox_4->addItem(string[3]);
    ui->comboBox_5->addItem(string[4]);

    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->comboBox_4->setEnabled(false);
    ui->comboBox_5->setEnabled(false);
     setTableview();
}

void doubleCleckedForm::initTableviewHeader()
{
    queryModel->setQuery("select duan,jian,qu,station from device where duan =''");
    queryModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("巡检时间"));
    queryModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("巡检内容"));
    queryModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("巡检结果"));
    queryModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("未查看故障"));
    queryModel->insertColumn(4);
    queryModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit(""));
    ui->tableView->setModel(queryModel);

}

void doubleCleckedForm::setTableview()
{

    QString sql = QObject::tr("select starttime,content,currentstate,errorcount from `check` where duan = '%1' and jian = '%2' and qu = '%3' and station ='%4' and deviceid ='%5'").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText(),ui->comboBox_5->currentText());
    queryModel->setQuery(sql);
    //queryModel->setData(1,2);
    ui->tableView->setModel(queryModel);




    qDebug()<<"sql:"<<sql;
}

void doubleCleckedForm::on_addDuan_CloseButton_clicked()
{
    this->close();
}

void doubleCleckedForm::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void doubleCleckedForm::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void doubleCleckedForm::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
