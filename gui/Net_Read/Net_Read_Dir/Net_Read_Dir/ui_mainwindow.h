/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include <cwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionO;
    QAction *actionS;
    QAction *actionW;
    QAction *actionM;
    QAction *action_4;
    QAction *actionSet;
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QMenuBar *menuBar;
    QMenu *menuH;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *leftDockWidget;
    CWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QDockWidget *dockWidget_6;
    CWidget *dockWidgetContents_8;
    QGridLayout *gridLayout_3;
    QListWidget *fileListWidget;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_5;
    QTextEdit *textEdit;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_4;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1006, 672);
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(false);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionO = new QAction(MainWindow);
        actionO->setObjectName(QStringLiteral("actionO"));
        actionS = new QAction(MainWindow);
        actionS->setObjectName(QStringLiteral("actionS"));
        actionW = new QAction(MainWindow);
        actionW->setObjectName(QStringLiteral("actionW"));
        actionM = new QAction(MainWindow);
        actionM->setObjectName(QStringLiteral("actionM"));
        actionM->setCheckable(true);
        actionM->setVisible(true);
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        actionSet = new QAction(MainWindow);
        actionSet->setObjectName(QStringLiteral("actionSet"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action->setCheckable(true);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 1006, 22));
        menuBar->setMouseTracking(true);
        menuBar->setFocusPolicy(Qt::StrongFocus);
        menuBar->setAcceptDrops(true);
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menuH = new QMenu(menuBar);
        menuH->setObjectName(QStringLiteral("menuH"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        leftDockWidget = new QDockWidget(MainWindow);
        leftDockWidget->setObjectName(QStringLiteral("leftDockWidget"));
        leftDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        leftDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents = new CWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QStringLiteral("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);

        leftDockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), leftDockWidget);
        dockWidget_6 = new QDockWidget(MainWindow);
        dockWidget_6->setObjectName(QStringLiteral("dockWidget_6"));
        dockWidget_6->setFloating(false);
        dockWidget_6->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_8 = new CWidget();
        dockWidgetContents_8->setObjectName(QStringLiteral("dockWidgetContents_8"));
        dockWidgetContents_8->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(dockWidgetContents_8);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        fileListWidget = new QListWidget(dockWidgetContents_8);
        fileListWidget->setObjectName(QStringLiteral("fileListWidget"));

        gridLayout_3->addWidget(fileListWidget, 0, 0, 1, 1);

        dockWidget_6->setWidget(dockWidgetContents_8);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_6);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayout_5 = new QGridLayout(dockWidgetContents_2);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(dockWidgetContents_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_5->addWidget(textEdit, 0, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidget_2->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        gridLayout_4 = new QGridLayout(dockWidgetContents_4);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(dockWidgetContents_4);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);
        dockWidget_3 = new QDockWidget(MainWindow);
        dockWidget_3->setObjectName(QStringLiteral("dockWidget_3"));
        dockWidget_3->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidget_3->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);

        menuBar->addAction(menuH->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuH->addAction(actionO);
        menuH->addAction(action_4);
        menuH->addAction(actionS);
        menuH->addAction(actionW);
        menu_2->addAction(actionM);
        menu_2->addAction(action);
        menu_3->addAction(action_3);
        menu_3->addAction(action_2);
        menu->addAction(actionSet);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionO->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266(O)", 0));
        actionO->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionS->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230(S)", 0));
        actionS->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionW->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(W)", 0));
        actionW->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0));
        actionM->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272", 0));
        action_4->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\256\345\275\225(D)", 0));
        action_4->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actionSet->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        action->setText(QApplication::translate("MainWindow", "\345\261\236\346\200\247", 0));
        action_2->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
        action_3->setText(QApplication::translate("MainWindow", "\350\257\264\346\230\216", 0));
        menuH->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\216\247\344\273\266", 0));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267", 0));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">123</p></body></html>", 0));
        dockWidget_3->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
