#ifndef PHONETICWIDGETFORM_H
#define PHONETICWIDGETFORM_H

#include <QWidget>
#include <QBitmap>
#include <QDebug>
#include <QPainter>
#include <QString>
#include"global.h"
#include <QFontDatabase>
#include <QMouseEvent>

namespace Ui {
class PhoneticWidgetForm;
}

class PhoneticWidgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneticWidgetForm(QWidget *parent = 0);
    ~PhoneticWidgetForm();


    void setPhonetic(char word[], QString wordPhonetic, QSize wordMaxSize);

    QRect getWidth(QString string);

    int getWordWidgetAndPhoneticHeight();


    void useFont();


    QSize getWidgetSize();

    void mousePressEvent(QMouseEvent *event);

    void setWidgetIndex(int index, bool keyWord, bool statementWord);
    void setClickedWidget();


    void setInitShow();
    void setKeyWordShow();
    bool getKeyStatus();

signals:
    void toMainWindowForSize(QSize size);
    void toMainWindowForIndexWidget(int index,QObject *);



private:
    Ui::PhoneticWidgetForm *ui;
    int widgetWidth;
    int widgetHeight;

    int index;

    bool keyWord;
    bool statementWord;

};

#endif // PHONETICWIDGETFORM_H
