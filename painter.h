#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QPainter>
#include <QMatrix>

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = 0);

signals:

public slots:
    void paintPosition(const qreal _x, const qreal _y,
                       const qreal _tx, const qreal _ty,
                       const qreal _r);

protected:
    void paintEvent(QPaintEvent *e);

    qreal x;
    qreal y;
    qreal tx;
    qreal ty;
    qreal radiusx;
    qreal radiusy;
};

#endif // PAINTER_H
