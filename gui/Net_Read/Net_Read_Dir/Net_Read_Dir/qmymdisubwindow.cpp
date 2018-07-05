#include "qmymdisubwindow.h"

QMyMdiSubWindow::QMyMdiSubWindow(QWidget *parent) : QMdiSubWindow(parent)
{

    qDebug()<<"new QMyMdiSubWindow";
}


//void QMyMdiSubWindow::closeEvent(QCloseEvent *closeEvent)
//{
//    qDebug()<<"close Event!";
//}


bool QMyMdiSubWindow::event(QEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        qDebug()<<"close qclose event !";
//        event->ignore();
        event->accept();
//        emit closeOneSubWindow(this->widget()->windowTitle());
        return true;
    }
    return QMdiSubWindow::event(event);
}


QMyMdiSubWindow::~QMyMdiSubWindow()
{

}
