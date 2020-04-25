#ifndef MAZE_H
#define MAZE_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <QList>
#include <iostream>
#include "walls.h"
enum Direction {Up,Down,Left,Right};

class Maze : public QObject, public QGraphicsItem
{
public:
    bool canIn(int in,Direction direct);
    Maze(int size,int height,int exit,QObject *parent = nullptr);
    void genWay(int start,int exit);
    void genMaze(int start);
    void breakWall(int ind, Direction dir);
    Direction getDir(int start,int end);

private:
    int findFree(int x,int y,bool** matx);
    int getAsFree(bool** matx);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    Walls **lab;
    int height;
    int size;
    int exit;
};

#endif // MAZE_H
