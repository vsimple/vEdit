#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardItem>
#include <QPushButton>
#include <QWidget>
#include "taba.h"
#include "tabb.h"

int MainWindow::numTabTop = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 菜单实例
    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    helpMenu = new QMenu(this);

    // 填充菜单子节点
    newAction = new QAction(QIcon(":/images/new"), tr("新建"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("新建文件"));
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAction = new QAction(QIcon(":/images/open"), tr("打开"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("打开文件"));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    cutAction = new QAction(QIcon(":/images/cut"), tr("剪切"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("剪切内容"));

    pasteAction = new QAction(QIcon(":/images/paste"), tr("粘贴"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("粘贴内容"));

    aboutAction = new QAction(QIcon(":/images/about"), tr("关于"), this);
    aboutAction->setStatusTip(tr("关于信息"));
    connect(aboutAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    // 填充菜单
    fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();

    editMenu = menuBar()->addMenu(tr("编辑"));
    editMenu->addAction(cutAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(aboutAction);

    // 填充工具栏
    fileToolBar = addToolBar(tr("新建"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);

    editToolBar = addToolBar(tr("修改"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(pasteAction);

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

    QStandardItem *item1 = new QStandardItem("计算机");
    item1->setIcon(QIcon(":images/home"));

    QStandardItem *item2 = new QStandardItem("编译原理");
    item2->setIcon(QIcon(":images/right"));

    item1->appendRow(item2);
    modelLeft->setItem(0, 0, item1);
    treeViewLeft->setModel(modelLeft);

    // 中间布局 代码编辑器
    //textEdit = new QTextEdit(this);
    //textEdit->setText("我是第一行<br/>我是第二行");
    //codeeditor = new CodeEditor(this);

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
    QString tabName("Untitled");
    tabName = tabName + QString::number(numTabTop, 10);

    CodeEditor *editorNew = new CodeEditor(tabWidgetTop);
    tabWidgetTop->addTab(editorNew, tabName);
    connect(editorNew, SIGNAL(textChanged()), editorNew, SLOT(textTopChangeTag()));
    numTabTop++;
}


void MainWindow::tabCloseTop(int index)
{
    CodeEditor *temp = qobject_cast<CodeEditor*>(tabWidgetTop->widget(index));
    QString s = temp->toPlainText();
    if(s != "" && temp->everChanged == 1)
    {
        if(QMessageBox::Yes == QMessageBox::question(this,
                                                 tr("保存文件"),
                                                 tr("内容被修改\n确定要保存？"),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes))
        {
            tabWidgetTop->setTabText(index, "Hello");


        }
        else
        {
            tabWidgetTop->removeTab(index);
        }
    }
    else
    {
        tabWidgetTop->removeTab(index);
    }

}

void MainWindow::openFile()
{
    QFileDialog::getOpenFileName(this, "open file", "/", "test file(*.txt);;C file(*.cpp);;All file(*.*)");
}

MainWindow::~MainWindow()
{
    delete ui;
}
