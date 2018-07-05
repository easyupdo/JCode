#include "phoneticwidgetform.h"
#include "ui_phoneticwidgetform.h"
#include "global.h"

PhoneticWidgetForm::PhoneticWidgetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhoneticWidgetForm)
{
    ui->setupUi(this);

//    this->setWindowFlags(Qt::FramelessWindowHint);


    useFont();



}

PhoneticWidgetForm::~PhoneticWidgetForm()
{
    delete ui;
}




//设置内容
void PhoneticWidgetForm::setPhonetic(char word[],QString wordPhonetic,QSize wordMaxSize)
{

        ui->label->setText(word);
        ui->label_2->setText(wordPhonetic);

        this->widgetWidth = ui->label->size().width();
        this->widgetHeight = ui->label->size().height();



        this->setMinimumHeight(wordMaxSize.height() + 50);
        this->setMaximumHeight(wordMaxSize.height() + 50);

        this->setMinimumWidth(wordMaxSize.width());
        this->setMaximumWidth(wordMaxSize.width());

}


QSize PhoneticWidgetForm::getWidgetSize()
{
    QSize size;
    size.setWidth(this->widgetWidth);
    size.setHeight(this->widgetHeight);
    return size;
}




void PhoneticWidgetForm::useFont()
{
    QString font;
    int loadedFontID = QFontDatabase::addApplicationFont(":/font/IpaPanNew.ttf");
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if(!loadedFontFamilies.empty())
    {
        font = loadedFontFamilies.at(0);
    }

    QFont f(font);
    f.setPixelSize(20);
    ui->label->setFont(f);
    f.setPixelSize(15);
    ui->label_2->setFont(f);

}





void PhoneticWidgetForm::mousePressEvent(QMouseEvent *event)
{
        if(event->type() == QMouseEvent::MouseButtonPress)
        {
             toMainWindowForIndexWidget(index,this->parent());
             //新子窗口开启旧地 音标显示控件 list销毁
        }
}




void PhoneticWidgetForm::setWidgetIndex(int index,bool keyWord,bool statementWord)
{
    this->index = index;
    this->keyWord = keyWord;
    this->statementWord = statementWord;
}

void PhoneticWidgetForm::setClickedWidget()
{
//    this->setStyleSheet();
    ui->label->setStyleSheet("QWidget{background-color: rgb(255, 218, 124);border:2px solid #000000;border-top-left-radius:5px;border-top-right-radius:5px;border-bottom:0px};");
    ui->label_2->setStyleSheet("QWidget{background-color: rgb(255, 218, 124);border:2px solid #000000;border-bottom-left-radius:5px;border-bottom-right-radius:5px};");
//    qDebug()<<QString::fromLocal8Bit("当前控件地址:")<<this<<this->parent();
    if(statementWord)
        ui->label->setStyleSheet("QWidget{color: rgb(166, 28, 0);background-color: rgb(255, 218, 124);border:2px solid #000000;border-top-left-radius:5px;border-top-right-radius:5px;border-bottom:0px};");
//    setInitShow();
}




void PhoneticWidgetForm::setInitShow()
{

//    QString styleBackGroundColor= "background-color:rgb(166, 28, 0)";

    QString styleUpBorder;
    QString styleDownBorder;
    QString styleLabelColor;

    if(keyWord)
    {
        styleUpBorder = "border:2px solid #3c78d8;border-top-left-radius:5px;border-top-right-radius:5px;border-bottom:0px;";
        styleDownBorder = "border:2px solid #3c78d8;border-bottom-left-radius:5px;border-bottom-right-radius:5px;";
//        qDebug()<<QString::fromLocal8Bit("设置关键词显示");
    }
    else
    {
        styleUpBorder = "border:2px solid #b4b3b3;border-top-left-radius:5px;border-top-right-radius:5px;border-bottom:0px;";
        styleDownBorder = "border:2px solid #b4b3b3;border-bottom-left-radius:5px;border-bottom-right-radius:5px;";
    }
    if(statementWord)
    {
        styleLabelColor = "color: rgb(166, 28, 0);";
    }

    QString styleUpLabel = "QWidget{" + styleUpBorder + styleLabelColor+ "}";
    QString styleDownLabel = "QWidget{" + styleDownBorder + "}";
    ui->label->setStyleSheet(styleUpLabel);
    ui->label_2->setStyleSheet(styleDownLabel);

}

void PhoneticWidgetForm::setKeyWordShow()
{
    ui->label->setStyleSheet("QWidget{background-color: rgb(255, 218, 124);border:2px solid #0000ff;border-top-left-radius:5px;border-top-right-radius:5px;border-bottom:0px};");
    ui->label_2->setStyleSheet("QWidget{background-color: rgb(255, 218, 124);border:2px solid #0000ff;border-bottom-left-radius:5px;border-bottom-right-radius:5px};");
}

bool PhoneticWidgetForm::getKeyStatus()
{
    if(this->keyWord)
        return true;
    else
        return false;
}




