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
    x = 0.5*_x*(qreal)width();
    y = 0.5*_y*(qreal)height();
    tx = 0.5*_tx*(qreal)width();
    ty = 0.5*_ty*(qreal)height();
    radiusx = 0.5*_r*(qreal)width();
    radiusy = 0.5*_r*(qreal)height();

    repaint();
}

void Painter::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    QPen objectPen(Qt::green);
    objectPen.setWidth(2);

    QPen targetPen(Qt::red);
    targetPen.setWidth(2);

    painter.drawRect(0,0,(width()-1),(height()-1));

    QTransform matrix;
    matrix.translate(width()/2, height()/2);
    matrix.scale(1, -1);

    painter.setWorldTransform(matrix);

    painter.setPen(objectPen);
    painter.drawEllipse(x, y, radiusx, radiusy);

    painter.setPen(targetPen);
    painter.drawEllipse(tx, ty, 2, 2);
}
