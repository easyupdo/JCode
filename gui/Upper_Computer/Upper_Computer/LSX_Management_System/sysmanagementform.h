#ifndef USERMANAGEMENTFORM_H
#define USERMANAGEMENTFORM_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class userManagementForm;
}

class userManagementForm : public QWidget
{
    Q_OBJECT

public:
    explicit userManagementForm(QWidget *parent = 0);
    ~userManagementForm();

    void readINI();
    void writeINI(QString,QString);
signals:
    void changeVoiceDownRootDir(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::userManagementForm *ui;
     QFileDialog * fileDialog;
};

#endif // USERMANAGEMENTFORM_H
