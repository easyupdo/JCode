#ifndef IMESSAGEBOX_H
#define IMESSAGEBOX_H

#include <QDialog>
#include <QMouseEvent>
#include <QPixmap>

namespace Ui {
class iMessageBox;
}

class iMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit iMessageBox(QWidget *parent = 0);
    ~iMessageBox();
public:
    void setMessageType(QString messageType);
    void setMessageText(QString messageText);
    void setMessageIcon();
    void setUserMessage(QString messageText,QString messageType);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btnOk_clicked();

    void on_iMessageClosepushButton_clicked();

    void on_btnCancel_2_clicked();

private:
    Ui::iMessageBox *ui;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // IMESSAGEBOX_H
