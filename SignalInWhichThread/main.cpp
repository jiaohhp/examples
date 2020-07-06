/*
 * same thread: QProcess::finished
 */
#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "MainThreadId=" << QThread::currentThreadId();

    /////////////QProcess /////////////////////
    QProcess *process = new QProcess(&a);
    process->setProgram("ping");
    process->setArguments(QStringList() << "-c" << "1" << "www.baidu.com");
    QObject::connect(process, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), &a, [=](){
        qDebug() << "QProcess::finished ThreadId=" << QThread::currentThreadId();
    }, Qt::DirectConnection);
    process->start();

    /////////////////http get//////////////////////
    QNetworkAccessManager* manager = new QNetworkAccessManager(&a);
    QObject::connect(manager, &QNetworkAccessManager::finished, &a, [](QNetworkReply* reply){
        qDebug() << "QNetworkAccessManager::finished ThreadId=" << QThread::currentThreadId();
        reply->deleteLater();
    }, Qt::DirectConnection);
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));

    return a.exec();
}
