#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QSplitter>
#include <QTextEdit>
#include <QFrame>
#include <QGridLayout>
#include <QDockWidget>
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include <QFileSystemModel>

#include <QFileDialog>
#include <QMdiSubWindow>
#include  <QMdiArea>
#include <QEvent>
#include <QCloseEvent>
#include "qmymdisubwindow.h"
#include "phoneticwidgetform.h"
#include <QLabel>
#include <QScrollArea>

#include <MakeNetEngine.h>

#include <QFontDatabase>
#include <QTextCodec>
#include <QFile>
#include <QSettings>
#include "global.h"

#include <QFileInfoList>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include "setui.h"
#include "aboutdialog.h"
#include "descdialog.h"
#include <QFile>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDrag>

#define FILE_SELECT 1
#define DIR_SELECT 0

namespace Ui {
class MainWindow;
}





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    void openNetFile(QString filePath);
    void saveAnalysisNetFile();

    void setLeftDockWidget();
    void setMainToolBar();
    void setTreeWidget(QString dirRootPath);


    void showFileNameAndFileText();
    QString showFileNameWithFileListView(QString filename);
    void showFileTextWithTextEdit(QString filename, QMyMdiSubWindow *oneSession);


    void destorySubWindows();

    void getFileNameAndFilePath();


    void analysisNetFile(QString filePath);
    void loginEngine(HMNSESSION &session);

//    void useFont(QString path);

    void layoutAllPhoneticWidget();


    //分解单词音标 然后将dialog添加到scrollArea上
    void setPhoneticDialog(QString tabName);

    void getPhoneWidgetMaxSize(wPhonetic wordPhonetic, char word[], QString &oneWordPhonetic, QSize &oneWordPhoneticSize);
    QSize getWidth(QString string, int fontSize);



//备用
    void writePhoneticForMap(QMap<QString, QString> &phoneticType, int start, int count, QString &allPhonetic);
    void readINIForPhonetic();
    void readyPhonetic();
    QString searchPhonetic(int iPosition);

    QString getAllPhone();

    void resizeEvent(QResizeEvent *event);
    void update(QWidget *areaWidget);


    void TEST();

    QString searchFileNameAllPath(QString key);

    void netFileIsAnalysis();


    void writeNetlText2File();



//    static void test2();



private slots:

//    void TestTabBar(int index);

        void rightCleckedAnalysis();

    void on_tabWidget_tabCloseRequested(int index);




    void on_action_4_triggered();

    void on_treeView_doubleClicked(const QModelIndex &index);


    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void slotSetPhoneticDialog();

    void on_treeView_pressed(const QModelIndex &index);

    void on_actionSet_triggered();

    void on_fileListWidget_customContextMenuRequested(const QPoint &pos);

    void on_actionM_triggered(bool checked);

    void on_action_triggered(bool checked);

    void on_actionW_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_3_visibilityChanged(bool visible);


////listview拖拽需要重写listview控件
//protected:
//    void dragEnterEvent(QDragEnterEvent *e);
//    void dropEvent(QDropEvent *e);



public slots:


    void on_fileListWidget_doubleClicked(const QModelIndex &index);


    void fromPhoneticWidgetForm(int index, QObject *widget);



private:
    Ui::MainWindow *ui;

    QSplitter * mainSplitterWindows;
    QSplitter * leftSplitterWindows;
    QSplitter * rightSplitterWindows;
    QGridLayout *mainSplitterLayout;
    QTextEdit * leftEdit ;
    QTextEdit * rightEdit ;

    QMenu * menu;
    QMenu * menu1;
    QAction *fileAction;
    QToolButton * AnalysisToolButton;
    QFileSystemModel * fileModel;

    QList<QString>openFileName;
    QMap<QString,QString>fileName2filePath;

    //音标所用的存储图
    QMap<QString,QString>Phonetic_Vowel;
    QMap<QString,QString>Phonetic_Consonant;
    QMap<QString,QString>Phonetic_Marks;

    QList<PhoneticWidgetForm*>allPhoneticWidget;
//    QList<allPhoneticWidget>allTabWidget;
//    QList<int>keyWordIndex;

    int oldWidgetIndex;


    //
    QWidget *areaWidget;

    QMap<QString,QString>fileNameAndPathMap;

    QString rightClickedGetFileName;

    bool netCodeStatus;
    //


    SetUi * set;
    MN_ECODE ebCode;


    QLabel *statusBarLabel;

    bool operationType;

    QWidget *titleBarWidget;

    QDockWidget * logWidget;
    QDockWidget * propertyWidget;


    QModelIndex fileIndex;
    bool rootNode;

    QString Net_Dir_Path;







};

#endif // MAINWINDOW_H
