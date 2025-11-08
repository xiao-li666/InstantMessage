#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include "global.h"

/******************************************************************************
 *
 * @file       main.cpp
 * @brief     主窗口
 *
 * @author     xiaoli
 * @date       2025/10/24
 * @history
 *****************************************************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //读取qss
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("open file success!");
        QString style = QLatin1String(qss.readAll()); //QByteArray转成QString
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("open file is failed!");
    }
    //都配置文件
    QString fileName = "config.ini";
    QString appPath = QCoreApplication::applicationDirPath();
    QString configpath = QDir::toNativeSeparators(appPath + QDir::separator() + fileName);//获得配置文件的路径
    QSettings settings(configpath,QSettings::IniFormat);//读取配置文件
    QString gateHost = settings.value("GateServer/host").toString();//获取配置文件中的信息
    QString gatePort = settings.value("GateServer/port").toString();
    gateUrlPrefix = "http://" + gateHost + ":" + gatePort;



    MainWindow w;
    w.show();
    return a.exec();
}
