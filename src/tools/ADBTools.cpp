#include "ADBTools.h"
#include <QDir>
#include <QCoreApplication>


//const QString ADBPATH = QCoreApplication::instance()->applicationFilePath() + "../tools/platform-tools/adb";
//const QString FASTBOOTPATH = "../tools/platform-tools/fastboot";
//#else
//const QString ADBPATH = "../tools/platform-tools/adb";
//const QString FASTBOOTPATH = "../tools/platform-tools/fastboot";
//#endif

ADBTools::ADBTools(QObject *parent) : QObject (parent)
{
    ADBPATH = qApp->applicationDirPath() + QDir::separator() + "../tools/platform-tools/adb";
    FASTBOOTPATH = qApp->applicationDirPath() + QDir::separator() + "../tools/platform-tools/fastboot";
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
    pro.waitForFinished(3000);    //命令执行超过3秒强制提出
    QString ret = pro.readAllStandardOutput();
    if(ret.isEmpty()) {
        ret = pro.readAllStandardError();
    }
    return ret;
}
QString ADBTools::executeCommandNoLimit(const QString &cmd)
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
    pro.waitForFinished(300000);    //命令执行超过300秒强制提出
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

