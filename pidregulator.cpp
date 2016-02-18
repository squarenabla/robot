#include "pidregulator.h"

PidRegulator::PidRegulator(QObject *parent) : QObject(parent)
{
    proportion = 0.0;
    integr = 0.0;
    diff = 0.0;

    //prevIntegr = 0.0;
    prevError = 0.0;
}

PidRegulator::~PidRegulator(){}

qreal PidRegulator::outputSignal(const qreal &error){
    //qDebug()<<"Error:"<<error;
    proportion = KP*error;
    integr+=KI*error;
    diff = KD*(error - prevError);

    prevError = error;

    return proportion+integr+diff;
}
