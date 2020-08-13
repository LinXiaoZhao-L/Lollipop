#include "HappyEliminate.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    HappyEliminate w;
    w.show();
    return a.exec();
}
