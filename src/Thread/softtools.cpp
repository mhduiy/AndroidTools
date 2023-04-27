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

bool SoftTools::extractApp(const QString &packageName, const QString &targetPath)
{
    qDebug() << "提取" << packageName << " " << targetPath<< QThread::currentThreadId();
    return true;
}

SoftTools *SoftTools::getInstance(QObject *parent)
{
    if(nullptr == SoftTools::instance) {
        SoftTools::instance = new SoftTools(parent);
    }
    return SoftTools::instance;
}
