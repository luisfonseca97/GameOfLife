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
#include <QSlider>


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
const int reprNumber = 3; //number of neighbours for reproduction
const int maxUnder = 1; //maximum number of neighbours for underpopulation
const int minOver = 4; //minimum number of neighbours for overpopulation

const QColor aliveCol = QColor(200,200,200);
const QColor deadCol = QColor(50,50,50);
const QColor rectCol = QColor(100,100,100);
const QColor textColor = Qt::white;

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
    //Rules:
    int repRule = 3; //reproduction rule
    int underRule = 1; //underpopulation rule
    int overRule = 4; //overpopulation rule

    bool play = false;

    QGraphicsScene *scene = new QGraphicsScene(0, 0, WIDTH, HEIGHT+70);

    QGraphicsView *view = new QGraphicsView(scene);

    QSlider *repSlider;
    QSlider *underPopSlider;
    QSlider *overPopSlider;

    QGraphicsTextItem *sl1Text = new QGraphicsTextItem("Reprodution:");
    QGraphicsTextItem *sl2Text = new QGraphicsTextItem("Underpopulation:");
    QGraphicsTextItem *sl3Text = new QGraphicsTextItem("Overpopulation:");

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateScene(Cell mat[NCOL][NCOL], QGraphicsScene *scene);

    int countAlive(Cell c, Cell mat[NCOL][NCOL]);

    void clearMatrix (Cell mat[NCOL][NCOL]);

    void buildGliders(Cell mat[NCOL][NCOL], int butId);

    void buildOscilators(Cell mat[NCOL][NCOL], int butId);

    void buildGun(Cell mat[NCOL][NCOL]);

    void buildRnd(Cell mat[NCOL][NCOL]);

    void showMousePos(QEvent *event);

private:
    Ui::MainWindow *ui;
    Cell mat[NCOL][NCOL] = {};

public slots:
    void updateRules();
    void step();
    void switchPlay();
    void clearButtonSlot();

    void gl1Slot();
    void gl2Slot();
    void gl3Slot();
    void gl4Slot();

    void os1Slot();
    void os2Slot();
    void os3Slot();
    void os4Slot();

    void glGunSlot();
    void rndSlot();

    void invButSlot();

};
#endif // MAINWINDOW_H
