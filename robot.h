#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QRegExp>
#include <QStringList>
#include <QMap>

class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);

signals:

public slots:
    void setPosition(const qreal &x, const qreal &y);
    void setSpeed(const qreal &x, const qreal &y);
    void setTarget(const qreal &x, const qreal &y);
    void setMass(const qreal &m);

    void parseDataStream(const QByteArray &data);

    void showRobotParam();

private:
    qreal positionX;
    qreal positionY;

    qreal speedX;
    qreal speedY;

    qreal targetX;
    qreal targetY;

    qreal mass;
    qreal radius;

    //static QStringList searchTags;

    QMap<QString, qreal*> searchMap;
};

#endif // ROBOT_H
