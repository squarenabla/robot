#include "tcpsocket.h"

TCPSocket::TCPSocket(QObject *parent) :
    QObject(parent)
{
}

void TCPSocket::doConnect(){
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug()<<"connecting";

    socket->connectToHost(QString(TCP_ADRESS), TCP_PORT);

    if(!socket->waitForConnected(5000)){
        qDebug()<<"Error: "<<socket->errorString();
    }

    return;
}

void TCPSocket::connected(){
    qDebug()<<"connected";
    socket->write("knock - knock");
    return;
}

void TCPSocket::disconnected(){
    qDebug()<<"disconnected";
    return;
}

void TCPSocket::bytesWritten(qint64 bytes){
    qDebug()<<bytes;
    return;
}

void TCPSocket::readyRead(){
    qDebug()<<"reading";
    qDebug()<<socket->readAll();
    return;
}
