#include "CustomRender.h"

CustomRender::CustomRender(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setFixedSize(1280, 720);
}

CustomRender::~CustomRender()
{}
