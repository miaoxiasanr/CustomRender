#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CustomRender.h"

class CustomRender : public QMainWindow
{
    Q_OBJECT

public:
    CustomRender(QWidget *parent = nullptr);
    ~CustomRender();

private:
    Ui::CustomRenderClass ui;
};
