/********************************************************************************
** Form generated from reading UI file 'descdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESCDIALOG_H
#define UI_DESCDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DescDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QLabel *label;
    QGroupBox *groupBox_2;
    QLabel *label_2;

    void setupUi(QDialog *DescDialog)
    {
        if (DescDialog->objectName().isEmpty())
            DescDialog->setObjectName(QStringLiteral("DescDialog"));
        DescDialog->resize(400, 300);
        gridLayout = new QGridLayout(DescDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(DescDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 171, 16));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(DescDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 181, 16));
        label_2->setFont(font);

        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(DescDialog);

        QMetaObject::connectSlotsByName(DescDialog);
    } // setupUi

    void retranslateUi(QDialog *DescDialog)
    {
        DescDialog->setWindowTitle(QApplication::translate("DescDialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DescDialog", "\345\205\263\351\224\256\350\257\215\357\274\232", 0));
        label->setText(QApplication::translate("DescDialog", "\345\205\263\351\224\256\350\257\215\347\224\250\350\223\235\350\211\262\350\276\271\346\241\206\346\240\207\346\263\250", 0));
        groupBox_2->setTitle(QApplication::translate("DescDialog", "\351\207\215\350\257\273\350\257\215\357\274\232", 0));
        label_2->setText(QApplication::translate("DescDialog", "\351\207\215\350\257\273\350\257\215\347\224\250\347\272\242\350\211\262\345\255\227\344\275\223\346\240\207\346\263\250", 0));
    } // retranslateUi

};

namespace Ui {
    class DescDialog: public Ui_DescDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESCDIALOG_H
