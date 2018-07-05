#ifndef MYSQLSUPPORT_H
#define MYSQLSUPPORT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QDebug>
#include <app/global.h>

struct dbConnectInfo
{
    QString hostName;
    QString userName;
    QString passWord;
    QString databaseName;
};

class MysqlSupport : public QObject
{
    Q_OBJECT

    friend class global;
public:
    explicit MysqlSupport(QObject *parent = 0);
    void mysqlConnect();
    void mysqlReConnect();
    void mysqlConfig();

signals:

public slots:
    void fromMainWindow();

//private:
public:
    QSqlDatabase db;
    struct dbConnectInfo dbInfo;
};

#endif // MYSQLSUPPORT_H
