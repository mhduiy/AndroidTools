#include "flashtool.h"
#include "deviceConnect.h"
#include <QApplication>
#include <QProcess>

FlashTool* FlashTool::instance = nullptr;

FlashTool::FlashTool(QObject *parent) : QObject(parent)
{

}

void FlashTool::flashPartition(const QString &partition, const QString &imgPath)
{
    QString command = QString("./fastboot -s %1 flash %2 %3").arg(DeviceConnect::getInstance()->getCurrentFastBootDeviceCode())
            .arg(partition).arg(imgPath);
    QProcess::startDetached(QString(R"(deepin-terminal --keep-open -w %1 -C "%2")").arg(QApplication::applicationDirPath() + "/../tools/platform-tools")
            .arg(command));

}

void FlashTool::startPartition(const QString &imgPath)
{
    QString command = QString("fastboot -s %1 boot %2").arg(DeviceConnect::getInstance()->getCurrentFastBootDeviceCode()).arg(imgPath);
    QProcess::startDetached(QString(R"(deepin-terminal --keep-open -w %1 -C "%2")").arg(QApplication::applicationDirPath() + "/../tools/platform-tools")
            .arg(command));
}

void FlashTool::eraserPartition(const QString &artition)
{
    QString command = QString("fastboot -s %1 erase %2").arg(DeviceConnect::getInstance()->getCurrentFastBootDeviceCode()).arg(artition);
    QProcess::startDetached(QString(R"(deepin-terminal --keep-open -w %1 -C "%2")").arg(QApplication::applicationDirPath() + "/../tools/platform-tools")
                            .arg(command));
}

FlashTool* FlashTool::getInstance(QObject *parent)
{
    if(nullptr ==FlashTool::instance) {
        FlashTool::instance = new FlashTool(parent);
    }
    return FlashTool::instance;
}
