#include "taba.h"
#include <QPushButton>

tabA::tabA(QWidget *parent) : QWidget(parent)
{
    QPushButton *buttonA = new QPushButton(this);
    buttonA->setText("页面A");
}

