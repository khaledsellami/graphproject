  //-----------------------------------------//
 //work of Khaled Sellami and Ilyes Yahyaoui//
//-----------------------------------------//

#include <iostream>
#include <QApplication>
#include<QtCore>
#include "mainwindow.h"
using namespace std;

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    mainwindow window;
    window.show();
    return app.exec();
}
