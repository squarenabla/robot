#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new TCPSocket(this);
    socket->doConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
