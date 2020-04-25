#ifndef MAZE_H
#define MAZE_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPolygon>
#include <QTimer>

#include "walls.h"
enum Direction {Up,Down,Left,Right};

class Maze : public QObject, public QGraphicsItem
{
public:
    bool canIn(int in,Direction direct);
    Maze(int size,int height,int exit,QObject *parent = nullptr);
    void genWay(int start,int exit);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    Walls **lab;
    int height;
    int size;
    int exit;
};

#endif // MAZE_H
