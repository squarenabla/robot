#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDebug>

#include <QByteArray>
#include <QMap>
#include <QRegExp>
#include <QString>

#include "globals.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

signals:

public slots:
    void parseDataStream(const QByteArray &byteData);
    s_taskEnvironment getParsedData();
    QString packData(qreal value0, qreal value1);

private:
    QMap<QString, qreal*> searchMap;
    s_taskEnvironment data;
    QRegExp regExp;
};

#endif // PARSER_H
