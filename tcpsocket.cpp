#include "tcpsocket.h"

using namespace std::chrono;

TCPSocket::TCPSocket(QObject *parent) :
    QObject(parent)
{
    robot = new Robot(this);
    connect(robot,SIGNAL(sendPosition(qreal,qreal,qreal,qreal,qreal)),
            this, SIGNAL(sendPosition(qreal,qreal,qreal,qreal,qreal)));

    connect(robot, SIGNAL(sendError(qreal,qreal)),this,SIGNAL(sendError(qreal,qreal)));
    connect(robot, SIGNAL(sendSpeed(qreal,qreal,qreal,qreal)),this,SIGNAL(sendSpeed(qreal,qreal,qreal,qreal)));

    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    prevTime = ms.count();
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
    //socket->write("knock - knock");
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
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    //qDebug()<<(unsigned int)ms.count();
    QByteArray data =  socket->readAll();
    if((unsigned int)ms.count() - prevTime > 100){

        //qDebug()<<data;
        robot->parseDataStream(data.left(BUFFER_SIZE));
        prevTime = ms.count();

        //qDebug()<<robot->packData().toLocal8Bit();
        socket->write(robot->packData().toLocal8Bit());
        socket->flush();
    }
    return;
}

