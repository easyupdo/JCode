#include "imessagebox.h"
#include "ui_imessagebox.h"

iMessageBox::iMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::iMessageBox)
{
    ui->setupUi(this);
    this->mousePressed = false;
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体关闭时自动释放内存
//    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->label_2->setAlignment(Qt::AlignHCenter);
    ui->label_2->setScaledContents(true);
    ui->label_3->setWordWrap(true);
}

iMessageBox::~iMessageBox()
{
    delete ui;
}


void iMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void iMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void iMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}


//三个借口 给不同的场景设置不同的反馈
void iMessageBox::setMessageType(QString messageType)
{


    if(messageType == "prompt")
    {
        ui->iMessageTitle->setText(QString::fromLocal8Bit("提示!"));
        ui->btnCancel_2->setVisible(false);
        QPixmap pic(":/image/info.png");
        ui->label_2->setPixmap(pic);
    }else if(messageType == "ask")
    {
        ui->iMessageTitle->setText(QString::fromLocal8Bit("询问!"));
//        ui->btnCancel_2->setVisible(false);
        QPixmap pic(":/image/question.png");
        ui->label_2->setPixmap(pic);

    }else if(messageType == "error")
    {
        ui->iMessageTitle->setText(QString::fromLocal8Bit("错误!"));
        ui->btnCancel_2->setVisible(false);
        QPixmap pic(":/image/error.png");
        ui->label_2->setPixmap(pic);
    }

}

void iMessageBox::setMessageText(QString messageText)
{
    ui->label_3->setText(messageText);
//    ui->btnCancel_2->setVisible(false);
}

void iMessageBox::setMessageIcon()
{

}

void iMessageBox::setUserMessage(QString messageText,QString messageType)
{
    setMessageType(messageType);
    setMessageText(messageText);
}

void iMessageBox::on_btnOk_clicked()
{
    done(1);
    this->close();
}

void iMessageBox::on_iMessageClosepushButton_clicked()
{
    done(0);
    this->close();
}

void iMessageBox::on_btnCancel_2_clicked()
{
    done(0);
    this->close();
}
