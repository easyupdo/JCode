/********************************************************************************
** Form generated from reading UI file 'phoneticwidgetform.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHONETICWIDGETFORM_H
#define UI_PHONETICWIDGETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PhoneticWidgetForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *PhoneticWidgetForm)
    {
        if (PhoneticWidgetForm->objectName().isEmpty())
            PhoneticWidgetForm->setObjectName(QStringLiteral("PhoneticWidgetForm"));
        PhoneticWidgetForm->resize(34, 156);
        PhoneticWidgetForm->setMinimumSize(QSize(0, 0));
        PhoneticWidgetForm->setStyleSheet(QLatin1String("QWidget#PhoneticWidgetForm{border:2px solid #d4d1d1;border-radius:5px;padding:2px 4px}\n"
"color: rgb(226, 226, 226)"));
        verticalLayout = new QVBoxLayout(PhoneticWidgetForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(PhoneticWidgetForm);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(16777215, 30));
        label->setStyleSheet(QStringLiteral("QWidget{border:2px solid #d4d1d1;border-top-left-radius:5px;border-top-right-radius:5px;border-bottom:0px}"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(PhoneticWidgetForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setStyleSheet(QStringLiteral("QWidget{border:2px solid #d4d1d1;border-bottom-left-radius:5px;border-bottom-right-radius:5px}"));
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(false);

        verticalLayout->addWidget(label_2);


        retranslateUi(PhoneticWidgetForm);

        QMetaObject::connectSlotsByName(PhoneticWidgetForm);
    } // setupUi

    void retranslateUi(QWidget *PhoneticWidgetForm)
    {
        PhoneticWidgetForm->setWindowTitle(QApplication::translate("PhoneticWidgetForm", "Form", 0));
        label->setText(QApplication::translate("PhoneticWidgetForm", "hello", 0));
        label_2->setText(QApplication::translate("PhoneticWidgetForm", "\311\231\n"
"a:\311\231:\n"
"\311\231\n"
"", 0));
    } // retranslateUi

};

namespace Ui {
    class PhoneticWidgetForm: public Ui_PhoneticWidgetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHONETICWIDGETFORM_H
