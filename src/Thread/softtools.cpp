#include "softtools.h"
#include <QDebug>
#include <QThread>
#include "deviceConnect.h"

SoftTools* SoftTools::instance = nullptr;

SoftTools::SoftTools(QObject *parent) : QObject(parent)
{

}

bool SoftTools::installApp(const QString &Path)
{
    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    qDebug() << "安装" << Path << QThread::currentThreadId();
    QString command = QString("adb -s %1 install %2").arg(cutDevice).arg(Path);
    qDebug() << command;
    adbTool.executeCommand(command);
    return true;
}

bool SoftTools::clearData(const QString &packageName)
{
    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    qDebug() << "清除" << packageName << QThread::currentThreadId();
    QString command = QString("adb -s %1 shell pm clear %2").arg(cutDevice).arg(packageName);
    adbTool.executeCommand(command);
    return true;
}

bool SoftTools::uninstallApp(const QString &packageName)
{
    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    qDebug() << "卸载" << packageName<< QThread::currentThreadId();
    QString command = QString("adb -s %1 uninstall %2").arg(cutDevice).arg(packageName);
    adbTool.executeCommand(command);
    return true;
}

bool SoftTools::freezeApp(const QString &packageName)
{
    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    qDebug() << "冻结" << packageName<< QThread::currentThreadId();
    QString command = QString("adb -s %1 shell pm disable-user %2").arg(cutDevice).arg(packageName);
    adbTool.executeCommand(command);
    return true;
}

bool SoftTools::unfreezeApp(const QString &packageName)
{
    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    qDebug() << "解冻" << packageName<< QThread::currentThreadId();
    QString command = QString("adb -s %1 shell pm enable %2").arg(cutDevice).arg(packageName);
    adbTool.executeCommand(command);
    return true;
}

bool SoftTools::extractApp(const QString &packageName, const QString &targetPath)
{
    qDebug() << "提取" << packageName << " " << targetPath<< QThread::currentThreadId();

    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();

    QString command1 = QString("adb -s %1 shell pm path %2").arg(cutDevice).arg(packageName);
    QString _apkPath =  adbTool.executeCommand(command1);

    _apkPath = _apkPath.simplified().split(':').value(1);
    qDebug() << packageName << "路径：" << _apkPath;

    QString command = QString("adb -s %1 pull %2 %3").arg(cutDevice).arg(_apkPath).arg(targetPath);
    adbTool.executeCommand(command);
    return true;
}

SoftTools *SoftTools::getInstance(QObject *parent)
{
    if(nullptr == SoftTools::instance) {
        SoftTools::instance = new SoftTools(parent);
    }
    return SoftTools::instance;
}
