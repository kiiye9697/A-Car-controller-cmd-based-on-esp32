#include "PWMChoosing.h"
#include<QInputDialog>
#include "Car_Function.h"
PWMChoosing::PWMChoosing(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	bool ok;
	PWM = QInputDialog::getInt(this, tr("Choose The PWM"), tr("Please input:"), 100,0, 255,1, &ok);
	initSerialPort(comPort, Baudrate);
	changePWM();
}
PWMChoosing::~PWMChoosing()
{}
void ShowPWMPlace()
{
	PWMChoosing wycbbhb;
	wycbbhb.show();
}
