#include "mainwindow.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/sytle/stylesheet.qss");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("stylesheet open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    } else {
        qDebug("open failed");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
