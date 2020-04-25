#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <iostream>
#include <QMessageBox>
#include <triangle.h>
#include <customscene.h>
#include "maze.h"

#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void slotGameTimer();
    void startGame();
    ~MainWindow();

public slots:
    void sockReady();
    void sockDisc();

private:
    Ui::MainWindow *ui;
    CustomScene *scene = nullptr;
    Triangle *triangle = nullptr;
    int index;
    int step;
    Maze* lab = nullptr;
    int x;
    int y;
    int exit;
    int sizeMaze;
    QMetaObject::Connection Conn;

    QTcpSocket* client;
    QByteArray Data;
};
#endif // MAINWINDOW_H
