#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <chrono>

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

#include <QPair>
#include <QString>
#include <QStringList>

#include "globals.h"
#include "robot.h"
#include "parser.h"

class TCPSocket : public QObject
{
    Q_OBJECT
public:
    explicit TCPSocket(QObject *parent = 0);

    void doConnect();

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
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:

    QTcpSocket *socket;
    Robot *robot;
    Parser *parser;
    unsigned int prevTime;

};

#endif // TCPSOCKET_H
