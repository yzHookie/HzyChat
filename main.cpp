#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QSettings>
#include "global.h"
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

    // 读取配置文件
    QString file_name = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();

    // QDir::separator() 为分割符，可处理linux和windows不同的斜杠
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + file_name);
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    MainWindow w;
    w.show();
    return a.exec();
}
