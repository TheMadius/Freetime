#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
       server = new myserver();
       server->startServer();

       while(!server->waitForNewConnection(500));

       step = 40;
       sizeMaze = 20;
       this->resize(sizeMaze*step,sizeMaze*step + 30);
       this->setFixedSize(sizeMaze*step,sizeMaze*step + 30);
       ui->setupUi(this);
       ui->graphicsView->resize(sizeMaze*step,sizeMaze*step);

       scene   = new CustomScene();    // Инициализируем кастомизированную сцену

       ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
       ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
       ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
       ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

       scene->setSceneRect(0,0,sizeMaze*step,sizeMaze*step);   // Устанавливаем размеры графической сцены

       startGame();

   }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    srand(clock());
    exit = sizeMaze*(sizeMaze/2) +rand()%(sizeMaze*(sizeMaze/2));
    int start = rand()%(sizeMaze*(sizeMaze/2));

    server->socket->write(QString::number(start).toStdString().data());

    if(lab != nullptr)
        delete lab;
    if(triangle != nullptr)
        delete triangle;

    disconnect(Conn);

    lab = new Maze(sizeMaze,step,exit);
    lab->setPos(0,0);

    index = start;
    x = start%sizeMaze;
    y = start/sizeMaze;

    lab->genMaze(start);

    triangle = new Triangle();
    triangle->setPos( x*step + 20, y*step + 20);
    scene->addItem(triangle);
    scene->addItem(lab);

    QTimer *gameTimer = new QTimer();
    Conn = connect(gameTimer, &QTimer::timeout, this, &MainWindow::slotGameTimer);
    gameTimer->start(100);
}


void MainWindow::slotGameTimer()
{
   if(!server->socket->waitForReadyRead(100))
       return;

    server->Data = server->socket->readAll();

    int re = QString(server->Data.data()).toInt();

    cout << re << endl;

    switch (re) {
    case 0:
        if(lab->canIn(index,Up))
        {
            server->socket->write(  QString::number((int)lab->canIn(index,Up)).toStdString().data());
            triangle->setY(triangle->y() - step);
            --y;
            index-= sizeMaze;
        }
        else
        {
            server->socket->write(  QString::number((int)lab->canIn(index,Up)).toStdString().data());
        }
        break;
    case 1:
        if(lab->canIn(index,Down))
        {
            server->socket->write(  QString::number((int)lab->canIn(index,Up)).toStdString().data());
            triangle->setY(triangle->y() + step);
            ++y;
            index+= sizeMaze;
        }
        else
        {
            server->socket->write(QString::number((int)lab->canIn(index,Up)).toStdString().data());
        }
        break;
    case 2:
        if(lab->canIn(index,Left))
        {
            server->socket->write(  QString::number((int)lab->canIn(index,Up)).toStdString().data());
            triangle->setX(triangle->x() - step);
            --x;
            index--;
        }
        else
        {
            server->socket->write(  QString::number((int)lab->canIn(index,Up)).toStdString().data());
        }
        break;
    case 3:
        if(lab->canIn(index,Right))
        {
             server->socket->write(  QString::number((int)lab->canIn(index,Up)).toStdString().data());
            triangle->setX(triangle->x() + step);
             ++x;
            index++;
        }
        else
        {
            server->socket->write(  QString::number((int)lab->canIn(index,Up)).toStdString().data());
        }
        break;
    }

/*

    if(GetAsyncKeyState('A'))
    { 
        if(lab->canIn(index,Left))
        {
            triangle->setX(triangle->x() - step);
            --x;
            index--;
        }
    }
    else
    if(GetAsyncKeyState('D'))
    {
        if(lab->canIn(index,Right))
        {
            triangle->setX(triangle->x() + step);
             ++x;
            index++;
        }
    }
    else
    if(GetAsyncKeyState('W'))
    {
        if(lab->canIn(index,Up))
        {
            triangle->setY(triangle->y() - step);
            --y;
            index-= sizeMaze;
        }
    }
    else
    if(GetAsyncKeyState('S'))
    {
        if(lab->canIn(index,Down))
        {
            triangle->setY(triangle->y() + step);
            ++y;
            index+= sizeMaze;
        }
     }
     */
     if(index == this->exit)
     {
        startGame();
     }

}
