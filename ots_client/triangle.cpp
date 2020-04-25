#include "triangle.h"
#include <math.h>

Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    step = 40;
    setRotation(0);      // Устанавливаем исходный разворот треугольника
    target = QPointF(0,0);  // Устанавливаем изначальное положение курсора
}

Triangle::~Triangle()
{

}

QRectF Triangle::boundingRect() const
{
    return QRectF(-20,-20,40,40);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(Qt::blue);
    painter->drawEllipse(-18,-18,36,36);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
