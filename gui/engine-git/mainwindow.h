#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QtDebug>
#include <QStringList>
#include <QDialog>
#include <QSettings>
#include <QTextCodec>
#include <QDateTime>
#include "help.h"
#include <iostream>
#include <cxxabi.h>
#include <execinfo.h>
#include <fstream>
#include "lsx-ases.h"
#include "document.h"


#define OUTPUT 1
#define BUFFER_SIZE 4096

#define HAVE_CXXABI_H
#define HAVE_EXECINFO_H

using namespace rapidjson;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_comboBox_3_activated(const QString &arg1);

  void on_pushButton_2_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

  void on_comboBox_2_activated(const QString &arg1);

  void on_comboBox_activated(const QString &arg1);

  void on_pushButton_5_clicked();

  private:
  Ui::MainWindow *ui;

  //user
 private:
  bool engine_mode;     // true:list false:one file
  QString engine_type;
  QString engine_ver;
  QString engine_model;
  QString list_filename; //批量测试
  QString net_dir;       //单个文件测试 net目录
  QStringList file_lists;//单个文件测试 net list

  QString wav;


  private:
  void Evaluation_List();
  void Evaluation_File();

};

#endif // MAINWINDOW_H
