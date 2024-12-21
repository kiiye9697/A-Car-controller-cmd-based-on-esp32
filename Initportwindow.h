#pragma once

#include <QWidget>
#include "ui_Initportwindow.h"

class Initportwindow : public QWidget
{
	Q_OBJECT

public:
	Initportwindow(QWidget *parent = nullptr);
	~Initportwindow();

private:
	Ui::InitportwindowClass ui;
};
