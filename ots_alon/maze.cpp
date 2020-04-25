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

    painter->drawRect(exitX+2,exitY+2,height-4,height-4);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Maze::genWay(int start,int exit)
{
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

Direction Maze::getDir(int start,int end)
 {
    if((start - end) == -1)
        return Right;
    if((start - end) == 1)
        return Left;
    if((start - end) == -size)
        return Down;
    if((start - end) == size)
        return Up;
 }

int Maze::findFree(int x,int y,bool** matx)
{
    srand(clock()*x*y);

    QList<int> list;

    if(x - 1 >= 0)
    {
       if(matx[y][x-1])
       {
        list.push_back(y*size + x - 1);
       }
    }

    if(x + 1 < size)
    {
        if(matx[y][x+1])
        {
         list.push_back(y*size + x + 1);
        }
    }

    if(y - 1 >= 0)
    {
        if(matx[y-1][x])
        {
             list.push_back((y-1)*size + x);
        }
    }

    if(y + 1 < size)
    {
        if(matx[y+1][x])
        {
            list.push_back((y+1)*size + x);
        }
    }

    if(list.empty())
    {
        return -1;
    }

    int r = rand()%list.size();

    return list[r];

}

void Maze::genMaze(int start)
{
     bool **matx = new bool*[size];
    int next;

    for(int i = 0;i < size; ++i)
    {
        matx[i] = new bool[size];

        for(int j = 0; j<size;++j )
        {
            matx[i][j] = true;
        }
     }

    while (true)
    {
        int startX =start % size;
        int startY =start / size;

        matx[startY][startX] = false;
        next = findFree(startX,startY,matx);
        if(next == -1)
        {
            start = getAsFree(matx);
            if(start == -1)
            {
                return;
            }
            continue;
        }
        breakWall(start,getDir(start,next));
        start = next;
    }
}

void Maze::breakWall(int ind, Direction dir)
{
    int startX = ind % size;
    int startY=  ind / size;

    switch (dir) {
    case Up:
        this->lab[startY][startX].setUp(false);
        this->lab[startY-1][startX].setDown(false);
        break;
    case Down:
        this->lab[startY][startX].setDown(false);
        this->lab[startY+1][startX].setUp(false);
        break;
    case Left:
        this->lab[startY][startX].setLeft(false);
        this->lab[startY][startX-1].setRight(false);
        break;
    case Right:
        this->lab[startY][startX].setRight(false);
        this->lab[startY][startX+1].setLeft(false);
        break;
    }
}

 int Maze::getAsFree(bool** matx)
 {
    for(int i = 0;i < size;++i)
    {
        for(int j = 0;j < size;++j)
        {
            if(!matx[i][j])
            {
                if(findFree(j,i,matx) != -1)
                {
                    return i*size + j;
                }
            }
        }
    }
    return -1;
 }
