#ifndef QMTABLEVIEWDELEGATE_H
#define QMTABLEVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>


class QMTableviewDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    QMTableviewDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//   bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const Q_DECL_OVERRIDE;

//    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
//    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const Q_DECL_OVERRIDE;

//    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
//    void editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

};

#endif // QMTABLEVIEWDELEGATE_H
