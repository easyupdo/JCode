#ifndef QMSQLQUERYMODEL_H
#define QMSQLQUERYMODEL_H

#include <QAbstractItemModel>
#include <QSqlQueryModel>

class QMSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit QMSqlQueryModel(QObject *parent = 0);

    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    // Basic functionality:
//    QModelIndex index(int row, int column,
//                      const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;

//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // QMSQLQUERYMODEL_H
