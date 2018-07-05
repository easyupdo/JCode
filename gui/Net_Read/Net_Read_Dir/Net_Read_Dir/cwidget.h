#ifndef CWIDGET_H
#define CWIDGET_H

#include <QObject>
#include <QWidget>

class CWidget:public QWidget
{
public:
    CWidget(QWidget *parent = 0);
    ~CWidget();

    QSize sizeHint() const;
};

#endif // CWIDGET_H
