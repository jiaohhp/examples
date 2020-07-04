/*
 * 必须QT库编译时支持syslog/jourld才可以，实测系统默认qt库不支持。
 */
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
int main(int argc, char *argv[])
{
    qputenv("QT_LOGGING_TO_CONSOLE", QByteArray("0"));
    QCoreApplication a(argc, argv);
    QTimer* timer = new QTimer(&a);
    timer->setInterval(1000);
    QObject::connect(timer, &QTimer::timeout, &a, [](){
        static int i = 0; qDebug() << ++i;
    });
    timer->start();
    return a.exec();
}
