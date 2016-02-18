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

    connect(socket, SIGNAL(sendError(qreal,qreal,qreal,qreal)), this, SLOT(setError(qreal,qreal,qreal,qreal)));
    connect(socket, SIGNAL(sendSpeed(qreal,qreal,qreal,qreal)), this, SLOT(setSpeed(qreal,qreal,qreal,qreal)));
    connect(socket, SIGNAL(taskDone()), this, SLOT(enableButton()));

    time = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSpeed(qreal sx, qreal sy, qreal dx, qreal dy){
    ui->labelSpX->setText("Vx = "+QString::number(sx));
    ui->labelSpY->setText("Vy = "+QString::number(sy));
    ui->labeldX->setText("dX = "+QString::number(dx));
    ui->labeldY->setText("dY = "+QString::number(dy));
}

void MainWindow::setError(qreal erx, qreal ery, qreal fx, qreal fy){
    ui->labelErX->setText("Error Fx = "+QString::number(erx));
    ui->labelErY->setText("Error Fy = "+QString::number(ery));
    plotError(time++, fx, fy);
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

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::plotError(qreal key, qreal value0, qreal value1){
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, value0);
    ui->customPlot->graph(1)->addData(key, value1);
    // set data of dots:
    ui->customPlot->graph(2)->clearData();
    ui->customPlot->graph(2)->addData(key, value0);
    ui->customPlot->graph(3)->clearData();
    ui->customPlot->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->customPlot->graph(0)->removeDataBefore(key-100);
    ui->customPlot->graph(1)->removeDataBefore(key-100);
    // rescale value (vertical) axis to fit the current data:
    ui->customPlot->graph(0)->rescaleValueAxis();
    ui->customPlot->graph(1)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key+0.25, 100, Qt::AlignRight);
    ui->customPlot->replot();
}


void MainWindow::on_pushButton_clicked(){
    ui->pushButton->setDisabled(true);
    socket->doConnect();
}

void MainWindow::enableButton(){
    ui->pushButton->setEnabled(true);
}
