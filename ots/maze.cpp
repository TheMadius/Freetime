#include "maze.h"

Maze::Maze(int size,int height,int exit,QObject *parent ):
    QObject(parent), QGraphicsItem()
{
    this->size = size;
    this->height = height;
    this->exit = exit;

    this->lab = new Walls*[size];

    for(int i = 0; i < size; ++i)
    {
        this->lab[i] = new Walls[size];
    }
}

QRectF Maze::boundingRect() const
{
    return QRectF(0,0,size*this->height,size*this->height);
}

bool Maze::canIn(int in,Direction direct)
{
    if(in >= size*size ||in < 0)
        return false;

    switch (direct) {
    case Up:
        return !(this->lab[in/size][in%size].moveUp());
    case Down:
        return !(this->lab[in/size][in%size].moveDown());
    case Left:
        return !(this->lab[in/size][in%size].moveLeft());
    case Right:
        return !(this->lab[in/size][in%size].moveRight());
    }
}

void Maze::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(Qt::black);

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
        {
            if(this->lab[i][j].moveUp())
            {
                painter->drawLine(j*this->height,i*this->height,(j+1)*this->height,i*this->height);
            }
            if(this->lab[i][j].moveDown())
            {
                painter->drawLine(j*this->height,(i+1)*this->height,(j+1)*this->height,(i+1)*this->height);
            }
            if(this->lab[i][j].moveRight())
            {
               painter->drawLine((j+1)*this->height,(i)*this->height,(j+1)*this->height,(i+1)*this->height);
            }
            if(this->lab[i][j].moveLeft())
            {
               painter->drawLine((j)*this->height,(i)*this->height,(j)*this->height,(i+1)*this->height);
            }
        }

    int exitX = (exit%size)*height;
    int exitY = (exit/size)*height;

    painter->setBrush(Qt::red);

    painter->drawRect(exitX,exitY,height,height);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Maze::genWay(int start,int exit){

    int startX = start%size;
    int startY= start/size;
    int exitX= exit%size;
    int exitY= exit/size;

    int MinX = (startX>exitX)?exitX:startX;
    int MinY= (startY>exitY)?exitY:startY;
    int MaxX= (startX<exitX)?exitX:startX;
    int MaxY= (startY<exitY)?exitY:startY;

    for(int i = MinX; i < MaxX;i++)
    {
        this->lab[startY][i].setRight(false);
        this->lab[startY][i+1].setLeft(false);
    }

    for(int i = MinY; i < MaxY;i++)
    {
        this->lab[i+1][exitX].setUp(false);
        this->lab[i][exitX].setDown(false);
    }

}
