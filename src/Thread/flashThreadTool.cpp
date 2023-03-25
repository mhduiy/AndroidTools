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
    if(nullptr != this->info) {
        delete this->info;  //刷新前释放内存
    }
    QString currentDeviceCode = DeviceConnect::getInstance()->getCurrentDeviceCode();
    MHDUIY::deviceRealTimeInfo *resInfo = new MHDUIY::deviceRealTimeInfo();
    /*电量  温度  */
    QString command = QString("adb -s %1 shell dumpsys battery").arg(currentDeviceCode);
    QString ret = tool.executeCommand(command);
    auto serialInfo = MHDUIY::serializationInformation(ret);
    QString btyLevelInfo = serialInfo["level"];
    resInfo->info[MHDUIY::deviceRealTimeInfo::BatteryLevel] = btyLevelInfo + "%";
    resInfo->valueInfo[MHDUIY::deviceRealTimeInfo::BatteryLevel] = btyLevelInfo.toInt();
    QString btyTepInfo = serialInfo["temperature"];
    resInfo->valueInfo[MHDUIY::deviceRealTimeInfo::BatteryTEMP] = btyTepInfo.toInt() * 10 / 50;
    resInfo->info[MHDUIY::deviceRealTimeInfo::BatteryTEMP] = btyTepInfo.insert(btyTepInfo.size() - 1, '.') + " ℃";

    /*内存*/
    command = QString("adb -s %1 shell cat /proc/meminfo").arg(currentDeviceCode);
    ret = tool.executeCommand(command);
    serialInfo = MHDUIY::serializationInformation(ret);
    double totalMem = serialInfo["MemTotal"].split(' ').value(0).toDouble() / 1024 / 1024;
    double freeMem = serialInfo["MemAvailable"].split(' ').value(0).toDouble() / 1024 / 1024;
    resInfo->info[MHDUIY::deviceRealTimeInfo::MemoryUsed] = QString("%1GB/%2GB")
            .arg(QString::number(freeMem, 'f', 1))
            .arg(QString::number(totalMem, 'f', 1));
    resInfo->valueInfo[MHDUIY::deviceRealTimeInfo::MemoryUsed] = int(freeMem / totalMem * 100.0);

    info = resInfo;
    emit readDeviceInfoFinish(resInfo);
}


FlashThreadTool *FlashThreadTool::getInstance(QObject *parent)
{
    if(FlashThreadTool::instance == nullptr) {
        FlashThreadTool::instance = new FlashThreadTool(parent);
    }
    return FlashThreadTool::instance;
}
