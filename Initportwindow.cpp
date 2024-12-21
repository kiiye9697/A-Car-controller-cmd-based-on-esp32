#include "Initportwindow.h"
#include<qinputdialog>
#include"Car_Function.h"

Initportwindow::Initportwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(80, 50);
    bool ok;
    QString string = QInputDialog::getText(this, tr("Choose Your COM"),tr("Please choose the com:"), QLineEdit::Normal, tr("COM3"), &ok);
	comPort=stringToWstring(string.toStdString());
	//完成界面中数据的输入与转换。
    Baudrate = QInputDialog::getInt(this, tr("Choose The Rate"),tr("Please input:"), 9600, -1000, 1000, 10, &ok);
	initSerialPort(comPort,Baudrate);
}

Initportwindow::~Initportwindow()
{}
void showportwindow() 
{
	Initportwindow nom;
	nom.show();
};//提供接口进入交互界面