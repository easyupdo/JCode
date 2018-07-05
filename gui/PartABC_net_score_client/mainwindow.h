#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void my_Receive();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray wav_data;
    QTcpSocket *socket;
    bool connect_flag;
};

#endif // MAINWINDOW_H
