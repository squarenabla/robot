#include "robot.h"

Robot::Robot(QObject *parent) :
    QObject(parent)
{
    prevspeedX = 0.0;
    prevspeedY = 0.0;

    prevForceX = 0.0;
    prevForceY = 0.0;

    firstMessage = true;
}


s_taskEnvironment Robot::findTarget(const s_taskEnvironment &environment){
    s_taskEnvironment result = environment;

    if(result.done == 1.0){
        emit taskDone();
        return result;
    }

    if(result.task == 2.0){
        switch ((int)(result.point)) {
        case 0:
            result.targetX = 0.7;
            result.targetY = 0.0;
            break;
        case 1:
            result.targetX = 0.0;
            result.targetY = 0.7;
            break;
        case 2:
            result.targetX = -0.3;
            result.targetY = 0.0;
            break;
        case 3:
            result.targetX = -0.7;
            result.targetY = 0.0;
            break;
        case 4:
            result.targetX = 0.7;
            result.targetY = 0.0;
            break;
        case 5:
            result.targetX = 0.0;
            result.targetY = -0.8;
            break;
        case 6:
            result.targetX = 0.0;
            result.targetY = -0.8;
            break;
        default:
            break;
        }
    }
    return result;
}

QPair<qreal, qreal> Robot::makeDecision(const s_taskEnvironment &rawData){
    s_taskEnvironment environment = findTarget(rawData);

    qreal targetX = environment.targetX;
    qreal targetY = environment.targetY;

    qreal positionX = environment.positionX;
    qreal positionY = environment.positionY;

    qreal speedX = environment.speedX;
    qreal speedY = environment.speedY;

    qreal radius = environment.radius;

    qreal alpha = qAbs((targetX - positionX)/(targetY - positionY));
    qreal betta = 1/qSqrt(alpha*alpha+1);

    qreal dSpeedX = sgn(targetX-positionX)*alpha*betta*CRUISE_SPEED-speedX;
    qreal dSpeedY = sgn(targetY-positionY)*betta*CRUISE_SPEED-speedY;

    if(qAbs(targetX - positionX) < radius/2){
        if(qAbs(targetX - positionX) < radius/4){
            dSpeedX = -speedX;
        }
        else{
            dSpeedX = sgn(targetX-positionX)*alpha*betta*CRUISE_SPEED/2-speedX;
        }
    }

    if(qAbs(targetY - positionY) < radius/2){
        if(qAbs(targetY - positionY) < radius/4){
            dSpeedY = -speedY;
        }
        else{
            dSpeedY = sgn(targetY-positionY)*betta*CRUISE_SPEED/2-speedY;
        }
    }

    qreal errorFx = 0.0;
    qreal errorFy = 0.0;

    if(!firstMessage){
        errorFx = (/*mass**/(speedX - prevspeedX)/*/dt*/) - prevForceX;
        errorFy = (/*mass**/(speedY - prevspeedY)/*/dt*/) - prevForceY;
    }
    else{
        firstMessage = false;
    }

    qreal forceX = dSpeedX + FxPid.outputSignal(errorFx);
    qreal forceY = dSpeedY + FyPid.outputSignal(errorFy);

    prevspeedX = speedX;
    prevspeedY = speedY;

    prevForceX = forceX;
    prevForceY = forceY;

    emit sendError(errorFx,errorFy, forceX, forceY);
    emit sendSpeed(speedX, speedY, targetX-positionX, targetY-positionY);
    emit sendPosition(positionX,positionY,targetX,targetY, radius);

    return QPair<qreal,qreal>(-forceX, -forceY);
}

















