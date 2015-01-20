#include "GeneratorWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GeneratorWindow w;

    w.show();
    return a.exec();
}
