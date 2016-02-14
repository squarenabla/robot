#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

#include <QString>

#include "globals.h"

class TCPSocket : public QObject
{
    Q_OBJECT
public:
    explicit TCPSocket(QObject *parent = 0);

    void doConnect();

signals:


public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
};

#endif // TCPSOCKET_H
