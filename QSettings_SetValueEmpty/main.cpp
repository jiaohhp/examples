/*
 * 1. settings.setValue("key","") => key=  =>v = settings.value("key","0") => v=""
 */
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSettings settings("jiaohhp", "examples");
    settings.setValue("EmptyValue", "");
    settings.setValue("Value", "1");
    qDebug() << settings.value("EmptyValue", "0").toString();
    settings.remove("EmptyValue");
    qDebug() << settings.value("EmptyValue", "0").toString();
    return a.exec();
}
