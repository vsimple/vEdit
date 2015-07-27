#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
#include <QMainWindow>
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
*/

#include <QMainWindow>
class QAction;
class QMenuBar;
class QMenu;
class QToolBar;
class QVBoxLayout;
class QHBoxLayout;
class QTreeView;
class QStandardItemModel;
class QTextEdit;
class QWidget;
class QSplitter;
class QTabWidget;
class CodeEditor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // 菜单栏、工具栏
    QMenu *fileMenu, *editMenu, *helpMenu;
    QToolBar *fileToolBar, *editToolBar, *helpToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    // 布局
    QWidget *widget;
    QVBoxLayout *vboxLeft, *vboxMiddle, *vboxRight;
    QHBoxLayout *hboxLayout;

    QSplitter *splitterMain, *splitterMiddle;

    // 左边：树形视图
    QTreeView *treeViewLeft, *treeViewRight;
    QStandardItemModel *modelLeft, *modelRight;

    // 中间：代码编辑器
    QTextEdit *textEdit;
    CodeEditor *codeeditor;
    QTabWidget *tabWidgetTop, *tabWidgetDown;
    int newTab;

    static int numTabTop;


private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void tabCloseTop(int);
};

#endif // MAINWINDOW_H
