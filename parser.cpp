#include "parser.h"

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    searchMap.insert("RX=",&data.positionX);
    searchMap.insert("RY=",&data.positionY);
    searchMap.insert("VRX=",&data.speedX);
    searchMap.insert("VRY=",&data.speedY);
    searchMap.insert("TX=",&data.targetX);
    searchMap.insert("TY=",&data.targetY);
    searchMap.insert("M=",&data.mass);
    searchMap.insert("(R=",&data.radius);
    searchMap.insert("(T=",&data.timeNow);
    searchMap.insert("TASK=", &data.task);
    searchMap.insert("POINT=", &data.point);
    searchMap.insert("DONE=", &data.done);

    regExp = QRegExp("(RX=|RY=|VRX=|VRY=|TX=|TY=|\\(R=|M=|\\(T=|TASK=|POINT=|DONE=)(\\-?\\d+\\.?\\d*)");
}

void Parser::parseDataStream(const QByteArray &byteData){
    QString str(byteData);
    int pos = 0;
    qDebug()<<byteData;

    while((pos = regExp.indexIn(str, pos)) != -1){
        (*searchMap[regExp.cap(1)]) = regExp.cap(2).toDouble();
        pos += regExp.matchedLength();
    }
    return;
}

s_taskEnvironment Parser::getParsedData(){
    return data;
}

QString Parser::packData(qreal value0, qreal value1){
    return "{(FRX="+QString::number(value0)+")(FRY="+QString::number(value1)+")}";
}
