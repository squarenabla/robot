#ifndef PIDREGULATOR_H
#define PIDREGULATOR_H

#include <QObject>
#include <QDebug>

#include "globals.h"

class PidRegulator : public QObject
{
    Q_OBJECT
public:
    explicit PidRegulator(QObject *parent = 0);
    ~PidRegulator();

signals:

public slots:
    qreal outputSignal(const qreal &error);
private:
    qreal proportion;
    qreal integr;
    qreal diff;

    qreal prevIntegr;
    qreal prevError;
};

#endif // PIDREGULATOR_H
