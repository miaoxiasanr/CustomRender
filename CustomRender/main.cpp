#include "CustomRender.h"
#include <QtWidgets/QApplication>
#include "CustomVector.h"
#include "CustomMatrix.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    CustomRender w;
    w.show();
    return a.exec();
}
