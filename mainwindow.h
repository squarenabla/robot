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
    void setSpeed(qreal sx, qreal sy, qreal dx, qreal dy);
    void setError(qreal erx, qreal ery, qreal fx, qreal fy);
    void enableButton();

private slots:
    void on_pushButton_clicked();

private:
    void setupPlot();
    void plotError(qreal key, qreal value0, qreal value1);

    Ui::MainWindow *ui;
    TCPSocket *socket;
    QPainter *painter;

    int time;

    double erX;
    double erY;

    QTimer dataTimer;
};

#endif // MAINWINDOW_H
