#include "robot.h"

//QStringList Robot::searchTags = (QStringList()<<"RX"<<"RY"<<"VRX"<<"VRY"<<"TX"<<"TY"<<"M"<<"R");

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

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
    searchMap.insert("(T=",&timeNow);
    searchMap.insert("IGNORED=",&ignored);
    searchMap.insert("TASK=", &taskNum);
    searchMap.insert("POINT=", &pointNum);

    positionX = 0.0;
    positionY = 0.0;

    speedX = 0.0;
    speedY = 0.0;

    prevspeedX = 0.0;
    prevspeedY = 0.0;

    targetX = 0.0;
    targetY = 0.0;

    timeNow = 0.0;
    timePast = 0.0;

    radius = 0.0;

    mass = 0.0;

    ignored = 0.0;

    firstMessage = true;
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

void Robot::showForce(){
    qDebug()<<"force:"<<forceX<<forceY;
    return;
}

void Robot::parseDataStream(const QByteArray &data){
    QRegExp rx("(RX=|RY=|VRX=|VRY=|TX=|TY=|\\(R=|M=|\\(T=|IGNORED=|TASK=)(\\-?\\d+\\.?\\d*)");
    QString str(data);
    int pos = 0;

    //qDebug()<<"parsing..."<<data.size()<<"bytes";

    qDebug()<<data;

    timePast = timeNow;
    prevspeedX = speedX;
    prevspeedY = speedY;
    prevIgnored = ignored;

    while((pos = rx.indexIn(str, pos)) != -1){
      //  qDebug()<<rx.cap(1)<<rx.cap(2);
        (*searchMap[rx.cap(1)]) = rx.cap(2).toDouble();
        pos += rx.matchedLength();
    }

    if(taskNum == 2.0){
        targetX = 0.7;
        targetY = 0.0;
        //firstMessage = true;
        switch ((int)pointNum) {
        case 0:
            targetX = 0.7;
            targetY = 0.0;
            break;
        case 1:
            targetX = 0.0;
            targetY = 0.7;
            break;
        case 2:
            targetX = -0.3;
            targetY = 0.0;
            break;
        case 3:
            targetX = -0.7;
            targetY = 0.0;
            break;
        case 4:
            targetX = 0.7;
            targetY = 0.0;
            break;
        case 5:
            targetX = 0.0;
            targetY = -0.8;
            break;
        default:
            break;
        }
    }
 //forceX = (mass*speedX*speedX)/(positionX - targetX);
    //forceY = (mass*speedY*speedY)/(positionY - targetY);
  //  qDebug()<<timeNow;



    //qreal dspx = speedX-prevspeedX;
    //qreal dspy = speedY-prevspeedY;
    qreal dt = timeNow-timePast;

    qDebug()<<"Ignored:"<<ignored;
    qDebug()<<"Position (dX dY)"<<targetX - positionX<<targetY - positionY;
   // qDebug()<<"Time (past now)"<<timePast<<timeNow;
    //if(qAbs(ignored - prevIgnored) < SMALL_NUM){
        qreal alpha = qAbs((targetX - positionX)/(targetY - positionY));
        qreal betta = 1/qSqrt(alpha*alpha+1);

        qreal dSpeedX = sgn(targetX-positionX)*alpha*betta*CRUISE_SPEED-speedX;
        qreal dSpeedY = sgn(targetY-positionY)*betta*CRUISE_SPEED-speedY;

        if(qAbs(targetX - positionX) < radius){
            if(qAbs(targetX - positionX) < radius/2){
                dSpeedX = -speedX;
            }
            else{
                dSpeedX = sgn(targetX-positionX)*alpha*betta*CRUISE_SPEED/2-speedX;
            }
        }

        if(qAbs(targetY - positionY) < radius){
            if(qAbs(targetY - positionY) < radius/2){
                dSpeedY = -speedY;
            }
            else{
                dSpeedY = sgn(targetY-positionY)*betta*CRUISE_SPEED/2-speedY;
            }
        }

        qDebug()<<"delta speed"<<dSpeedX<<dSpeedY;

        qreal k = qAbs(dSpeedX/dSpeedY);



        qreal errorFx = 0.0;
        qreal errorFy = 0.0;

        if(!firstMessage){
            errorFx = (/*mass**/(speedX - prevspeedX)/*/dt*/) - forceX;
            errorFy = (/*mass**/(speedY - prevspeedY)/*/dt*/) - forceY;
        }
        else{
            firstMessage = false;
        }

        if(qAbs(dSpeedX) < 0.001 || qAbs(dSpeedY) < 0.001){
            if(dSpeedX < 0.001){
                forceX = 0.0;
                forceY = sgn(dSpeedY)*MAX_FORCE;
            }
            if(dSpeedY < 0.001){
                forceY = 0.0;
                forceX = sgn(dSpeedX)*MAX_FORCE;
            }
        }
        else{
            if(k < 1){
                    forceX = k*sgn(dSpeedX)*MAX_FORCE/*mass*MAX_AXELERATION*/;
                    forceY = sgn(dSpeedY)*MAX_FORCE/*mass*MAX_AXELERATION*/;
            }
            else{
                    forceX = sgn(dSpeedX)*MAX_FORCE/*mass*MAX_AXELERATION*/;
                    forceY = sgn(dSpeedY)*MAX_FORCE/*mass*MAX_AXELERATION*//k;
            }
        }
  //      }

        //forceX = FxPid.outputSignal(errorFx) + mass*(alpha*betta*CRUISE_SPEED-speedX)/TIME_TO_CRUISE;
        //forceY = FyPid.outputSignal(errorFy) + mass*(betta*CRUISE_SPEED-speedY)/TIME_TO_CRUISE;

       // FxPid.outputSignal(errorFx);
       // FyPid.outputSignal(errorFy);
          forceX += FxPid.outputSignal(errorFx);
          forceY += FyPid.outputSignal(errorFy);
    //}
    //qDebug()<<"Real FX ="<<mass*(dspx)/(dt);
    //qDebug()<<"Real FY ="<<mass*(dspy)/(dt);


    //qDebug()<<"Real F ="<<mass*qSqrt(dspx*dspx + dspy*dspy)/dt;
    //qDebug()<<"Real PX ="<<mass*(speedX-prevspeedX);

    //forceX = 1.0;
    //forceY = 1.0;

    emit sendPosition(positionX,positionY,targetX,targetY, radius);
    emit sendError(errorFx,errorFy);
    emit sendSpeed(speedX, speedY, targetX-positionX, targetY-positionY);

    showForce();
    return;
}

QString Robot::packData(){
    //QString resultForce("{(FRX="+QString::number(forceX)+")(FRY="+QString::number(forceY)+")}");
    return "{(FRX="+QString::number(-forceX)+")(FRY="+QString::number(-forceY)+")}";
    //return "{(FRX=1.0)(FRY=1.0)}";
}
















