#include "ADBTools.h"

const QString ADBPATH = "../tools/platform-tools/adb";

ADBTools::ADBTools(QObject *parent) : QObject (parent)
{

}

ADBTools::~ADBTools()
{

}

QString ADBTools::executeCommand(const QString &cmd)
{
    QString command = cmd;
    //使用新的adb路径
    if(cmd.startsWith("adb")) {
        command = command.right(command.size() - 3);
        command = ADBPATH + command;
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
