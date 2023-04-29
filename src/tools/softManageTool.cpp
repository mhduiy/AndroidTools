#include "softManageTool.h"
#include "deviceConnect.h"
#include <QDir>
#include <QStandardPaths>
#include <QThread>

SoftManageTool* SoftManageTool::instance = nullptr;

SoftManageTool::SoftManageTool(QObject *parent) : QObject((parent))
{
    QThread *thread = new QThread();
    softTool = SoftTools::getInstance();
    connect(this, &SoftManageTool::installApp, softTool, &SoftTools::installApp);
    connect(this, &SoftManageTool::clearData, softTool, &SoftTools::clearData);
    connect(this, &SoftManageTool::uninstallApp, softTool, &SoftTools::uninstallApp);
    connect(this, &SoftManageTool::extractApp, softTool, &SoftTools::extractApp);
    connect(this, &SoftManageTool::freezeApp, softTool, &SoftTools::freezeApp);
    connect(this, &SoftManageTool::unfreezeApp, softTool, &SoftTools::unfreezeApp);
    softTool->moveToThread(thread);
    thread->start();    //将耗时任务移动到子线程中执行
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
    QString currentDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    switch (flag) {
        case SOFT_TOTAL:
        l = tool.executeCommand(totalCmd.arg(currentDevice)).split('\n');
            break;
        case SOFT_SYS:
        l = tool.executeCommand(sysCmd.arg(currentDevice)).split('\n');
            break;
        case SOFT_THIRD:
        l = tool.executeCommand(thirdCmd.arg(currentDevice)).split('\n');
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
   static MHDUIY::SoftInfo _info;
   QString currentDeviceCode = DeviceConnect::getInstance()->getCurrentDeviceCode();
   QString ret = "I am 360";
   _info.info[MHDUIY::SoftInfo::Name] = ret;
   _info.info[MHDUIY::SoftInfo::PackageName] = packageName;
   QString &&_cmd = QString("adb -s %1 shell dumpsys package %2").arg(currentDeviceCode).arg(packageName);
   QString &&_cmdInfo = tool.executeCommand(_cmd);

   for(QString &qst : _cmdInfo.split('\n')){
       qst = qst.simplified();
       if(qst.startsWith("firstInstallTime", Qt::CaseInsensitive)){
           _info.info[MHDUIY::SoftInfo::InstallTime] = qst.split("=").last();

       }else if(qst.startsWith("resourcePath", Qt::CaseInsensitive)){
           _info.info[MHDUIY::SoftInfo::InstallPath] = qst.split("=").last();

       }else if(qst.startsWith("versionName", Qt::CaseInsensitive)){
           _info.info[MHDUIY::SoftInfo::Version] = qst.split("=").last();

       }else if(qst.startsWith("VersionCode", Qt::CaseInsensitive)){
           _info.info[MHDUIY::SoftInfo::VersionCode] = qst.split(" ").value(0).split("=").last();
           _info.info[MHDUIY::SoftInfo::TargetSDK] = qst.split(" ").value(2).split("=").last();
           _info.info[MHDUIY::SoftInfo::MinSDK] = qst.split(" ").value(1).split("=").last();

       }
   }

   return _info;
}

//发出信号，在子线程中执行
bool SoftManageTool::operateSoft(MHDUIY::OPERATFLAG flag, const QString &packageName)
{
    QString doc_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    switch( flag ){
    case MHDUIY::OP_INSTALL:
        emit installApp(packageName);
        break;
    case MHDUIY::OP_UNINSTALL:
        emit uninstallApp(packageName);
        break;
    case MHDUIY::OP_CLEARDATA:
        emit clearData(packageName);
        break;
    case MHDUIY::OP_EXTRACT:
        emit extractApp(packageName, doc_path + QDir::separator() + packageName + ".apk");
        break;
    case MHDUIY::OP_FREEZE:
        emit freezeApp(packageName);
        break;
    case MHDUIY::OP_UNFREEZE:
        emit unfreezeApp(packageName);
        break;
    default:
        break;
    }
    return true;
}

SoftManageTool *SoftManageTool::getInstance(QObject *parent)
{
    if(SoftManageTool::instance == nullptr) {
        SoftManageTool::instance = new SoftManageTool(parent);
    }
    return SoftManageTool::instance;
}
