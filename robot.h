#ifndef ROBOT_H
#define ROBOT_H

#include <QtCore/qmath.h>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QRegExp>
#include <QStringList>
#include <QMap>

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

    void sendError(const qreal erx, const qreal ery);
    void sendSpeed(const qreal vx, const qreal vy,
                   const qreal dx, const qreal dy);


public slots:
    void setPosition(const qreal &x, const qreal &y);
    void setSpeed(const qreal &x, const qreal &y);
    void setTarget(const qreal &x, const qreal &y);
    void setMass(const qreal &m);

    void parseDataStream(const QByteArray &data);
    QString packData();

    void showRobotParam();
    void showForce();

private:
    qreal positionX;
    qreal positionY;


    qreal speedX;
    qreal speedY;

    qreal prevspeedX;
    qreal prevspeedY;

    qreal targetX;
    qreal targetY;

    qreal mass;
    qreal radius;

    qreal forceX;
    qreal forceY;

    qreal timeNow;
    qreal timePast;
    //static QStringList searchTags;
    qreal realFx;
    qreal realFy;

    qreal ignored;
    qreal prevIgnored;

    qreal taskNum;
    qreal pointNum;

    PidRegulator FxPid;
    PidRegulator FyPid;

    bool firstMessage;

    QMap<QString, qreal*> searchMap;
};

#endif // ROBOT_H
