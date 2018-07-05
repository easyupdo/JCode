#include "delegateaddiconforsqlqyery.h"
#include<QDebug>
#include <QPainter>
#include <QSpinBox>
delegateAddIconForSqlQyery::delegateAddIconForSqlQyery(QObject *parent):QStyledItemDelegate(parent)
{

}

void delegateAddIconForSqlQyery::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QString string = index.data().toString();
    qDebug()<<"String:"<<string;
    qDebug()<<"Location:"<< option.rect;
    qDebug()<<"width:"<<option.rect.width();
    qDebug()<<option.icon;
    qDebug()<<option.version;
    //index.data().
   QPixmap pix;
   QString path = "C:/Users/shenmingzh/Desktop/testDATA/test.png";
   //  qDebug()<<"pathN:"<<path;
     qDebug()<<"N:"<<index.data().toString();
     qDebug()<<index.data().Icon;
     QFontMetrics fm (index.data().toString());
     int length = fm.width(index.data().toString());
     qDebug()<<"length:"<<length;
      pix.load(path);
     painter->drawPixmap(option.rect.x()+10,option.rect.y(),20,20,pix);
     QRectF f(option.rect.x()+option.rect.width()/2-length/2+20,option.rect.y()+5,option.rect.height()+length,option.rect.width());
     qDebug()<<""<<f;
     qDebug()<<"Data:"<<index.data();

    painter->drawText(f,string);
    painter->restore();

}


QWidget *delegateAddIconForSqlQyery::createEditor(QWidget *parent,const QStyleOptionViewItem &/* option */,const QModelIndex &/* index */) const
{
    QSpinBox *editor = new QSpinBox(parent);
////    QItemEditorFactory
//    editor->setFrame(false);
//    editor->setMinimum(0);
//    editor->setMaximum(100);


    return editor;
}


void delegateAddIconForSqlQyery::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QPixmap pix;
                                                      // add a pic
    QString path = "C:/Users/shenmingzh/Desktop/testDATA/test.png";
  //  qDebug()<<"pathN:"<<path;
    qDebug()<<"N:"<<index.data().toString();
     pix.load(path);

//    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  //  spinBox->setValue(value);
}

void delegateAddIconForSqlQyery::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
//    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
//    spinBox->interpretText();
//    int value = spinBox->value();

//    for (int row = 0; row < 4; ++row)
//    {
//        for (int column = 0; column < 2; ++column)
//        {
//            //QModelIndex index = model.index(row, column, QModelIndex());
////            model->setData(index, QVariant((row + 1) * (column + 1)));
//             model->setData(index, index.data().toString());
//        }
//        model->setData(index, value, Qt::EditRole);

//    }
}

void delegateAddIconForSqlQyery::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

