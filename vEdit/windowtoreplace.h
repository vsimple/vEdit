#ifndef WINDOWTOREPLACE_H
#define WINDOWTOREPLACE_H

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QWidget;

namespace Ui {
class WindowToReplace;
}

class WindowToReplace : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowToReplace(QWidget *parent = 0);
    ~WindowToReplace();

private:
    Ui::WindowToReplace *ui;
    QLabel *label1, *label2;
    QLineEdit *findLine;
    QLineEdit *replaceLine;
    QPushButton *replaceButton;
    QHBoxLayout *hboxLayout1, *hboxLayout2;
    QVBoxLayout *vboxLayout;
    QWidget *widget;
};

#endif // WINDOWTOREPLACE_H
