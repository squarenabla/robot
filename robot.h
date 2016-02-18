#ifndef ROBOT_H
#define ROBOT_H

#include <QtCore/qmath.h>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QPair>

#include "pidregulator.h"

class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);

signals:
    void sendPosition(const qreal x, const qreal y,
                      const qreal tx, const qreal ty,
                      const qreal r);

    void sendError(const qreal erx, const qreal ery,
                   const qreal fx, const qreal fy);
    void sendSpeed(const qreal vx, const qreal vy,
                   const qreal dx, const qreal dy);


    void taskDone();

public slots:
    QPair<qreal,qreal> makeDecision(const s_taskEnvironment &rawData);

private:
    qreal prevspeedX;
    qreal prevspeedY;

    qreal prevForceX;
    qreal prevForceY;

    s_taskEnvironment findTarget(const s_taskEnvironment &environment);

    PidRegulator FxPid;
    PidRegulator FyPid;

    bool firstMessage;
};

#endif // ROBOT_H
