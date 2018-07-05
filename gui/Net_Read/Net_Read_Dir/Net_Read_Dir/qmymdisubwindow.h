#ifndef QMYMDISUBWINDOW_H
#define QMYMDISUBWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QCloseEvent>
#include <QEvent>
#include <QDebug>

class QMyMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit QMyMdiSubWindow(QWidget *parent = 0);
    ~QMyMdiSubWindow();



signals:
    void closeOneSubWindow(QString windowTitle);

public slots:

    protected:
//      void closeEvent(QCloseEvent *closeEvent) Q_DECL_OVERRIDE;

       bool event(QEvent *event) Q_DECL_OVERRIDE;



};

#endif // QMYMDISUBWINDOW_H
