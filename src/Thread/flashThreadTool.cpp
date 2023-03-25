#include "flashThreadTool.h"
#include <QThread>
#include "deviceConnect.h"

FlashThreadTool *FlashThreadTool::instance = nullptr;

FlashThreadTool::FlashThreadTool(QObject *parent) : QObject (parent)
{

}

FlashThreadTool::~FlashThreadTool()
{

}

void FlashThreadTool::FlashPGInfo()
{
    QString currentDeviceCode = DeviceConnect::getInstance()->getCurrentDeviceCode();
    QString command = QString("adb -s %1 shell dumpsys battery").arg(currentDeviceCode);

    MHDUIY::deviceRealTimeInfo *info = new MHDUIY::deviceRealTimeInfo();
    QString ret = tool.executeCommand(command);
    QStringList l = ret.split('\n');
    for(auto &s : l) {
        s = s.simplified();
        if(s.startsWith("level")) {
            info->info[MHDUIY::deviceRealTimeInfo::BatteryLevel] = s.split(":").value(1) + "%";
            info->valueInfo[MHDUIY::deviceRealTimeInfo::BatteryLevel] = s.split(":").value(1).toInt();
        }
    }
    emit readDeviceInfoFinish(info);
}


FlashThreadTool *FlashThreadTool::getInstance(QObject *parent)
{
    if(FlashThreadTool::instance == nullptr) {
        FlashThreadTool::instance = new FlashThreadTool(parent);
    }
    return FlashThreadTool::instance;
}
