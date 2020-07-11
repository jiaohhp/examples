#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QDebug>
#include <QThread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(0, this, [](){
        const char* names[] = {
            "QThread::IdlePriority",
            "QThread::LowestPriority",
            "QThread::LowPriority",
            "QThread::NormalPriority",
            "QThread::HighPriority",
            "QThread::HighestPriority",
            "QThread::TimeCriticalPriority",
            "QThread::InheritPriority"
        };
        qDebug() << "ui thread priority:" << names[QThread::currentThread()->priority()];
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
