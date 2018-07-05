#include "cwidget.h"
#include <QPushButton>
CWidget::CWidget(QWidget *parent)
{
//    QPushButton * button = new QPushButton(this);
}
CWidget::~CWidget()
{

}

QSize CWidget::sizeHint() const
{
    return QSize(200,650);
}
