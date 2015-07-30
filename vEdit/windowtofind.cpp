#include "windowtofind.h"
#include "ui_windowtofind.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>

WindowToFind::WindowToFind(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowToFind)
{
    ui->setupUi(this);
    this->setWindowTitle("查找");
    this->setMaximumSize(300, 100);
    this->setMinimumSize(300, 100);

    hboxLayout = new QHBoxLayout();
    label = new QLabel("需要查找的内容：");
    inputLine = new QLineEdit();
    findButton = new QPushButton("查找");
    hboxLayout->addWidget(inputLine);
    hboxLayout->addWidget(findButton);

    vboxLayout = new QVBoxLayout();
    vboxLayout->addWidget(label);
    vboxLayout->addLayout(hboxLayout);

    widget = new QWidget();
    widget->setLayout(vboxLayout);
    this->setCentralWidget(widget);
}

WindowToFind::~WindowToFind()
{
    delete ui;
}
