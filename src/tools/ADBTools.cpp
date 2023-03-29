#include "ADBTools.h"

const QString ADBPATH = "/usr/bin/adb";

ADBTools::ADBTools(QObject *parent) : QObject (parent)
{

}

ADBTools::~ADBTools()
{

}

QString ADBTools::executeCommand(const QString &cmd)
{
    QProcess pro;
    pro.start(cmd);
    pro.waitForFinished(5000);
    QString ret = pro.readAllStandardOutput();
    if(ret.isEmpty()) {
        ret = pro.readAllStandardError();
    }
    return ret;
}
