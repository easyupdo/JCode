/********************************************************************************
** Form generated from reading UI file 'setui.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUI_H
#define UI_SETUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetUi
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QLabel *label_11;
    QLineEdit *lineEdit_6;
    QLabel *label_13;
    QLineEdit *lineEdit_7;
    QLabel *label_15;
    QLineEdit *lineEdit_8;

    void setupUi(QDialog *SetUi)
    {
        if (SetUi->objectName().isEmpty())
            SetUi->setObjectName(QStringLiteral("SetUi"));
        SetUi->resize(455, 271);
        gridLayout_3 = new QGridLayout(SetUi);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(SetUi);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(384, 48, 38, 23));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(210, 210, 80, 20));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(320, 210, 80, 20));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 50, 361, 24));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(30, 0));
        lineEdit->setMaximumSize(QSize(30, 16777215));
        lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(5, 0));
        label_2->setMaximumSize(QSize(5, 16777215));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(30, 0));
        lineEdit_2->setMaximumSize(QSize(30, 16777215));
        lineEdit_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_2, 0, 2, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(5, 0));
        label_4->setMaximumSize(QSize(5, 16777215));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(30, 0));
        lineEdit_3->setMaximumSize(QSize(30, 16777215));
        lineEdit_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_3, 0, 4, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(5, 0));
        label_6->setMaximumSize(QSize(5, 16777215));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 0, 5, 1, 1);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(30, 0));
        lineEdit_4->setMaximumSize(QSize(30, 16777215));
        lineEdit_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_4, 0, 6, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(5, 0));
        label_8->setMaximumSize(QSize(5, 16777215));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 0, 7, 1, 1);

        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(30, 0));
        lineEdit_5->setMaximumSize(QSize(30, 16777215));
        lineEdit_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_5, 0, 8, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(5, 0));
        label_11->setMaximumSize(QSize(5, 16777215));
        label_11->setFont(font);

        gridLayout->addWidget(label_11, 0, 9, 1, 1);

        lineEdit_6 = new QLineEdit(widget);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setMinimumSize(QSize(30, 0));
        lineEdit_6->setMaximumSize(QSize(30, 16777215));
        lineEdit_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_6, 0, 10, 1, 1);

        label_13 = new QLabel(widget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(5, 0));
        label_13->setMaximumSize(QSize(5, 16777215));
        label_13->setFont(font);

        gridLayout->addWidget(label_13, 0, 11, 1, 1);

        lineEdit_7 = new QLineEdit(widget);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setMinimumSize(QSize(30, 0));
        lineEdit_7->setMaximumSize(QSize(30, 16777215));
        lineEdit_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_7, 0, 12, 1, 1);

        label_15 = new QLabel(widget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(5, 0));
        label_15->setMaximumSize(QSize(5, 16777215));
        label_15->setFont(font);

        gridLayout->addWidget(label_15, 0, 13, 1, 1);

        lineEdit_8 = new QLineEdit(widget);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setMinimumSize(QSize(30, 0));
        lineEdit_8->setMaximumSize(QSize(30, 16777215));
        lineEdit_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_8, 0, 14, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(SetUi);

        QMetaObject::connectSlotsByName(SetUi);
    } // setupUi

    void retranslateUi(QDialog *SetUi)
    {
        SetUi->setWindowTitle(QApplication::translate("SetUi", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("SetUi", "\345\257\206\347\240\201", 0));
        pushButton->setText(QApplication::translate("SetUi", "\344\277\256\346\224\271", 0));
        pushButton_2->setText(QApplication::translate("SetUi", "\344\277\235\345\255\230", 0));
        pushButton_3->setText(QApplication::translate("SetUi", "\345\217\226\346\266\210", 0));
        lineEdit->setText(QApplication::translate("SetUi", "DD", 0));
        label_2->setText(QApplication::translate("SetUi", "-", 0));
        lineEdit_2->setText(QApplication::translate("SetUi", "DD", 0));
        label_4->setText(QApplication::translate("SetUi", "-", 0));
        lineEdit_3->setText(QApplication::translate("SetUi", "DD", 0));
        label_6->setText(QApplication::translate("SetUi", "-", 0));
        lineEdit_4->setText(QApplication::translate("SetUi", "DD", 0));
        label_8->setText(QApplication::translate("SetUi", "-", 0));
        lineEdit_5->setText(QApplication::translate("SetUi", "DD", 0));
        label_11->setText(QApplication::translate("SetUi", "-", 0));
        lineEdit_6->setText(QApplication::translate("SetUi", "DD", 0));
        label_13->setText(QApplication::translate("SetUi", "-", 0));
        lineEdit_7->setText(QApplication::translate("SetUi", "DD", 0));
        label_15->setText(QApplication::translate("SetUi", "-", 0));
        lineEdit_8->setText(QApplication::translate("SetUi", "DD", 0));
    } // retranslateUi

};

namespace Ui {
    class SetUi: public Ui_SetUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUI_H
