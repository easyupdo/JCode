#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdlib.h>
#include <stdio.h>
#include "global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/Analysis.ico"));

    this->setWindowTitle(QString::fromLocal8Bit("asec 网络读取工具"));

    delete (ui->centralWidget);

    logWidget = ui->dockWidget;
    propertyWidget = ui->dockWidget_3;

    this->removeDockWidget(ui->dockWidget);
    this->removeDockWidget(ui->dockWidget_3);


    titleBarWidget = ui->dockWidget_2->titleBarWidget();
    ui->dockWidget->setWindowTitle(QString::fromLocal8Bit("Log显示域(敬请期待)"));
    ui->dockWidget_3->setWindowTitle(QString::fromLocal8Bit("属性显示域(敬请期待)"));

    this->splitDockWidget(ui->dockWidget_2,propertyWidget,Qt::Horizontal);
    this->splitDockWidget(ui->dockWidget_2,logWidget,Qt::Vertical);



    set = new SetUi;
    set-> showCode();
    ebCode = set->getCode();


    this->setDockNestingEnabled(true);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->fileListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->tabWidget->setMinimumHeight(500);
    ui->leftDockWidget->setMaximumWidth(300);
    ui->dockWidget_6->setMaximumWidth(300);

    oldWidgetIndex = 0;
    netCodeStatus = true;

    readyPhonetic();

    setMainToolBar();

    connect(ui->actionO,&QAction::triggered,this,&MainWindow::getFileNameAndFilePath);//open

    setLeftDockWidget();


    this->setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::South);


    //隐藏someting
    ui->actionS->setDisabled(true);

    rootNode = false;
}



MainWindow::~MainWindow()
{

    delete ui;
    delete set;

}

void MainWindow::analysisNetFile(QString filePath)
{

//    QLabel *label = new QLabel("FUCK YOU!");
//    label->show();

    QSize oneWordPhoneticSize;
    allPhoneticWidget.clear();
    HMNSESSION  session;
    loginEngine(session);


    QFile netFile(filePath);
    netFile.open(QIODevice::ReadOnly);
    if(netFile.isOpen())
        qDebug()<<"net file open successful!";
    else
    {
        QMessageBox box;
        box.setText(QString::fromLocal8Bit("net 文件读取错误,请检查net打开操作!"));
        box.exec();
    }

    char *data = (new char[netFile.size()]);
    netFile.read(data,netFile.size());
     qDebug()<<"Read Data"<<data;

    int loadStatus = LoadNet(session,data,netFile.size());

    if(loadStatus)
    {
        qDebug()<<"LoadNet successful!";
        netCodeStatus = true;
    }
    else
    {
    QMessageBox box;
    box.setText(QString::fromLocal8Bit("加载Net文件时出现错误,请检查解析密码"));
    box.exec();

        netCodeStatus = false;
    }
    if(netCodeStatus)
    {
        char gText[1024];
        int GetOrgTextStatus =  GetOrgText(session,gText,1024);
        if(!GetOrgTextStatus)
            qDebug()<<QString::fromLocal8Bit("获取net文本成功:")<<gText;
        int wordCount = GetTextSplitCount(session);

//       qDebug()<<QString::fromLocal8Bit("单词数:") + QString::number(wordCount);


       PTEXT_SPLIT_ITEM pItem = new TEXT_SPLIT_ITEM;

//       qDebug()<<QString::fromLocal8Bit("获取拆分项内容是否成功")<<GetTextSplitItem(session,0,pItem);
//       qDebug()<<QString::fromLocal8Bit("获取拆分项:");
//       qDebug()<<QString::fromLocal8Bit("在原始文本中的起始位置")<<pItem->nStart<<QString::fromLocal8Bit("在原始文本中的长度")<<pItem->nLen;

        //单词数添加控件个数
        char splitTextData[64];
        int  buffer[20];
        memset(splitTextData,0,sizeof(splitTextData));

        //一个net分解后一个单词 可能有几个读音
        int keyWordCount = 0;


        for(int i = 0;i<wordCount;i++)
        {
            int splitRet = GetTextSplitText(session,i,splitTextData,1024);//获取拆分词
            int phoneticCount  = GetPhoneticCount(session,i);//文本拆分位置从1开始计数
    //        qDebug()<<QString::fromLocal8Bit("音标计数:")<<phoneticCount;
              //一个单词可能有好几个读音
            QString onePhonetic;
            QString owPhonetic;
            QSize onePhoneticSize;
            QSize onePhoeticMaxSize;
            for(int j = 0;j<phoneticCount;j++)
            {
                memset(buffer,0,20);
                int phoneRet = GetPhoneticItem(session,i,j,buffer,20);//音标项位置 从 0 开始计数
                if(!phoneRet)
                {
    //                qDebug()<<QString::fromLocal8Bit("获取音标项目成功");
                    int x = 0;
                    //一个读音有好几个音标组成
                    for(;;)
                    {
                        if(buffer[x] == 0)
                        {
                            onePhoneticSize = getWidth(onePhonetic,15);
                            if(onePhoeticMaxSize.width() < onePhoneticSize.width())
                            {
                                onePhoeticMaxSize = onePhoneticSize;
                            }
                            owPhonetic = owPhonetic + onePhonetic + "\n";//一个单词的所有音标
                            onePhonetic.clear();
                            break;
                        }
                        else
                        {
                            QString pItem = searchPhonetic(buffer[x]);
//                            qDebug()<<QString::fromLocal8Bit("音标Item:")<<buffer<<QString::number(buffer[x],16)<<pItem;//显示音标

                            onePhonetic =onePhonetic + pItem;

                            x+=1;
                        }
                    }
    //                qDebug()<<QString::fromLocal8Bit("一个单词读音");
//                    qDebug()<<QString::fromLocal8Bit("一个单词音标:")<<owPhonetic<<onePhoeticMaxSize;
                }else
                {
    //                qDebug()<<QString::fromLocal8Bit("获取音标项目失败");
                }
            }
                    QSize owSize = getWidth(splitTextData,25);
                    if(owSize.width() < onePhoeticMaxSize.width())
                        oneWordPhoneticSize = onePhoeticMaxSize;
                    else
                        oneWordPhoneticSize = owSize;
                    oneWordPhoneticSize.setHeight(onePhoeticMaxSize.height()*phoneticCount);//显示控件的高度

    /****************************耗时**********************/
            if(!splitRet)
            {
                PhoneticWidgetForm * newPhoneticWidget = new PhoneticWidgetForm;

                newPhoneticWidget->setPhonetic(splitTextData,owPhonetic,oneWordPhoneticSize);//每一个单词一个控件
                /*设置关键词*/
                bool stressStatus = GetStress(session,i);
                bool statementStressStatus = GetStatementStress(session,i);
                if(statementStressStatus)
                qDebug()<<QString::fromLocal8Bit("这是重读词:")<<splitTextData;


                newPhoneticWidget->setWidgetIndex(i,stressStatus,statementStressStatus);//设置控件索引，便于索引定位控件位置
                allPhoneticWidget.insert(i,newPhoneticWidget);//控件添加到list中
            }else
                qDebug()<<QString::fromLocal8Bit("获取拆分项文本失败");
    /*****************************耗时************************/
        }
    //    for(int i = 0;i<keyWordIndex.size();i++)
    //    qDebug()<<QString::fromLocal8Bit("关键词集合:")<<allPhoneticWidget.at(keyWordIndex.at(i));
            delete(pItem);
    }

    delete(data);

}



void MainWindow::getPhoneWidgetMaxSize(wPhonetic wordPhonetic,char word[],QString &oneWordPhonetic,QSize &oneWordPhoneticSize)
{
//    int wordWidth = 0;
//    QString warp = "\n";
//    wordWidth = getWidth(word).width();
//    for(int i = 0;i<wordPhonetic.wordAllPhonetic.size();i++)
//    {
////        qDebug()<<QString::fromLocal8Bit("单词:")<<word;
//        int phoneticWidth = 0;
//        for(int j = 0;j<wordPhonetic.wordAllPhonetic.at(i).hPhonetic.size();j++)
//        {
//            int  width= getWidth(wordPhonetic.wordAllPhonetic.at(i).hPhonetic.at(j)).width();
//            if(phoneticWidth < width)
//            {
//                phoneticWidth = width;
//            }
//            QString phonetic = wordPhonetic.wordAllPhonetic.at(i).hPhonetic.at(j);
//            int maxHeight = getWidth(word).height() * (j+1);
//            oneWordPhoneticSize.setHeight(maxHeight + 50);
////            qDebug()<<QString::fromLocal8Bit("控件高度")<<maxHeight;

////            qDebug()<<QString::fromLocal8Bit("一个单词的音标有几个是什么:")<<phonetic<<maxHeight;//i:有几个读音   j:每一个读音有几个音标
//            oneWordPhonetic = oneWordPhonetic  + phonetic + warp;
//        }

//        if(wordWidth < phoneticWidth)
//        {
////            qDebug()<<QString::fromLocal8Bit("根据音标设置宽度");
//            oneWordPhoneticSize.setWidth(phoneticWidth+20);
//        }else
//        {
////            qDebug()<<QString::fromLocal8Bit("根据单词设置宽度");

//            oneWordPhoneticSize.setWidth(wordWidth+20);
//        }

////        qDebug()<<"kongjiandaxiao:"<<oneWordPhonetic;



//        qDebug()<<"wordPhonetic"<<wordPhonetic.wordAllPhonetic.size();
//    }

//    qDebug()<<"Label Size:"<<ui->label->size()<<"FUCK you"<<oneWordPhoneticSize;


}

QSize MainWindow::getWidth(QString string,int fontSize)
{
    QFont font;
    font.setPointSize(fontSize);

    QFontMetrics fm(font);
    QRect rec = fm.boundingRect(string);
    //字符串所占的像素宽度,高度
    QSize size;
    size.setWidth(rec.width());
    size.setHeight(rec.height());

    return size;
}

void MainWindow::loginEngine(HMNSESSION & session)
{
    session = StartSession();
    qDebug()<<"HMNSESSION"<<session;


    int status = SetECode(session,&ebCode);
    if(status)
        qDebug()<<QString::fromLocal8Bit("设置密码成功!");
    else
    {
        QMessageBox box;
        box.setText(QString::fromLocal8Bit("密码设置错误,请检查!"));
    }
}





//
void MainWindow::getFileNameAndFilePath()
{
//    system("pause");
    if(!operationType)
        ui->tabWidget->clear();


    QFileDialog *fileDialog = new QFileDialog;
    QString filePath = fileDialog->getOpenFileName();
    qDebug()<<QString::fromLocal8Bit("文件名:")<<filePath;
    if(filePath.length() > 0)
    {
        analysisNetFile(filePath);//引擎加载net文件并分解
        if(netCodeStatus)
        {
            qDebug()<<"realFileName";
            QString realFileName = showFileNameWithFileListView(filePath);//添加到listView
        //            system("pause");

            setPhoneticDialog(realFileName);//添加每一个单词的显示控件
            ui->dockWidget_6->raise();

            QWidget * widget = new QWidget;
            ui->dockWidget_2->setTitleBarWidget(widget);

        }
    }

    operationType = FILE_SELECT;
//    QSize oneWordPhoneticSize;
    delete(fileDialog);




}




//文档编辑器接口
void MainWindow::openNetFile(QString filePath)
{
    QTextEdit *oneSession = new QTextEdit;
    qDebug()<<"oneSession address:"<<oneSession;
    QMyMdiSubWindow *sessionWindow = new QMyMdiSubWindow;
   sessionWindow->setAttribute(Qt::WA_DeleteOnClose);

    sessionWindow->setWidget(oneSession);

    QString realFileName = showFileNameWithFileListView(filePath);

    fileName2filePath.insert(realFileName,filePath);

    QMap<QString,QString>::iterator it;

//    for(it = fileName2filePath.begin();it!=fileName2filePath.end();it++)
//    {
//        qDebug()<<"MAP:"<<it.value();
//    }

//    startOneNetSession(sessionWindow,realFileName);

    showFileTextWithTextEdit(filePath,sessionWindow);//将内容显示到mdiArea上
}

//
void MainWindow::setPhoneticDialog(QString tabName)
{
    QWidget * tab = new QWidget;
    ui->tabWidget->addTab(tab,QString());

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);


    int lastIndex = tabName.lastIndexOf("/");
    QString realFileName = tabName.right(tabName.length() - lastIndex -1);

//    system("pause");

    ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab),realFileName);

    QGridLayout *tabLayout = new QGridLayout;
    tab->setLayout(tabLayout);
    tabLayout->setContentsMargins(0,0,0,0);



    QScrollArea * area = new QScrollArea();

    tabLayout->addWidget(area);
    area->setWidgetResizable(true);

    areaWidget = new QWidget();
//    area->addScrollBarWidget(areaWidget,Qt::AlignCenter);
    area->setWidget(areaWidget);

    update(areaWidget);


}


//跟新音标显示控件位置
void MainWindow::update(QWidget *areaWidget)
{
    int xPosition = 10;
    int nxPosition = 10;
    int yPosition = 10;
    int rowCount = 1;
    int rowHeight = 0;
//    qDebug()<<QString::fromLatin1("tabWidget大小:")<<this->size();
    for(int i = 0;i<allPhoneticWidget.size();i++)
    {
//        qDebug()<<QString::fromLocal8Bit("集合地址")<<allPhoneticWidget.at(i);
        connect(allPhoneticWidget.at(i),&PhoneticWidgetForm::toMainWindowForIndexWidget,this,&MainWindow::fromPhoneticWidgetForm);
        nxPosition = nxPosition + allPhoneticWidget.at(i)->width() + 10;
//        qDebug()<<QString::fromLocal8Bit("nxPosition")<<nxPosition<<ui->tabWidget->findChildren();
        if(nxPosition < (ui->tabWidget->size().width() - 15))
        {
            qDebug()<<QString::fromLocal8Bit("tabWidget大小:")<<ui->tabWidget->size().width()<<QString::fromLocal8Bit("第几个")<<i<<QString::fromLocal8Bit("nxPostion")<<nxPosition<<QString::fromLocal8Bit("设置显示位置x")<<nxPosition;
            int width = allPhoneticWidget.at(i)->width();
            int height = allPhoneticWidget.at(i)->height();
            if(rowHeight < allPhoneticWidget.at(i)->height())
                rowHeight = allPhoneticWidget.at(i)->height();
//            qDebug()<<QString::fromLocal8Bit("设置")<<width<<height;
            allPhoneticWidget.at(i)->setParent(areaWidget);
            allPhoneticWidget.at(i)->setGeometry(xPosition,yPosition,width,height);
            allPhoneticWidget.at(i)->setInitShow();
//            qDebug()<<QString::fromLocal8Bit("这是第几个控件")<<i<<QString::fromLocal8Bit("area区域大小")<<ui->tabWidget->width();
            xPosition = nxPosition;
            rowCount +=1;
        }else
        {
            i -=1;
            xPosition = 10;
            nxPosition = 10;
            rowCount = 1;
            yPosition = yPosition + rowHeight + 10;
            areaWidget->setMinimumHeight(yPosition + rowHeight + 10);
        }
//        qDebug()<<QString::fromLocal8Bit("设置每一个控件的位置X&Y:")<<xPosition<<yPosition<<QString::fromLocal8Bit("一行控件中最高:")<<rowHeight;
//        qDebug()<<QString::fromLocal8Bit("area的控件")<<area->widget();

    }
}





//save预留
void MainWindow::saveAnalysisNetFile()
{

}



void MainWindow::setLeftDockWidget()
{
    ui->leftDockWidget->setWindowTitle(QString::fromLocal8Bit("资源管理器"));
    this->tabifyDockWidget(ui->leftDockWidget,ui->dockWidget_6);
    ui->dockWidget_6->setWindowTitle(QString::fromLocal8Bit("文件"));
}


//设置工具栏  预留
void MainWindow::setMainToolBar()
{
    delete (ui->mainToolBar);
//    AnalysisToolButton = new QToolButton;
//    AnalysisToolButton->setText(QString::fromLocal8Bit("分解"));
//    AnalysisToolButton->setToolTip(QString::fromLocal8Bit("分解"));

//    //add
//    ui->mainToolBar->addWidget(AnalysisToolButton);

}

//
void MainWindow::setTreeWidget(QString dirRootPath)
{
//    ui->treeView->setWindowTitle(QString::fromLocal8Bit("文件系统"));

    fileModel = new QFileSystemModel;
    fileModel->setRootPath("");

    ui->treeView->setModel(fileModel);

    ui->treeView->setRootIndex(fileModel->index(dirRootPath));

    ui->treeView->setColumnHidden(1,1);
    ui->treeView->setColumnHidden(2,1);
    ui->treeView->setColumnHidden(3,1);

    ui->treeView->setHeaderHidden(1);



}






void MainWindow::showFileNameAndFileText()
{

}

QString MainWindow::showFileNameWithFileListView(QString filename)
{
    int lastIndex = filename.lastIndexOf('/');
    QString realFileName = filename.right(filename.length()-lastIndex-1);
    ui->fileListWidget->addItem(new QListWidgetItem(realFileName));
    return realFileName;
}

void MainWindow::showFileTextWithTextEdit(QString filename,QMyMdiSubWindow * oneSession)
{
    //    qDebug()<<QString::fromLocal8Bit("")<<fileDialog->getExistingDirectory();
//    qDebug()<<"SSS"<<
    QTextEdit * textEdit = dynamic_cast<QTextEdit *>(oneSession->widget());
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        if(file.isOpen())
        {
            QTextStream textStream(&file);
                    while (!textStream.atEnd())
                    {
                        textEdit->append(textStream.readLine());
                        //---QtextEdit按行显示文件内容
//                         oneSession->widget()->append(textStream.readLine());
//                         qDebug()<<textStream.readLine();
                    }
        }
}




// 双击文件 显示当前文件
void MainWindow::on_fileListWidget_doubleClicked(const QModelIndex &index)
{

    QString realFileName = index.data().toString();
    qDebug()<<"fileListWidget Dobule clicked:"<<realFileName;
    qDebug()<<"Now column:"<<index.row();
    ui->tabWidget->setCurrentIndex(index.row());


}



//关闭tab
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QString fileName = ui->tabWidget->tabText(index);

//    QList<QListWidgetItem *> itemList =  ui->fileListWidget->findItems(fileName,Qt::MatchCaseSensitive);

//    qDebug()<<"itemList:"<<itemList.at(0)->text();

    QListWidgetItem * removeItem = ui->fileListWidget->takeItem(0);
    ui->fileListWidget->removeItemWidget(removeItem);
    ui->tabWidget->removeTab(index);

    if(ui->tabWidget->count() == 0)
    ui->dockWidget_2->setTitleBarWidget(titleBarWidget);



}






void MainWindow::readyPhonetic()
{
    //添加音标到map
    readINIForPhonetic();

}

QString MainWindow::searchPhonetic(int iPosition)
{

    qDebug()<<"iiPosition"<<iPosition;

    QMap<QString,QString>::Iterator it;

//    搜索map
    QString sPosition = QString::number(iPosition,16);
//    qDebug()<<"Size:"<<Phonetic_Vowel.size()<<Phonetic_Consonant.size();
        if(iPosition>=536870912 &&iPosition<=536870939 )
        {
            it= Phonetic_Consonant.find(sPosition);
//            qDebug()<<sPosition;
            return it.value();
        }else if(iPosition >=268435456 && iPosition <=268435475)
        {
            it= Phonetic_Vowel.find(sPosition);
            return it.value();
        }else if(iPosition == -268435456)
        {
            it = Phonetic_Marks.find(sPosition);
            return it.value();
        }
        return NULL;
}



void MainWindow::readINIForPhonetic()
{
    QSettings *phoneticSymbol = new QSettings(":/conf/phonetic.ini",QSettings::IniFormat);
    QMap<QString,QString> *Phonetic_Ptr;
    QString PhoneticType;
    int count = 0;
    int one;

    for(int i = 0;i<3;i++)
    {
        switch(i)
        {
            case 0:
                count = 20;Phonetic_Ptr = &Phonetic_Vowel;PhoneticType = "/vowel/";one = 0x10000000;break;//元音
            case 1:
                count = 28;Phonetic_Ptr = &Phonetic_Consonant;PhoneticType = "/consonant/";one = 0x20000000;break;//辅音
            case 2:
                count = 2;Phonetic_Ptr = &Phonetic_Marks;PhoneticType = "/marks/";one = 0xf0000000;break;//标示
        }
        //加入Phonetic到map
            for(int i = 0;i<count;i++)
            {
                QString position = QString::number(one,16);
                QString PhoneticPosition = PhoneticType +"0x" + position + "/";
                QString Phonetic =  phoneticSymbol->value(PhoneticPosition).toString();
                Phonetic_Ptr->insert(position,Phonetic);
                one +=1;
//                qDebug()<<"Position:"<<PhoneticPosition<<QString::fromLocal8Bit("音标:")<<Phonetic;

            }
    }
    delete(phoneticSymbol);


}

//测试遍历音标
void MainWindow::TEST()
{
    QMap<QString,QString>::iterator it;
    for(it = Phonetic_Vowel.begin();it!=Phonetic_Vowel.end();it++)
        qDebug()<<QString::fromLocal8Bit("元音:")<<it.value();

    for(it = Phonetic_Consonant.begin();it!=Phonetic_Consonant.end();it++)
        qDebug()<<QString::fromLocal8Bit("辅音:")<<it.value();

    for(it = Phonetic_Marks.begin();it!=Phonetic_Marks.end();it++)
        qDebug()<<QString::fromLocal8Bit("标示:")<<it.value();
}



void MainWindow::writePhoneticForMap(QMap<QString, QString> &phoneticType, int start, int count,QString &allPhonetic)
{
    QString s;
    QString position = QString::number(start,16);
    for(int i = 0;i<count ;i++)
    {
        phoneticType.insert(position,allPhonetic.at(i));
       s = s + allPhonetic.at(i);
    }
//    ui->label_2->setText(s);
}


QString MainWindow::getAllPhone()
{
    QSettings *phoneticSymbol = new QSettings(":/net/phonetic_consonant.ini",QSettings::IniFormat);
    QString cPhonetic =  phoneticSymbol->value("/consonant/0x2000000a").toString();
//    qDebug()<<"What the fuck:"<<cPhonetic;
//    ui->label_3->setText(cPhonetic);


    return cPhonetic;

}





void MainWindow::fromPhoneticWidgetForm(int index,QObject * widget)
{
    QObjectList widgetList = widget->children();

    //v0.01 控制all音标显示控件
//    for(int i = 0;i<allPhoneticWidget.size();i++)
//    {
//        if(i == index)
//        {
//            qDebug()<<QString::fromLocal8Bit("设置")<<index;
//            PhoneticWidgetForm * cleckedWidget_Ptr = dynamic_cast<PhoneticWidgetForm*>(widgetList.at(i));//获取当前点击的控件的地址

//            qDebug()<<QString::fromLocal8Bit("areWidget所有的孩子")<<widgetList;
//           qDebug()<<QString::fromLocal8Bit("当前地址:")<<cleckedWidget_Ptr;
//            cleckedWidget_Ptr->setClickedWidget();//设置该空间的显示
//        }
//        else
//            dynamic_cast<PhoneticWidgetForm*>(widgetList.at(i))->setOtherWidget();
//    }

    //v0.02 控制鼠标邻近控制两个控件


//    PhoneticWidgetForm * cleckedWidget_Ptr = dynamic_cast<PhoneticWidgetForm*>(widgetList.at(index));//获取当前点击的控件的地址
//    cleckedWidget_Ptr->setClickedWidget();

//    if(index != oldWidgetIndex)
//    {

//        oldCleckedWidget_Ptr->setOtherWidget();
//    }
//    oldWidgetIndex = index;

        PhoneticWidgetForm * nextWidget_Ptr;
    {
        //跟新所有的关键词显示
        for(int i = 0;i<widgetList.size();i++)
        {
            nextWidget_Ptr = dynamic_cast<PhoneticWidgetForm*>(widgetList.at(i));//获取当前点击的控件的地址
            nextWidget_Ptr->setInitShow();
        }
    }


    PhoneticWidgetForm * indexWidget_Ptr = dynamic_cast<PhoneticWidgetForm*>(widgetList.at(index));//获取索引的控件的地址
    if(indexWidget_Ptr->getKeyStatus())
        indexWidget_Ptr->setKeyWordShow();
    else
        indexWidget_Ptr->setClickedWidget();

}





void MainWindow::resizeEvent(QResizeEvent *event)
{
//    qDebug()<<QString::fromLocal8Bit("重置子控件大小")<<this->size()<<QString::fromLocal8Bit("scrollwidget大小")<<ui->tabWidget->size()<<areaWidget->size();
    update(areaWidget);
//    ui->centralWidget->resize(this->size());

}



//打开文件夹
void MainWindow::on_action_4_triggered()
{
    ui->tabWidget->clear();
    if(operationType)
    {
        ui->tabWidget->clear();
        ui->fileListWidget->clear();

    }

         QStandardItemModel *model = new QStandardItemModel(this);
        QString dirPath = QFileDialog::getExistingDirectory();
        Net_Dir_Path = dirPath;
        qDebug()<<"Net_Dir_Path"<<Net_Dir_Path;

        if(dirPath.length() > 0)
        {
            int lastIndex = dirPath.lastIndexOf('/');
            QString dirName = dirPath.right(dirPath.length()-lastIndex-1);


            QStandardItem * treeRootDir = new QStandardItem(dirName);
            treeRootDir->setIcon(QIcon(":/image/folder.png"));
            treeRootDir->setEditable(false);
            model->appendRow(treeRootDir);



            QDir dir(dirPath);
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
            QStringList nameFilters;
            nameFilters<<"*.net";
            dir.setNameFilters(nameFilters);
            QFileInfoList infoList = dir.entryInfoList();
            QMap<QString,QString>::iterator it = fileNameAndPathMap.begin();
            for(int i = 0;i<infoList.size();i++)
            {
                qDebug()<<QString::fromLocal8Bit("所有文件:")<<infoList.at(i).fileName()<<infoList.at(i).filePath();
                fileNameAndPathMap.insert(it,infoList.at(i).fileName(),infoList.at(i).filePath());

                QStandardItem * fileName = new QStandardItem(infoList.at(i).fileName());
                fileName->setEditable(false);
                fileName->setIcon(QIcon(":/image/file.png"));
                treeRootDir->appendRow(fileName);

            }

            ui->leftDockWidget->raise();



            ui->treeView->setModel(model);
    //        ui->treeView->setItemsExpandable(true);
            ui->treeView->expandAll();

            operationType = DIR_SELECT;


        }



}









void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<QString::fromLocal8Bit("索引")<<index<<index.data().toString()<<ui->tabWidget->tabBar()->tabText(0);
//    qDebug()<<"Property"<<objectName()<<ui->treeView->indexWidget(index)->property("net");
//    if(ui->treeView->parent()->objectName())

    if(index.parent().isValid())
    netFileIsAnalysis();

}

void MainWindow::netFileIsAnalysis()
{
            bool exeitFlag = false;
            for(int i = 0;i<ui->tabWidget->count();i++)
            {
                qDebug()<<"fileIndex"<<fileIndex;
                if(fileIndex.data().toString() == ui->tabWidget->tabBar()->tabText(i))
                {
                    ui->tabWidget->setCurrentIndex(i);
                    exeitFlag = true;
                    break;
                }
            }
            if(!exeitFlag)//true: 已经打开
            {
                slotSetPhoneticDialog();
                QWidget * widget = new QWidget;
                ui->dockWidget_2->setTitleBarWidget(widget);
            }
}




//资源管理器
//打开文件夹右键出现开始解析菜单
void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{


    QMenu menu;
    QAction *action1 = new QAction(QString::fromLocal8Bit("开始解析"),this);
//    QAction *action2 = new QAction(QString::fromLocal8Bit("打开文件"),this);
//    QAction * close = new QAction(QString::fromLocal8Bit("关闭"));

    QAction * action3 = new QAction(QString::fromLocal8Bit("生成文本(all)"),this);

    QList<QAction *>actionList;
   actionList<<action1;
  menu.addActions(actionList);
   connect(action1,&QAction::triggered,this,&MainWindow::rightCleckedAnalysis);
//   connect(close,&QAction::triggered,this,&MainWindow::);


    QMenu menu2;
    QList<QAction *>actionList2;
    actionList2<<action3;
    menu2.addActions(actionList2);
    connect(action3,&QAction::triggered,this,&MainWindow::rightCleckedAnalysis);


    if(rootNode)
    menu.exec(QCursor::pos());
    else
        menu2.exec(QCursor::pos());


}


void MainWindow::rightCleckedAnalysis()
{
    if(rootNode)
    {
        qDebug()<<QString::fromLocal8Bit("KKKKK");
        netFileIsAnalysis();
    }else
    {
        qDebug()<<QString::fromLocal8Bit("KKKKK");
        writeNetlText2File();
    }

}










//打开文件
void MainWindow::on_fileListWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    QAction *action2 = new QAction(QString::fromLocal8Bit("开始解析"),this);
//    QAction * close = new QAction(QString::fromLocal8Bit("关闭"));

   QList<QAction *>actionList;
   actionList<<action2;

//   connect(action2,&QAction::triggered,this,&MainWindow::slotSetPhoneticDialog);

//   connect(close,&QAction::triggered,this,&MainWindow::);

//    menu.addActions(actionList);
//    menu.exec(QCursor::pos());
}






void MainWindow::writeNetlText2File()
{
    HMNSESSION  session;
    loginEngine(session);
    QString nowPath = Net_Dir_Path;
    QString netTextPath = nowPath + "/net_text.txt";

    QFile fileName;

   int fileStatus =  fileName.exists(netTextPath);
   qDebug()<<"fileStatus"<<fileStatus;
   if(!fileStatus)
   {
       fileName.setFileName(netTextPath);
       if(!fileName.open(QIODevice::WriteOnly|QIODevice::Text))
       {
           qDebug()<<QString::fromLocal8Bit("打开失败");
       }
       fileName.close();
   }
   else
       fileName.remove(netTextPath);

    qDebug()<<"netTextPath "<<netTextPath;


//    for()
    int net_account = 0;
    QMap<QString,QString>::iterator it = fileNameAndPathMap.begin();
    for(;it!=fileNameAndPathMap.end();it++)
    {
        net_account+=1;
             qDebug()<<"IT:"<<it.key()<<"  "<<it.value();

            //写入该文件夹先所有的net的文本到net_text.txt文件
            QFile netFile(it.value());
            netFile.open(QIODevice::ReadOnly);
            if(netFile.isOpen())
                qDebug()<<"net file open successful!";
            else
            {
                QMessageBox box;
                box.setText(QString::fromLocal8Bit("net 文件读取错误,请检查net打开操作!"));
                box.exec();
            }

            char *data = (new char[netFile.size()]);
            netFile.read(data,netFile.size());
             qDebug()<<"Read Data"<<data;

            int loadStatus = LoadNet(session,data,netFile.size());

            if(loadStatus)
            {
                qDebug()<<"LoadNet successful!";
                netCodeStatus = true;


            }
            else
            {
            QMessageBox box;
            box.setText(QString::fromLocal8Bit("加载Net文件时出现错误,请检查解析密码"));
            box.exec();

                netCodeStatus = false;
            }
            if(netCodeStatus)
            {
                char gText[1024];
                int GetOrgTextStatus =  GetOrgText(session,gText,1024);
                if(!GetOrgTextStatus)
                    qDebug()<<QString::fromLocal8Bit("获取net文本成功:")<<gText;
//                int wordCount = GetTextSplitCount(session);

                QFile write_file(netTextPath);

                write_file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
                QByteArray num = QString::number(net_account).toLatin1() + ">";
                write_file.write(num,2);
                write_file.write(gText,strlen(gText));
                write_file.write("\n",1);
                write_file.write("\n",1);
                write_file.close();
              }

        }
    if(net_account)
    {
        QMessageBox box;
        box.setText(QString::fromLocal8Bit("文本写入:") + netTextPath);
        box.exec();
    }
}



//打开文件夹文件分析net
void MainWindow::slotSetPhoneticDialog()
{
//    this->setPhoneticDialog();
    QMap<QString,QString>::iterator it;
    for(it = fileNameAndPathMap.begin();it!=fileNameAndPathMap.end();it++)
        qDebug()<<QString::fromLocal8Bit("遍历图:")<<it.key()<<it.value();


     QString fileNamePath = searchFileNameAllPath(rightClickedGetFileName);
    qDebug()<<QString::fromLocal8Bit("文件路径")<<fileNamePath;

    analysisNetFile(fileNamePath);//引擎加载net文件并分解
    if(netCodeStatus)
    this->setPhoneticDialog(fileNamePath);
}


void MainWindow::on_treeView_pressed(const QModelIndex &index)
{
//    if(QGuiApplication::mouseButtons() == Qt::RightButton)
//    {
        qDebug()<<QString::fromLocal8Bit("右键索引:")<<index;
        QAbstractItemModel *model =(QAbstractItemModel *)(index.model());




        rightClickedGetFileName = model->data(index).toString();
        qDebug()<<"Get:"<<rightClickedGetFileName;

        fileIndex = index;

        rootNode =index.parent().isValid();
        qDebug()<<QString::fromLocal8Bit("打开文件夹右击判断是否是目录还是文件")<<rootNode;

//    }
}

QString MainWindow::searchFileNameAllPath(QString key)
{
    return fileNameAndPathMap.find(key).value();
}


//设置选项
void MainWindow::on_actionSet_triggered()
{

    set->exec();
    set-> showCode();
    ebCode = set->getCode();



}









//log
void MainWindow::on_actionM_triggered(bool checked)
{
    if(checked)
    {
            logWidget->show();
    }
    else
    {
        logWidget->hide();
    }
}

//属性
void MainWindow::on_action_triggered(bool checked)
{
    if(checked)
    {
        propertyWidget->show();
    }else
    {
        propertyWidget->hide();
    }

}

//退出
void MainWindow::on_actionW_triggered()
{
    qApp->exit();
}

//关于
void MainWindow::on_action_2_triggered()
{
    AboutDialog * about = new AboutDialog(this);
    about->exec();
}

void MainWindow::on_action_3_triggered()
{
    DescDialog * desc = new DescDialog(this);
    desc->exec();
}

//dock关闭信号、

void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    if(visible)
    ui->actionM->setChecked(true);
    else
        ui->actionM->setChecked(false);
}

void MainWindow::on_dockWidget_3_visibilityChanged(bool visible)
{
    if(visible)
    ui->action->setChecked(true);
    else
        ui->action->setChecked(false);
}



