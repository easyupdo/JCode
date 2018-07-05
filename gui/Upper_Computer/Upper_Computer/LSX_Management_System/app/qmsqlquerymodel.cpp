#include "qmsqlquerymodel.h"
#include <QSqlQueryModel>

QMSqlQueryModel::QMSqlQueryModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

//QVariant QMSqlQueryModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//QModelIndex QMSqlQueryModel::index(int row, int column, const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//}

//QModelIndex QMSqlQueryModel::parent(const QModelIndex &index) const
//{
//    // FIXME: Implement me!
//}

//int QMSqlQueryModel::rowCount(const QModelIndex &parent) const
//{
//    if (!parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

//int QMSqlQueryModel::columnCount(const QModelIndex &parent) const
//{
//    if (!parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

QVariant QMSqlQueryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();
    if(role == Qt::TextAlignmentRole)//如果角色是文本对其方式
        return Qt::AlignCenter;//返回居中对齐

    // FIXME: Implement me!
//    return "FUCK";
            return QSqlQueryModel::data(index,role);//数据使用基类的data方法将view显示到view就行
}
