#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    x = 0.0;
    y = 0.0;
    tx = 0.0;
    ty = 0.0;

    radiusx = 0.0;
    radiusy = 0.0;
}

void Painter::paintPosition(const qreal _x, const qreal _y, const qreal _tx, const qreal _ty, const qreal _r){
    x = _x*width()/2;
    y = _y*height()/2;
    tx = _tx*width()/2;
    ty = _ty*height()/2;
    radiusx = _r*width()/2;
    radiusy = _r*height()/2;

    repaint();
}

void Painter::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    QPen objectPen(Qt::green);
    objectPen.setWidth(2);

    QPen targetPen(Qt::red);
    targetPen.setWidth(2);

    painter.drawRect(0,0,width(),height());

    QTransform matrix;
    matrix.translate(width()/2, height()/2);
    matrix.scale(1, -1);

    painter.setWorldTransform(matrix);

    painter.setPen(objectPen);
    painter.drawEllipse((int)x, (int)y, (int)radiusx, (int)radiusy);

    painter.setPen(targetPen);
    painter.drawEllipse((int)tx, (int)ty, 2, 2);




}
