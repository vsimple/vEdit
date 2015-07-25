#include "tabb.h"
#include <QPushButton>

tabB::tabB(QWidget *parent) : QWidget(parent)
{
    QPushButton *buttonB = new QPushButton(this);
    buttonB->setText("页面B");
}

