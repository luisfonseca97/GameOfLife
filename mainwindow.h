#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <iostream>

#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

using namespace std;

// global variables:
const int WIDTH = 660;
const int HEIGHT = 400;
const int SIZE = 10;
const int NCOL = HEIGHT/SIZE; //SIZE must be a divisor of HEIGHT

const QColor aliveCol = QColor(200,200,200);
const QColor deadCol = QColor(50,50,50);
const QColor rectCol = QColor(100,100,100);

class Cell {
public:
    int x;
    int y;
    bool alive;
    vector<pair<int,int>> neigh;

    Cell(int a = 0, int b = 0) {
        x = a;
        y = b;
        alive = false;
        vector<pair<int,int>> neigh;
    }

    void draw(QGraphicsScene *scene){
        QGraphicsRectItem *cell1 = new QGraphicsRectItem(this->x*SIZE,this->y*SIZE,SIZE,SIZE);
        if (this->alive) {
            cell1->setBrush(QBrush(aliveCol));
        }
        else {
            cell1->setBrush(QBrush(deadCol));
        }
        scene->addItem(cell1);
    }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateScene(Cell mat[NCOL][NCOL], QGraphicsScene *scene);

    int countAlive(Cell c, Cell mat[NCOL][NCOL]);

    void step(Cell mat[NCOL][NCOL]);

    void clearMatrix (Cell mat[NCOL][NCOL]);

    void buildGliders(Cell mat[NCOL][NCOL], int butId);

    void buildOscilators(Cell mat[NCOL][NCOL], int butId);

    void buildGun(Cell mat[NCOL][NCOL]);

    void buildRnd(Cell mat[NCOL][NCOL]);

    void showMousePos(QEvent *event);

private:
    Ui::MainWindow *ui;
    Cell mat[NCOL][NCOL] = {};
};
#endif // MAINWINDOW_H
