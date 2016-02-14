#include "robot.h"

//QStringList Robot::searchTags = (QStringList()<<"RX"<<"RY"<<"VRX"<<"VRY"<<"TX"<<"TY"<<"M"<<"R");

Robot::Robot(QObject *parent) :
    QObject(parent)
{
    searchMap.insert("RX=",&positionX);
    searchMap.insert("RY=",&positionY);
    searchMap.insert("VRX=",&speedX);
    searchMap.insert("VRY=",&speedY);
    searchMap.insert("TX=",&targetX);
    searchMap.insert("TY=",&targetY);
    searchMap.insert("M=",&mass);
    searchMap.insert("(R=",&radius);
}

void Robot::setPosition(const qreal &x, const qreal &y){
    positionX = x;
    positionY = y;
    return;
}

void Robot::setSpeed(const qreal &x, const qreal &y){
    speedX = x;
    speedY = y;
    return;
}

void Robot::setTarget(const qreal &x, const qreal &y){
    targetX = x;
    targetY = y;
    return;
}

void Robot::setMass(const qreal &m){
    mass = m;
    return;
}

void Robot::showRobotParam(){
    qDebug()<<"showing data";
    qDebug()<<positionX<<positionY<<speedX<<speedY<<
              targetX<<targetY<<mass<<radius;
    return;
}

void Robot::parseDataStream(const QByteArray &data){
    QRegExp rx("(RX=|RY=|VRX=|VRY=|TX=|TY=|\\(R=|M=)(\\-?\\d+\\.?\\d*)");
    QString str(data);
    int pos = 0;

    qDebug()<<"parsing...";

    while((pos = rx.indexIn(str, pos)) != -1){
        qDebug()<<rx.cap(1)<<rx.cap(2);
        (*searchMap[rx.cap(1)]) = rx.cap(2).toDouble();
        pos += rx.matchedLength();
    }

    showRobotParam();
    return;
}



