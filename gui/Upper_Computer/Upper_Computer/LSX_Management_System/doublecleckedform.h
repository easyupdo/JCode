#ifndef DOUBLECLECKEDFORM_H
#define DOUBLECLECKEDFORM_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QMouseEvent>
namespace Ui {
class doubleCleckedForm;
}

class doubleCleckedForm : public QWidget
{
    Q_OBJECT

public:
    explicit doubleCleckedForm(QWidget *parent = 0);
    ~doubleCleckedForm();

public:
    void initTableviewHeader();
    void setTableview();

public slots:
    void fromPollingDevice(QString *string);


private slots:
    void on_addDuan_CloseButton_clicked();


protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::doubleCleckedForm *ui;

    QSqlQueryModel * queryModel;


    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // DOUBLECLECKEDFORM_H
