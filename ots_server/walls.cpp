#include "walls.h"

Walls:: Walls(bool up,bool down,bool right,bool left)
{
    m_up = up;
    m_down = down;
    m_left = left;
    m_right = right;
}

bool Walls:: moveUp()
{
    return  m_up;
}
bool Walls:: moveDown()
{
    return  m_down;
}
bool Walls:: moveRight()
{
    return  m_right;
}
bool Walls:: moveLeft()
{
    return  m_left;
}
void Walls::setUp(bool flag)
{
  m_up = flag;
}
void Walls::setDown(bool flag)
{
  m_down= flag;
}
void Walls::setRight(bool flag)
{
  m_right= flag;
}
void Walls::setLeft(bool flag)
{
  m_left = flag;
}
