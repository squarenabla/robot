
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupPlot();

    socket = new TCPSocket(this);
    connect(socket, SIGNAL(sendPosition(qreal,qreal,qreal,qreal,qreal)),
            ui->widget, SLOT(paintPosition(qreal,qreal,qreal,qreal,qreal)));

    connect(socket, SIGNAL(sendError(qreal,qreal)), this, SLOT(setError(qreal,qreal)));
    connect(socket, SIGNAL(sendSpeed(qreal,qreal)), this, SLOT(setSpeed(qreal,qreal)));

    time = 0;
    erX = 0.0;
    erY = 0.0;

    socket->doConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSpeed(qreal sx, qreal sy){
    ui->labelSpX->setText("Vx = "+QString::number(sx));
    ui->labelSpY->setText("Vy = "+QString::number(sy));
}

void MainWindow::setError(qreal erx, qreal ery){
    ui->labelErX->setText("Error Fx = "+QString::number(erx));
    ui->labelErY->setText("Error Fy = "+QString::number(ery));
    erX = qAbs(erx);
    erY = qAbs(ery);
    //plotError(time++, erx, ery);
    plotError(time++);
}

void MainWindow::setupPlot(){
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->customPlot->graph(0)->setAntialiasedFill(false);
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));

    ui->customPlot->addGraph(); // blue dot
    ui->customPlot->graph(2)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->addGraph(); // red dot
    ui->customPlot->graph(3)->setPen(QPen(Qt::red));
    ui->customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    //ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    //ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    //ui->customPlot->xAxis->setAutoTickStep(false);
    //ui->customPlot->xAxis->setTickStep(2);
    //ui->customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  //  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(plotError()));
  //  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::plotError(qreal key){
    //qDebug()<<key<<value0<<value1;

    double value0 = erX;
    double value1 = erY;

    //double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    qDebug()<<"PLOT!!!";


    //static double lastPointKey = 0;

    //if (key-lastPointKey > 0.01) // at most add point every 10 ms
    //{
     // double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
     // double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
      // add data to lines:
      ui->customPlot->graph(0)->addData(key, value0);
      ui->customPlot->graph(1)->addData(key, value1);
      // set data of dots:
      ui->customPlot->graph(2)->clearData();
      ui->customPlot->graph(2)->addData(key, value0);
      ui->customPlot->graph(3)->clearData();
      ui->customPlot->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      ui->customPlot->graph(0)->removeDataBefore(key-500);
      ui->customPlot->graph(1)->removeDataBefore(key-500);
      // rescale value (vertical) axis to fit the current data:
      ui->customPlot->graph(0)->rescaleValueAxis();
      ui->customPlot->graph(1)->rescaleValueAxis(true);
      //lastPointKey = key;
  //  }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key+0.25, 500, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
//    static double lastFpsKey;
//    static int frameCount;
//    ++frameCount;
//    if (key-lastFpsKey > 2) // average fps over 2 seconds
//    {
//      ui->statusBar->showMessage(
//            QString("%1 FPS, Total Data points: %2")
//            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
//            .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
//            , 0);
//      lastFpsKey = key;
//      frameCount = 0;
//    }
}

