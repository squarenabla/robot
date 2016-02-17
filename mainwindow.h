#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>

#include "qcustomplot.h"
#include "tcpsocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setSpeed(qreal sx, qreal sy);
    void setError(qreal erx, qreal ery);

private:
    void setupPlot();
    void plotError(qreal key);

    Ui::MainWindow *ui;
    TCPSocket *socket;
    QPainter *painter;
    int time;

    double erX;
    double erY;

    QTimer dataTimer;
    //double lastPointKey;
};

#endif // MAINWINDOW_H
