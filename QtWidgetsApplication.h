#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidgetsApplication.h"

class QtWidgetsApplication : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsApplication(QWidget *parent = nullptr);
    ~QtWidgetsApplication();
    void Init_The_Code();
    Ui::QtWidgetsApplicationClass ui;
};
void showportwindow();
