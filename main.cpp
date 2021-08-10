#include "mainwindow.h"
#include <vector>
#include <iostream>

#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    MainWindow w;
    w.show();

    return prog.exec();
}
