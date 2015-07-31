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
class QStandardItem;
class WindowToFind;
class WindowToReplace;

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
    QMenu *fileMenu, *editMenu, *searchMenu, *buildMenu, *helpMenu;
    QMenu *recentMenu;
    QToolBar *fileToolBar, *editToolBar, *searchToolBar, *buildToolBar, *helpToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *findAction;
    QAction *replaceAction;
    QAction *compileAction;
    QAction *runAction;
    QAction *aboutAction;

    // 布局
    QWidget *widget;
    QVBoxLayout *vboxLeft, *vboxMiddle, *vboxRight;
    QHBoxLayout *hboxLayout;

    QSplitter *splitterMain, *splitterMiddle;

    // 左边：树形视图
    QTreeView *treeViewLeft, *treeViewRight;
    QStandardItemModel *modelLeft, *modelRight;
    QStandardItem *topItemLeft;

    // 中间：代码编辑器
    QTextEdit *textEdit;
    CodeEditor *codeeditor;
public:
    QTabWidget *tabWidgetTop, *tabWidgetDown;
    int newTab;

    static int numTabTop;
public:
    static int currentTabIndex;
private:
    WindowToFind *find;
    WindowToReplace *replace;


private:
    void subMenu();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void tabCloseTop(int);
    void changeTab();
    void findWindow();
    void replaceWindow();
    void pasteContext();
    void undoContext();
    void redoContext();
    void cutContext();

};

#endif // MAINWINDOW_H
