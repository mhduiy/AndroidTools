#include "flashThreadTool.h"
#include <QThread>

FlashThreadTool *FlashThreadTool::instance = nullptr;

FlashThreadTool::FlashThreadTool(QObject *parent) : QObject (parent)
{

}

FlashThreadTool::~FlashThreadTool()
{

}

void FlashThreadTool::FlashPGInfo()
{
    MHDUIY::deviceRealTimeInfo *info = new MHDUIY::deviceRealTimeInfo();
    QString ret = tool.executeCommand("adb shell dumpsys battery");
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

void FlashThreadTool::checkNewDevice()
{
    QString ret = tool.executeCommand("adb devices");
//    ret = ret.simplified();
//    info->info[MHDUIY::deviceBaceInfo::DeviceCodeName] =
    QStringList l = ret.split('\n');
    QVector<MHDUIY::deviceBaceInfo*> res;
    bool readFlag = false;
    for (QString &s : l) {
        if(s.isEmpty()) {
            continue;
        }
        if(s.startsWith("*")) {
            return;
        }
        if(s == "List of devices attached") {
            readFlag = true;
        }
        if(readFlag == true) {  //读取到新设备
            MHDUIY::deviceBaceInfo *info = new MHDUIY::deviceBaceInfo();
            s = s.simplified();
            QStringList ll = s.split(' ');
            if(ll.value(1) == "device") {
                qDebug() << ll.value(0);
                info->info[MHDUIY::deviceBaceInfo::DeviceCodeName] = ll.value(0);
            }
            res.push_back(info);
        }
    }
}

FlashThreadTool *FlashThreadTool::getInstance(QObject *parent)
{
    if(FlashThreadTool::instance == nullptr) {
        FlashThreadTool::instance = new FlashThreadTool(parent);
    }
    return FlashThreadTool::instance;
}
