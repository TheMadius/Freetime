#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
       ui->setupUi(this);

       client = new QTcpSocket(this);

       connect(client,SIGNAL(readyRead()),this,SLOT(sockReady()));
       connect(client,SIGNAL(disconnected()),this,SLOT(sockDisc()));

       while (!client->waitForConnected(500))
       {
           client->connectToHost("127.0.0.1",5555);
       }

       step = 40;
       sizeMaze = 20;
       this->resize(sizeMaze*step,sizeMaze*step + 30);
       this->setFixedSize(sizeMaze*step,sizeMaze*step + 30);

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


    client->waitForReadyRead(1000);

    QString  str (Data.data());

    int start = str.toInt();

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
    int dire;

    if(GetAsyncKeyState('A'))
    { 
        dire = 2;
    }
    else
    if(GetAsyncKeyState('D'))
    {
        dire = 3;
    }
    else
    if(GetAsyncKeyState('W'))
    {
        dire = 0;
    }
    else
    if(GetAsyncKeyState('S'))
    {
        dire = 2;
    }
    else
        return;

    this->client->write( QString::number(dire).toStdString().data());

    while(!client->waitForReadyRead(10));

    Data = client->readAll();

    int flag = QString( Data.data()).toInt();

    if(flag == 1)
    {
        switch (dire) {
        case 0:
            lab->breakWall(index,Up);
            triangle->setY(triangle->y() - step);
            --y;
            index-= sizeMaze;
            break;
        case 1:
            lab->breakWall(index,Down);
            triangle->setY(triangle->y() + step);
            ++y;
            index+= sizeMaze;
            break;
        case 2:
            lab->breakWall(index,Left);
            triangle->setX(triangle->x() - step);
            --x;
            index--;
            break;
        case 3:
            lab->breakWall(index,Right);
            triangle->setX(triangle->x() + step);
             ++x;
            index++;
            break;
        }
    }

    this->scene->update(0,0,sizeMaze*step,sizeMaze*step);

}

void MainWindow::sockDisc()
{
    client->deleteLater();
}

void MainWindow::sockReady()
{
        client->waitForReadyRead(500);
        Data = client->readAll();
        qDebug()<<Data;
}
