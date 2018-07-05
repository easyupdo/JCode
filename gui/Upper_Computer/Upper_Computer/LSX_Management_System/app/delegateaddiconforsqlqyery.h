#ifndef DELEGATEADDICONFORSQLQYERY_H
#define DELEGATEADDICONFORSQLQYERY_H
#include <QStyledItemDelegate>

class delegateAddIconForSqlQyery:public QStyledItemDelegate
{
public:
    delegateAddIconForSqlQyery(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // DELEGATEADDICONFORSQLQYERY_H
