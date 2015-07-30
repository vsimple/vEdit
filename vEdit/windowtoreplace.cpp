#include "windowtoreplace.h"
#include "ui_windowtoreplace.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

WindowToReplace::WindowToReplace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowToReplace)
{
    ui->setupUi(this);

    this->setWindowTitle("替换");
    this->setMaximumSize(300, 150);
    this->setMinimumSize(300, 150);

    hboxLayout1 = new QHBoxLayout();
    label1 = new QLabel("需要查找的内容：");
    findLine = new QLineEdit();
    hboxLayout1->addWidget(findLine);

    hboxLayout2 = new QHBoxLayout();
    label2 = new QLabel("替换为：");
    replaceLine = new QLineEdit();
    replaceButton = new QPushButton("替换");
    hboxLayout2->addWidget(replaceLine);
    hboxLayout2->addWidget(replaceButton);

    vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(label1);
    vboxLayout->addLayout(hboxLayout1);
    vboxLayout->addWidget(label2);
    vboxLayout->addLayout(hboxLayout2);

    widget = new QWidget();
    widget->setLayout(vboxLayout);
    this->setCentralWidget(widget);
}

WindowToReplace::~WindowToReplace()
{
    delete ui;
}
