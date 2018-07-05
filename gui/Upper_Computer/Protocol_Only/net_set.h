#ifndef NET_SET_H
#define NET_SET_H

#include <QDialog>

namespace Ui {
class Net_Set;
}

class Net_Set : public QDialog
{
    Q_OBJECT

public:
    explicit Net_Set(QWidget *parent = 0);
    ~Net_Set();


signals:
    void delNetSetObj();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


signals:
    void toMainNetSet(QString ip,int port);

private:
    Ui::Net_Set *ui;
};

#endif // NET_SET_H
