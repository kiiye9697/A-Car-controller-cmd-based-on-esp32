#pragma once

#include <QMainWindow>
#include "ui_PWMChoosing.h"

class PWMChoosing : public QMainWindow
{
	Q_OBJECT

public:
	PWMChoosing(QWidget *parent = nullptr);
	~PWMChoosing();

private:
	Ui::PWMChoosingClass ui;
};
void ShowPWMPlace();
