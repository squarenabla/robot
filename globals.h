#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtCore>

#define TCP_PORT 9999
#define TCP_ADRESS "127.0.0.1"
#define BUFFER_SIZE 218

#define KP 0.2
#define KI 0.0
#define KD 0.2

#define CRUISE_SPEED 0.2
#define TIME_TO_CRUISE 0.1
#define MAX_AXELERATION 0.001
#define MAX_FORCE 0.1
#define SMALL_NUM 0.0001

struct s_taskEnvironment{
    qreal positionX = 0.0;
    qreal positionY = 0.0;

    qreal speedX = 0.0;
    qreal speedY = 0.0;

    qreal prevspeedX = 0.0;
    qreal prevspeedY = 0.0;

    qreal targetX = 0.0;
    qreal targetY = 0.0;

    qreal mass = 0.0;
    qreal radius = 0.0;

    qreal timeNow = 0.0;
    qreal timePast = 0.0;

    qreal point = 0.0;
    qreal task = 0.0;
    qreal done = 0.0;
};


template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#endif // GLOBALS_H
