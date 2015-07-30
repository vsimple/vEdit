#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QWidget>
#include <QSplitter>
#include <QTabWidget>
#include "codeeditor.h"
#include <QTextStream>
#include <QFile>

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardItem>
#include <QPushButton>
#include <QWidget>
#include "taba.h"
#include "tabb.h"
#include "highlighter.h"

int MainWindow::numTabTop = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 菜单实例
    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    searchMenu = new QMenu(this);
    buildMenu = new QMenu(this);
    helpMenu = new QMenu(this);
    recentMenu = new QMenu(fileMenu);

    // 填充菜单子节点
    newAction = new QAction(QIcon(":/images/new"), tr("新建"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("新建文件"));
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAction = new QAction(QIcon(":/images/open"), tr("打开"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("打开文件"));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    saveAction = new QAction(QIcon(":/images/save"), tr("保存"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("保存文件"));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));

    saveAsAction = new QAction(QIcon(":/images/saveAs"), tr("另存为"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("另存为文件"));
    connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAsFile()));

    cutAction = new QAction(QIcon(":/images/cut"), tr("剪切"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("剪切内容"));

    pasteAction = new QAction(QIcon(":/images/paste"), tr("粘贴"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("粘贴内容"));

    undoAction = new QAction(QIcon(":/images/undo"), tr("撤销"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(tr("撤销内容"));

    redoAction = new QAction(QIcon(":/images/redo"), tr("重做"), this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(tr("重做内容"));

    findAction = new QAction(QIcon(":/images/find"), tr("查找"), this);
    // runAction->setShortcut("Ctrl+f8");
    findAction->setStatusTip(tr("查找内容"));

    replaceAction = new QAction(QIcon(":/images/replace"), tr("替换"), this);
    // runAction->setShortcut("Ctrl+f8");
    replaceAction->setStatusTip(tr("替换内容"));

    runAction = new QAction(QIcon(":/images/run"), tr("运行"), this);
    // runAction->setShortcut("Ctrl+f8");
    runAction->setStatusTip(tr("运行程序"));

    compileAction = new QAction(QIcon(":/images/compile"), tr("编译"), this);
    // redoAction->setShortcut("Ctrl+f9");
    compileAction->setStatusTip(tr("编译程序"));

    aboutAction = new QAction(QIcon(":/images/about"), tr("关于"), this);
    aboutAction->setStatusTip(tr("关于信息"));
    connect(aboutAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    // 填充菜单
    fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    subMenu();


    editMenu = menuBar()->addMenu(tr("编辑"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();

    searchMenu = menuBar()->addMenu(tr("搜索"));
    searchMenu->addAction(findAction);
    searchMenu->addAction(replaceAction);

    buildMenu = menuBar()->addMenu(tr("构造"));
    buildMenu->addAction(compileAction);
    buildMenu->addAction(runAction);

    helpMenu = menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(aboutAction);

    // 填充工具栏
    fileToolBar = addToolBar(tr("新建"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("修改"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);

    searchToolBar = addToolBar(tr("搜索"));
    searchToolBar->addAction(findAction);
    searchToolBar->addAction(replaceAction);

    buildToolBar = addToolBar(tr("构造"));
    buildToolBar->addAction(compileAction);
    buildToolBar->addAction(runAction);

    helpToolBar = addToolBar(tr("帮助"));
    helpToolBar->addAction(aboutAction);

    // 页面布局
    vboxLeft = new QVBoxLayout();
    vboxMiddle = new QVBoxLayout();
    vboxRight = new QVBoxLayout();
    hboxLayout = new QHBoxLayout();

    // 左边布局 树形视图
    treeViewLeft = new QTreeView(this);
    modelLeft = new QStandardItemModel(1, 1);
    modelLeft->setHeaderData(0, Qt::Horizontal, "工程");

    topItemLeft = new QStandardItem("计算机");
    topItemLeft->setIcon(QIcon(":images/home"));

    modelLeft->setItem(0, 0, topItemLeft);
    treeViewLeft->setModel(modelLeft);

    connect(treeViewLeft, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(changeTab()));

    // 中间布局 代码编辑器
    //textEdit = new QTextEdit(this);
    //textEdit->setText("我是第一行<br/>我是第二行");
    //codeeditor = new CodeEditor(this);

    newTab = 0;
    tabWidgetTop = new QTabWidget(this);
    tabWidgetTop->setTabsClosable(true);
    tabWidgetTop->setTabShape(QTabWidget::Rounded);
    connect(tabWidgetTop, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseTop(int)));

    tabWidgetDown = new QTabWidget(this);
    tabA *tab1 = new tabA(tabWidgetDown);
    tabB *tab2 = new tabB(tabWidgetDown);
    tabWidgetDown->addTab(tab1, "A栏目");
    tabWidgetDown->addTab(tab2, "B栏目");

    // 右边布局
    treeViewRight = new QTreeView(this);
    modelRight = new QStandardItemModel(1, 1);
    modelRight->setHeaderData(0, Qt::Horizontal, "工程");

    QStandardItem *item3 = new QStandardItem("计算机");
    item3->setIcon(QIcon(":images/home"));

    QStandardItem *item4 = new QStandardItem("编译原理");
    item4->setIcon(QIcon(":images/right"));

    item3->appendRow(item4);
    modelRight->setItem(0, 0, item3);
    treeViewRight->setModel(modelRight);


    //
    /*
    vboxLeft->addWidget(treeViewLeft);
    vboxMiddle->addWidget(textEdit);
    vboxRight->addWidget(treeViewRight);

    hboxLayout->addLayout(vboxLeft);
    hboxLayout->addLayout(vboxMiddle);
    hboxLayout->addLayout(vboxRight);
    hboxLayout->setStretch(0, 1);
    hboxLayout->setStretch(1, 4);
    hboxLayout->setStretch(2, 1);
    */
    splitterMain = new QSplitter(Qt::Horizontal, this);
    splitterMain->addWidget(treeViewLeft);
    splitterMiddle = new QSplitter(Qt::Vertical, splitterMain);
    //splitterMiddle->addWidget(codeeditor);
    splitterMiddle->addWidget(tabWidgetTop);
    splitterMiddle->addWidget(tabWidgetDown);
    splitterMiddle->setStretchFactor(0, 8);
    splitterMiddle->setStretchFactor(1, 1);
    splitterMain->addWidget(treeViewRight);
    splitterMain->setStretchFactor(0, 1);
    splitterMain->setStretchFactor(1, 6);
    splitterMain->setStretchFactor(2, 1);

    setCentralWidget(splitterMain);
    //widget = new QWidget();
    //widget->setLayout(splitterMain);
    //this->setCentralWidget(widget);
}

void MainWindow::newFile()
{
    newTab = 0;
    QString tabName("Untitled");
    tabName = tabName + QString::number(numTabTop, 10);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(11);

    CodeEditor *editorNew = new CodeEditor(tabWidgetTop);
    editorNew->setFont(font);
    new Highlighter(editorNew->document());
    tabWidgetTop->addTab(editorNew, tabName);
    connect(editorNew, SIGNAL(textChanged()), editorNew, SLOT(textTopChangeTag()));
    connect(undoAction, SIGNAL(triggered(bool)), editorNew, SLOT(undo()));
    connect(redoAction, SIGNAL(triggered(bool)), editorNew, SLOT(redo()));
    connect(cutAction, SIGNAL(triggered(bool)), editorNew, SLOT(cut()));
    connect(pasteAction, SIGNAL(triggered(bool)), editorNew, SLOT(paste()));
    connect(findAction, SIGNAL(triggered(bool)), editorNew, SLOT(findWindow()));
    connect(replaceAction, SIGNAL(triggered(bool)), editorNew, SLOT(replaceWindow()));
    numTabTop++;
}

void MainWindow::saveFile()
{
    if(!newTab)
    {
        newTab = 1;
        saveAsFile();
    }
    else
    {
        int index = tabWidgetTop->currentIndex();
        CodeEditor *temp = qobject_cast<CodeEditor*>(tabWidgetTop->widget(index));
        QString fileName = tabWidgetTop->tabText(index);

        QFile file(fileName);
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            return;
        }
        QTextStream out(&file);
        out << temp->toPlainText();
        temp->everChanged = 0;
    }
}

void MainWindow::saveAsFile()
{
    int index = tabWidgetTop->currentIndex();
    CodeEditor *temp = qobject_cast<CodeEditor*>(tabWidgetTop->widget(index));
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存为"),tr("未命名.c"), tr("test file(*.txt);;C file(*.c);"));
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream out(&file);
    out << temp->toPlainText();
    tabWidgetTop->setTabText(index, fileName);
    temp->everChanged = 0;

}

void MainWindow::tabCloseTop(int index)
{
    CodeEditor *temp = qobject_cast<CodeEditor*>(tabWidgetTop->widget(index));
    QString s = temp->toPlainText();
    if(s != "" && temp->everChanged == 1)
    {
        int r = QMessageBox::warning(this,
                                     tr("保存文件"),
                                     tr("内容被修改\n是否要保存？"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                     QMessageBox::Yes);
        if( r == QMessageBox::Yes)
        {
            saveFile();
        }
        else if( r == QMessageBox::No)
        {
            tabWidgetTop->removeTab(index);
            numTabTop--;
        }
    }
    else
    {
        tabWidgetTop->removeTab(index);
        numTabTop--;
    }

}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "open file", "/codefiles/cpp", "C file(*.c);;test file(*.txt);;C++ file(*.cpp);;All file(*.*)");
    if(!fileName.isEmpty())
    {
        newTab = 1;


        // 添加目录

        QString path = fileName.section('/', -2);
        QString name = fileName.section('/', -1);
        QString project = path.left(path.size() - name.size() - 1);
        QStandardItem *itemFile = new QStandardItem(name);
        QStandardItem *itemProject = new QStandardItem(project);
        itemFile->setIcon(QIcon(":/images/right"));
        itemProject->setIcon(QIcon(":/images/down"));
        itemFile->setEditable(false);
        itemProject->setEditable(false);     

        itemProject->appendRow(itemFile);
        topItemLeft->appendRow(itemProject);

        //int position = fileName.lastIndexOf('/');
        //QString tabName = fileName.right(fileName.size() - position - 1);

        QFont font;
        font.setFamily("Courier");
        font.setFixedPitch(true);
        font.setPointSize(11);

        CodeEditor *editorNew = new CodeEditor(tabWidgetTop);
        editorNew->setFont(font);

        new Highlighter(editorNew->document());
        tabWidgetTop->addTab(editorNew, name);

        QFile file(fileName);
        if (!file.open(QIODevice::ReadWrite))
            return;
        QTextStream out(&file);
        while(!file.atEnd())
        {
             editorNew->setPlainText(out.readAll());
        }

        tabWidgetTop->setCurrentIndex(numTabTop);
        numTabTop++;


        QString pathFile = "D:\\vEdit.txt";
        QString str;
        QFile filePath(pathFile);
        if (filePath.open(QIODevice::ReadWrite))
        {
            int exist = 0;
            QTextStream out(&filePath);
            while(!out.atEnd())
            {
                str = out.readLine();
                if(str == fileName)
                    exist = 1;
            }
            if( !exist )
                out << '\n' << fileName;
            file.close();
        }
        connect(undoAction, SIGNAL(triggered(bool)), editorNew, SLOT(undo()));
        connect(redoAction, SIGNAL(triggered(bool)), editorNew, SLOT(redo()));
        connect(cutAction, SIGNAL(triggered(bool)), editorNew, SLOT(cut()));
        connect(pasteAction, SIGNAL(triggered(bool)), editorNew, SLOT(paste()));
        connect(findAction, SIGNAL(triggered(bool)), editorNew, SLOT(findWindow()));
        connect(replaceAction, SIGNAL(triggered(bool)), editorNew, SLOT(replaceWindow()));
    }
}

void MainWindow::changeTab()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(treeViewLeft->model());
    QModelIndex index = treeViewLeft->currentIndex();
    QStandardItem* item = model->itemFromIndex(index);
    tabWidgetTop->setCurrentIndex(item->parent()->row());
}

void MainWindow::subMenu()
{
    recentMenu->setTitle(tr("最近打开"));

    QString path = "D:\\vEdit.txt";
    QString str;
    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        int i = 1;
        QTextStream out(&file);
        QStringList store;
        while(!out.atEnd())
        {
            store << out.readLine();
            /*
            str = out.readLine();
            QAction *temp = new QAction(QIcon(":/images/add"), QString("%1 %2").arg(i).arg(str), this);
            temp->setStatusTip(str);
            recentMenu->addAction(temp);
            i++;
            */
        }
        file.close();

        int len = store.size();
        while(i <= len)
        {
            QAction *temp = new QAction(QIcon(":/images/add"), QString("%1 %2").arg(i).arg(store[len - i]), this);
            temp->setStatusTip(str);
            recentMenu->addAction(temp);
            i++;
        }
    }
    str = "清除历史";
    QAction *clearHistory = new QAction(QIcon(":/images/clear"), str, this);
    clearHistory->setStatusTip(str);
    recentMenu->addAction(clearHistory);

    fileMenu->addMenu(recentMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}
