#ifndef WALLS_H
#define WALLS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPolygon>
#include <QTimer>

class Walls
{
public:
    Walls(bool up = true,bool down= true,bool right= true,bool left= true);
    bool moveUp();
    bool moveDown();
    bool moveRight();
    bool moveLeft();

    void setUp(bool flag);
    void setDown(bool flag);
    void setRight(bool flag);
    void setLeft(bool flag);
private:
    bool m_up;
    bool m_down;
    bool m_left;
    bool m_right;
};


#endif // WALLS_H
