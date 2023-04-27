#include "updateThreadTool.h"
#include <QThread>
#include "deviceConnect.h"

UpdateThread *UpdateThread::instance = nullptr;

UpdateThread::UpdateThread(QObject *parent) : QObject (parent)
{

}

UpdateThread::~UpdateThread()
{

}

void UpdateThread::FlashPGInfo()
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
    resInfo->info[MHDUIY::deviceRealTimeInfo::MemoryUsed] = QString("%1G/%2G")
            .arg(QString::number(freeMem, 'f', 1))
            .arg(QString::number(totalMem, 'f', 1));
    resInfo->valueInfo[MHDUIY::deviceRealTimeInfo::MemoryUsed] = int(freeMem / totalMem * 100.0);

    /*存储*/
    command = QString("adb -s %1 shell df -h | grep '% /data'").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    QStringList ll = ret.simplified().split(' ');
    if(ll.size() == 6) {
        resInfo->info[MHDUIY::deviceRealTimeInfo::StorageUsed] = QString("%1/%2")
                .arg(ll.value(3))
                .arg(ll.value(1));
        resInfo->valueInfo[MHDUIY::deviceRealTimeInfo::StorageUsed] = 100-ll.value(4).left(ll.value(4).size() - 1).toInt();
    }
    /*当前活动*/
    command = QString("adb -s %1 shell dumpsys window | grep mCurrentFocus");
    ret = tool.executeCommand(command).simplified();
    if(ret.startsWith("mCurrentFocus=Window", Qt::CaseInsensitive)) {
        QString rightInfo = ret.split("Window{").value(1).replace('}', "");
        QStringList rightInfoItemList = rightInfo.split(' ');
        if(rightInfoItemList.size() == 3) {
            resInfo->info[MHDUIY::deviceRealTimeInfo::WindowsCode] = rightInfoItemList.value(0);
            QStringList activityItem = rightInfoItemList.value(0).split('/');
            if(activityItem.size() == 2) {
                resInfo->info[MHDUIY::deviceRealTimeInfo::CurrentPackage] = activityItem.value(0);
                resInfo->info[MHDUIY::deviceRealTimeInfo::CurrentActivity] = activityItem.value(1);
            }
            else if(activityItem.size() == 1){
                resInfo->info[MHDUIY::deviceRealTimeInfo::CurrentPackage] = "无前台应用";
                resInfo->info[MHDUIY::deviceRealTimeInfo::CurrentActivity] = "无前台应用";
            }
        }
    }


    info = resInfo;
    emit readDeviceInfoFinish(resInfo);
}


UpdateThread *UpdateThread::getInstance(QObject *parent)
{
    if(UpdateThread::instance == nullptr) {
        UpdateThread::instance = new UpdateThread(parent);
    }
    return UpdateThread::instance;
}
