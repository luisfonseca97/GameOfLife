#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QRandomGenerator>
#include <algorithm>
#include <QDebug>
#include <QMouseEvent>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(0, 0, WIDTH, HEIGHT+70);

    //background:
    scene->setBackgroundBrush(Qt::gray);

    //build the rectangles and the board:
    QGraphicsRectItem* glRect = new QGraphicsRectItem(410,70,245,130);
    glRect->setBrush(QBrush(rectCol));
    QGraphicsRectItem* osRect = new QGraphicsRectItem(410,200,245,130);
    osRect->setBrush(QBrush(rectCol));
    scene->addItem(glRect);
    scene->addItem(osRect);
    QGraphicsTextItem *glText = new QGraphicsTextItem("Gliders");
    glText->setPos(415,75);
    glText->setDefaultTextColor(textColor);
    scene->addItem(glText);
    QGraphicsTextItem *osText = new QGraphicsTextItem("Oscilators");
    osText->setPos(415,205);
    osText->setDefaultTextColor(textColor);
    scene->addItem(osText);

    for (int i = 0; i <= NCOL; i++)
    {
          scene->addLine(SIZE*i,0,SIZE*i,HEIGHT);
          scene->addLine(0,SIZE*i,HEIGHT,SIZE*i);
    }

    //adding the buttons: (maybe don't hard-code the dimensions of the rects)
    QPushButton *button1;
    button1 = new QPushButton();
    button1->setGeometry(QRect(420, 20, 100, 30));
    button1->setText("Start / Stop");
    scene->addWidget(button1);

    QPushButton *clearButton;
    clearButton = new QPushButton();
    clearButton->setGeometry(QRect(545, 20, 100, 30));
    clearButton->setText("Clear Board");
    scene->addWidget(clearButton);

    QPushButton *invButton; //this button covers the matrix and should be seen when running the app
    invButton = new QPushButton();
    invButton->setGeometry(QRect(0,0,HEIGHT,HEIGHT));
    scene->addWidget(invButton);

    QPushButton *gl1Button;
    gl1Button = new QPushButton();
    gl1Button->setGeometry(QRect(420, 110, 100, 30));
    gl1Button->setText("Glider");
    scene->addWidget(gl1Button);

    QPushButton *gl2Button;
    gl2Button = new QPushButton();
    gl2Button->setGeometry(QRect(545, 110, 100, 30));
    gl2Button->setText("Double Glider");
    scene->addWidget(gl2Button);

    QPushButton *gl3Button;
    gl3Button = new QPushButton();
    gl3Button->setGeometry(QRect(420, 160, 100, 30));
    gl3Button->setText("Spaceship");
    scene->addWidget(gl3Button);

    QPushButton *gl4Button;
    gl4Button = new QPushButton();
    gl4Button->setGeometry(QRect(545, 160, 100, 30));
    gl4Button->setText("Hammer Head");
    scene->addWidget(gl4Button);

    QPushButton *os1Button;
    os1Button = new QPushButton();
    os1Button->setGeometry(QRect(420, 240, 100, 30));
    os1Button->setText("Clover Leaf");
    scene->addWidget(os1Button);

    QPushButton *os2Button;
    os2Button = new QPushButton();
    os2Button->setGeometry(QRect(545, 240, 100, 30));
    os2Button->setText("Kok's Galaxy");
    scene->addWidget(os2Button);

    QPushButton *os3Button;
    os3Button = new QPushButton();
    os3Button->setGeometry(QRect(420, 290, 100, 30));
    os3Button->setText("Ekie's Fumarole");
    scene->addWidget(os3Button);

    QPushButton *os4Button;
    os4Button = new QPushButton();
    os4Button->setGeometry(QRect(545, 290, 100, 30));
    os4Button->setText("Tumbler");
    scene->addWidget(os4Button);

    QPushButton *glGunButton;
    glGunButton = new QPushButton();
    glGunButton->setGeometry(QRect(420, 350, 100, 30));
    glGunButton->setText("Glider Gun");
    scene->addWidget(glGunButton);

    QPushButton *rndButton;
    rndButton = new QPushButton();
    rndButton->setGeometry(QRect(545, 350, 100, 30));
    rndButton->setText("Random Layout");
    scene->addWidget(rndButton);

    //adding sliders:
    //reproduction slider
    QSlider *repSlider;
    repSlider = new QSlider(Qt::Horizontal);
    repSlider->setGeometry(20,440,100,20);
    repSlider->setRange(0,8);
    repSlider->setValue(3);
    scene->addWidget(repSlider);

    QGraphicsTextItem *sl1Text = new QGraphicsTextItem("Reprodution:");
    sl1Text->setPos(20,420);
    sl1Text->setDefaultTextColor(textColor);
    scene->addItem(sl1Text);

    //underpopulation slider
    QSlider *underPopSlider;
    underPopSlider = new QSlider(Qt::Horizontal);
    underPopSlider->setGeometry(140,440,100,20);
    underPopSlider->setRange(0,8);
    underPopSlider->setValue(1);
    scene->addWidget(underPopSlider);

    QGraphicsTextItem *sl2Text = new QGraphicsTextItem("Underpopulation:");
    sl2Text->setPos(140,420);
    sl2Text->setDefaultTextColor(textColor);
    scene->addItem(sl2Text);

    //overpopulation slider -> play goes to true when I uncomment
    /**QSlider *overPopSlider;
    overPopSlider = new QSlider(Qt::Horizontal);
    overPopSlider->setGeometry(260,440,100,20);
    overPopSlider->setRange(0,8);
    overPopSlider->setValue(4);
    scene->addWidget(overPopSlider);

    QGraphicsTextItem *sl3Text = new QGraphicsTextItem("Overpopulation:");
    sl3Text->setPos(260,420);
    sl3Text->setDefaultTextColor(textColor);
    scene->addItem(sl3Text);**/

    //building the cells matrix:
    for (int i = 0; i<NCOL; i++) {
        for (int j = 0; j<NCOL; j++) {
            mat[i][j] = Cell(i,j);
        }
    }

    //adding the neighbours:
    for (int i = 0; i<NCOL; i++) {
        for (int j = 0; j<NCOL; j++) {
            mat[i][j].neigh.push_back(make_pair((i-1+NCOL)%NCOL,(j-1+NCOL)%NCOL));
            mat[i][j].neigh.push_back(make_pair(i,(j-1+NCOL)%NCOL));
            mat[i][j].neigh.push_back(make_pair((i+1)%NCOL,(j-1+NCOL)%NCOL));
            mat[i][j].neigh.push_back(make_pair((i-1+NCOL)%NCOL,j));
            mat[i][j].neigh.push_back(make_pair((i+1)%NCOL,j));
            mat[i][j].neigh.push_back(make_pair((i-1+NCOL)%NCOL,(j+1)%NCOL));
            mat[i][j].neigh.push_back(make_pair(i,(j+1)%NCOL));
            mat[i][j].neigh.push_back(make_pair((i+1)%NCOL,(j+1)%NCOL));
        }
    }

    //have an initial layout for debugging
    mat[1][4].alive = true;
    mat[2][4].alive = true;
    mat[3][4].alive = true;

    bool play = false;

    updateScene(mat, scene);

    //make scene
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(670, 480);
    view->show();

    QTimer *_timer = new QTimer; //for the animation

    //connect the buttons:
    connect(clearButton, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            updateScene(mat, scene);
        }
    });

    connect(button1, &QPushButton::clicked, this, [&play]()
    {
        play = !play;
    }
    );

    connect(gl1Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildGliders(mat, 0);
            updateScene(mat, scene);
        }
    });

    connect(gl2Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildGliders(mat, 1);
            updateScene(mat, scene);
        }
    });

    connect(gl3Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildGliders(mat, 2);
            updateScene(mat, scene);
        }
    });

    //play goes to true when uncommenting this block, don't know why
    /**connect(gl4Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildGliders(mat, 3);
            updateScene(mat, scene);
        }
    });**/

    connect(os1Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildOscilators(mat, 0);
            updateScene(mat, scene);
        }
    });

    connect(os2Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildOscilators(mat, 1);
            updateScene(mat, scene);
        }
    });

    connect(os3Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildOscilators(mat, 2);
            updateScene(mat, scene);
        }
    });

    connect(os4Button, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            //buildOscilators(mat, 3);
            buildGun(mat);
            updateScene(mat, scene);
        }
    });

    //play goes to true when uncommenting the block
    /**connect(glGunButton, &QPushButton::clicked, scene, [this, &play, scene](){
        if (!play) {
            clearMatrix(mat);
            buildGun(mat);
            updateScene(mat, scene);
        }
    });**/

    connect(rndButton, &QPushButton::clicked, scene, [this, &play, scene](){
        if(!play) {
            clearMatrix(mat);
            buildRnd(mat);
            updateScene(mat,scene);
        }
    });

    connect(_timer, &QTimer::timeout, scene, [this, &play, scene]()
    {
        //The following line came stack exchange. Kept it for future reference on generating random numbers
        //mat[QRandomGenerator::global()->bounded(NCOL)][QRandomGenerator::global()->bounded(NCOL)].alive = true;
        if (play) {
            step(mat);
            updateScene(mat, scene);
        }
    }
    );

    _timer->start(200);

    //Invert the stage of a cell when clicking on it
    connect(invButton, &QPushButton::clicked, scene, [this, view, &play, scene](){
        if (!play) {
            QPoint pos2 = view->pos();
            QPoint pos = QCursor::pos();
            QPoint coord;
            coord.setX((pos.x()-pos2.x()-5)/SIZE);
            coord.setY((pos.y()-pos2.y()-35)/SIZE);
            mat[coord.x()][coord.y()].alive = !mat[coord.x()][coord.y()].alive;
            updateScene(mat, scene);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScene(Cell mat[NCOL][NCOL], QGraphicsScene *scene)
{
    for (int i = 0; i<NCOL; i++) {
        for (int j = 0; j<NCOL; j++) {
            mat[i][j].draw(scene);
        }
    }
}

int MainWindow::countAlive(Cell c, Cell mat[NCOL][NCOL]) //auxiliary function for the step function
{
    int r = 0;
    for (pair<int,int> p : c.neigh) {
        if (mat[get<0>(p)][get<1>(p)].alive) {r++;}
    }
    return r;
}

void MainWindow::step(Cell mat[NCOL][NCOL]) //animation step
{
    int aliveCount;
    vector<pair<int,int>> living = {};
    for (int i = 0; i < NCOL; i++) {
        for (int j = 0; j < NCOL; j++) {
            aliveCount = countAlive(mat[i][j],mat);
            //rules:
            if(!mat[i][j].alive){
                if(aliveCount == reprNumber) {
                    living.push_back(make_pair(i,j));
                }
            }
            else if (aliveCount > maxUnder && aliveCount < minOver) {
                living.push_back(make_pair(i,j));
            }
        }
    }
    for (int i = 0; i < NCOL; i++) {
        for (int j = 0; j < NCOL; j++) {
            mat[i][j].alive = std::find(living.begin(), living.end(), make_pair(i,j)) != living.end();
        }
    }
}

void MainWindow::clearMatrix(Cell mat[NCOL][NCOL])
{
    for (int i = 0; i < NCOL; i++) {
        for(int j = 0; j < NCOL; j++) {
            mat[i][j].alive = false;
        }
    }
}

void MainWindow::buildGliders(Cell mat[NCOL][NCOL], int butId)
{
    int c = NCOL / 2; //center of the board
    vector<pair<int,int>> live = {}; //list of cells to make alive
    switch(butId) {
    case 0: //simple glider
    {
        live = {{c,c},{c,c-1},{c,c-2},{c-1,c},{c-2,c-1}};
        break;
    }
    case 1: //double glider
    {
        live = {{c-10,c-10},{c-10,c-11},{c-10,c-12},{c-11,c-10},{c-12,c-11},{c+9,c-10},{c+9,c-11},{c+9,c-12},{c+10,c-10},{c+11,c-11}};
        break;
    }
    case 2: //spaceship
    {
        live = {{c-1,c-1},{c,c-1},{c+1,c-1},{c+2,c-1},{c-2,c},{c+2,c},{c+2,c+1},{c-2,c+2},{c+1,c+2}};
        break;
    }
    case 3: //hammerhead (built by line)
    {
        int y;
        for(int j : {1,-1}){
            y = c+7*j+max(0,j);
            for(int k : {-8, -7, -6, -5, -4}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-8, -3, 5, 6}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-8, 4, 5, 7, 8, 9}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-7, 3, 4, 6, 7, 8, 9}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-5, -4, 0, 1, 3, 4, 7, 8}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-3, 2, 5}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-2, 0, 2, 4}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            live.push_back(make_pair(c-1,y));
        }
        break;
    }
    default:
        break;
    }
    for (pair p : live) {
        mat[p.first][p.second].alive = true;
    }
}

void MainWindow::buildOscilators(Cell mat[NCOL][NCOL], int butId)
{
    int c = NCOL / 2;
    vector<pair<int,int>> live = {};
    switch(butId) {
    case 0: //clover leaf (I can probably make this a little nicer to read)
    {
        for (int k = -1; k < 2; k+=2) {
            live.push_back(make_pair(c-1, c+k*5));
            live.push_back(make_pair(c+1, c+k*5));
            live.push_back(make_pair(c-3, c+k*4));
            live.push_back(make_pair(c-2, c+k*4));
            live.push_back(make_pair(c-1, c+k*4));
            live.push_back(make_pair(c+1, c+k*4));
            live.push_back(make_pair(c+2, c+k*4));
            live.push_back(make_pair(c+3, c+k*4));
            live.push_back(make_pair(c-4, c+k*3));
            live.push_back(make_pair(c, c+k*3));
            live.push_back(make_pair(c+4, c+k*3));
            live.push_back(make_pair(c-4, c+k*2));
            live.push_back(make_pair(c-2, c+k*2));
            live.push_back(make_pair(c+2, c+k*2));
            live.push_back(make_pair(c+4, c+k*2));
            live.push_back(make_pair(c-3, c+k*1));
            live.push_back(make_pair(c-2, c+k*1));
            live.push_back(make_pair(c, c+k*1));
            live.push_back(make_pair(c+2, c+k*1));
            live.push_back(make_pair(c+3, c+k*1));
        }
        break;
    }
    case 1: //Kok's Galaxy (built by block)
    {
        for (int i = 0; i < 6; i++) {
            for (int j : {0,1}) {
                mat[c-4+i][c-4+j].alive = true;
                mat[c+4-i][c+4-j].alive = true;
                mat[c+4-j][c-4+i].alive = true;
                mat[c-4+j][c+4-i].alive = true;
            }
        }
        break;
    }
    case 2: //Ekie's Fumarole
    {
        live = {{c+2, c-2},{c+2, c-3},{c+2, c-4}};
        int xc = c - 2;
        int yc = c + 3;
        int y;
        int x;
        for(int j : {1,-1}){
            y = xc+3*j+max(0,j);
            for(int k : {-7, -6}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-7, -4, -3}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-6, -5, -3, -2}) {
                live.push_back(make_pair(c+k,y));
            }
            y -= j;
            for(int k : {-3, -2}) {
                live.push_back(make_pair(c+k,y));
            }
        }
        for(int j : {1,-1}){
            x = yc+3*j+max(0,j);
            for(int k : {5,6}) {
                live.push_back(make_pair(x,c+k));
            }
            x -= j;
            for(int k : {1,2,3,6}) {
                live.push_back(make_pair(x,c+k));
            }
            x -= j;
            for(int k : {4,5}) {
                live.push_back(make_pair(x,c+k));
            }
            x -= j;
            live.push_back(make_pair(x,c));
        }
        break;
    }
    case 3: // Tumbler
    {
        for(int j : {-1,1}) {
            int x = 3;
            for (int k : {-2,-1}) {
                live.push_back((make_pair(c+x*j,c+k)));
            }
            x -= 1;
            for (int k : {-3,-2, 1, 2}) {
                live.push_back((make_pair(c+x*j,c+k)));
            }
            x -= 1;
            for (int k : {-1, 0, 1}) {
                live.push_back((make_pair(c+x*j,c+k)));
            }
        }
        break;
    }
    default:
        break;
    }
    for (pair p : live) {
        mat[p.first][p.second].alive = true;
    }
}

void MainWindow::buildGun(Cell mat[NCOL][NCOL])
{
    vector<pair<int,int>> live = {{1,4},{2,4},{1,5},{2,5},{17,4},{18,4},{17,5},{18,5},{17,6},{18,6},{35,2},{36,2},{35,3},{36,3}};
    int y1 = 3;
    int y2 = 5;
    for (int i : {-1, 1}) {
        int h = 3;
        live.push_back(make_pair(24, y1 + h*i));
        live.push_back(make_pair(13, y2 + h*i));
        h -= 1;
        for (int k : {22, 24}) {
            live.push_back(make_pair(k, y1 + h*i));
        }
        for (int k : {12, 13}) {
            live.push_back(make_pair(k, y2 + h*i));
        }
        h -= 1;
        for (int k : {21, 23}) {
            live.push_back(make_pair(k, y1 + h*i));
        }
        for (int k : {11, 12}) {
            live.push_back(make_pair(k, y2 + h*i));
        }
        h -= 1;
        for (int k : {20, 23}) {
            live.push_back(make_pair(k, y1 + h*i));
        }
        for (int k : {10, 11, 12}) {
            live.push_back(make_pair(k, y2 + h*i));
        }
    }
    for (pair p: live) {
        mat[p.first][p.second].alive = true;
    }
}

void MainWindow::buildRnd(Cell mat[NCOL][NCOL])
{
    for (int i = 0; i < NCOL; i++) {
        for (int j = 0; j < NCOL; j++) {
            int r = QRandomGenerator::global()->bounded(100);
            mat[i][j].alive = r < 25;
        }
    }
}

void MainWindow::showMousePos(QEvent *event)
//I have this function for debugging only
{
    switch (event->type()) {
        case QEvent::MouseButtonPress: {
            QMouseEvent *me = static_cast<QMouseEvent *>(event); //me: mouse event (must be mouse button press)
            QPointF mappedPos = me -> scenePosition();
            qDebug() << mappedPos;
        }
        default:
            break;
    }
}

