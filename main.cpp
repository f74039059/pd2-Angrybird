//#include "mainwindow.h"
#include "firstwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstWindow *first = new FirstWindow;
   //MainWindow w;
    //w.show();
    return a.exec();
}
