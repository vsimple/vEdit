#ifndef WINDOWTOFIND_H
#define WINDOWTOFIND_H

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QWidget;

namespace Ui {
class WindowToFind;
}

class WindowToFind : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowToFind(QWidget *parent = 0);
    ~WindowToFind();

private:
    Ui::WindowToFind *ui;
    QLabel *label;
    QLineEdit *inputLine;
    QPushButton *findButton;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QWidget *widget;
};

#endif // WINDOWTOFIND_H
