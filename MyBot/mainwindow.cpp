#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readSettings();
    if (userName != "no name"){
        speakBot();
    }
    else{
        ui->listWidget->addItem("Как к вам обращаться?");
    }

    printHistory();
}


MainWindow::~MainWindow()
{
    delete ui;
}
