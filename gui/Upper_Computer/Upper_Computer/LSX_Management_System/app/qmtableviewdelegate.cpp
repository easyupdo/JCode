#include "qmtableviewdelegate.h"


#include <QSpinBox>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QRectF>
#include <QPixmap>
#include <QFontMetrics>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QStyle>

QMTableviewDelegate::QMTableviewDelegate(QObject *parent): QStyledItemDelegate(parent)
{

}


void QMTableviewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QPixmap pix;
  QPixmap backpic;
  painter->save();

//   if(index.column() == 1)
//   {
//       QWidget *widget = new QWidget;
//       widget->resize(20,20);
        QString path = ":/image/test.png";
        QString back = ":/image/test2.png";
        int status = pix.load(path);
        backpic.load(back);
//   }
    // string
   QString string = index.data().toString();
   QFontMetrics fm (index.data().toString());
   int length = fm.width(index.data().toString());
   int byteLength = string.length();
//   qDebug()<<"byteLength"<<byteLength;
   int everyLengthNumber = length/byteLength;
//   qDebug()<<"everyLengthNumber:"<<everyLengthNumber;

//   qDebug()<<"length22222222222:"<<length;
//   qDebug()<<"option.rect"<<option.rect;
    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->drawPixmap(option.rect.x(),option.rect.y()+4,20,20,backpic);
    }
    else
    {
       painter->drawPixmap(option.rect.x(),option.rect.y()+4,20,20,pix); ;
    }

    int nCount = string.count();
    int lengthCount = 0;
    int allLength =0;
    bool flag = false;
    for(int i = 0 ; i < nCount ; i++)
    {
       QString c = string.at(i);
       ushort uni = c.unicode()->unicode();
       if(uni >= 0x4E00 && uni <= 0x9FA5)
       {
           //这个字符是中文
//           qDebug()<<c;
           allLength = allLength + 8 *2;
       }
       else
           allLength = allLength + 8;
        lengthCount += 1;
       if(allLength > (option.rect.width() - 25))
       {
           lengthCount -=1;
           flag = true;
           break;
       }
    }

    if(flag)
        string = string.mid(0,lengthCount) + "...";
    else
        string = string.mid(0,lengthCount);

    if(lengthCount == 0)
        string = "";

     int center_Left = (option.rect.width()-20-fm.width(string))/2;
     if(center_Left<0)
         center_Left = 0;

    QRectF f(option.rect.x()+20+center_Left,option.rect.y()+6,option.rect.height()+length,option.rect.width());
    painter->drawText(f,string);
//    qDebug()<<QString::fromLocal8Bit("代理列 字符串 内容:")<<string;
//    painter->drawPixmap(option.rect.x(),option.rect.y()+5,20,20,backpic);
    painter->restore();

}



