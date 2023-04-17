#include "softManageTool.h"
#include "deviceConnect.h"

SoftManageTool* SoftManageTool::instance = nullptr;

SoftManageTool::SoftManageTool(QObject *parent) : QObject((parent))
{

}

SoftManageTool::~SoftManageTool()
{

}

QStringList SoftManageTool::getSoftList(SOFTFLAG flag)
{
    static QString totalCmd = "adb -s %1 shell pm list packages";
    static QString sysCmd = "adb -s %1 shell pm list packages -s";
    static QString thirdCmd = "adb -s %1 shell pm list packages -3";
    QStringList l;
    QStringList res;
    switch (flag) {
        case SOFT_TOTAL:
        l = tool.executeCommand(totalCmd.arg(DeviceConnect::getInstance()->getCurrentDeviceCode())).split('\n');
            break;
        case SOFT_SYS:
        l = tool.executeCommand(sysCmd.arg(DeviceConnect::getInstance()->getCurrentDeviceCode())).split('\n');
            break;
        case SOFT_THIRD:
        l = tool.executeCommand(thirdCmd.arg(DeviceConnect::getInstance()->getCurrentDeviceCode())).split('\n');
            break;
        default:
            break;
    }
    for(QString& lineInfo : l) {
        if(lineInfo.isEmpty()) {continue;}
        res.push_back(lineInfo.split(':').last());
    }
    return res;
}

MHDUIY::SoftInfo &SoftManageTool::getSoftInfo(const QString &packageName)
{

}

bool SoftManageTool::operateSoft(OPERATFLAG flag, const QString &packageName)
{
    return true;
}

SoftManageTool *SoftManageTool::getInstance(QObject *parent)
{
    if(SoftManageTool::instance == nullptr) {
        SoftManageTool::instance = new SoftManageTool(parent);
    }
    return SoftManageTool::instance;
}
