#include "QtWidgetsApplication.h"
#include"PWMChoosing.h"
#include"Car_Function.h"
#include<QPushButton>
#include<windows.h>
QtWidgetsApplication::QtWidgetsApplication(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(600, 400);
    this->setWindowTitle("菜单");
    ui.setupUi(this);
    showportwindow();
    Init_The_Code();
}
void QtWidgetsApplication::Init_The_Code()
{
    QPushButton* start = new QPushButton("初始化",this);
    connect(start, &QPushButton::clicked, this, showportwindow);
    start->resize(50,40);
    

    connect(ui.exit, &QPushButton::clicked, this,exitexe);
    connect(ui.Buttonfront, &QPushButton::clicked, this,forward);
    connect(ui.Buttonback, &QPushButton::clicked, this,backward);
    connect(ui.fastleft, &QPushButton::clicked, this,leftfast);
    connect(ui.fastright, &QPushButton::clicked, this, rightfast);
    connect(ui.leftturn, &QPushButton::clicked, this, leftmove);
    connect(ui.rightturn, &QPushButton::clicked, this,rightmove);
    connect(ui.PWMspeed, &QPushButton::clicked, this, ShowPWMPlace);
}
QtWidgetsApplication::~QtWidgetsApplication()
{}
