#include "ADBTools.h"

const QString ADBPATH = "../tools/platform-tools/adb";
const QString FASTBOOTPATH = "../tools/platform-tools/fastboot";

ADBTools::ADBTools(QObject *parent) : QObject (parent)
{

}

ADBTools::~ADBTools()
{

}

QString ADBTools::executeCommand(const QString &cmd)
{
    if(cmd.isEmpty()) {
        return QString();
    }
    QString command = cmd;
    //使用新的adb路径
    if(cmd.startsWith("adb")) {
        command = command.right(command.size() - 3);
        command = ADBPATH + command;
    }
    else if(cmd.startsWith("fastboot")) {
        command = command.right(command.size() - 8);
        command = FASTBOOTPATH + command;
    }
    QProcess pro;
    pro.start(command);
    pro.waitForFinished(5000);
    QString ret = pro.readAllStandardOutput();
    if(ret.isEmpty()) {
        ret = pro.readAllStandardError();
    }
    return ret;
}

bool ADBTools::pairDevice(const QString &ip, const QString &pairCode)
{
    QString command = QString("echo %1 | %2 pair %3").arg(pairCode).arg(ADBPATH).arg(ip);
    FILE *fp = popen(command.toLocal8Bit(), "r");
    QTextStream stream(fp);
    QString ret = stream.readAll();
    qDebug() << ret;
    if(ret.contains(" Failed: ")) { //配对失败
        return false;
    }
    else {
        return true;
    }
}

