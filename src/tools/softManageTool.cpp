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
   //static QString getInstance = "adb -s %1 shell dumpsys package";

   static MHDUIY::SoftInfo _info;
   // MHDUIY::deviceDetailsInfo *res = new MHDUIY::deviceDetailsInfo();
   QString currentDeviceCode = DeviceConnect::getInstance()->getCurrentDeviceCode();

   /*软件名0*/
//   QString getInstance = QString("adb -s %1 shell dumpsys package").arg(currentDeviceCode);
//   QString ret = tool.executeCommand(getInstance).simplified();
   QString ret = "I am 360";
   _info.info[MHDUIY::SoftInfo::Name] = ret;
//   qDebug() << "index.()";

   /*包名1*/
//   getInstance = QString("adb -s %1 shell dumpsys package").arg(currentDeviceCode);
//   ret = tool.executeCommand(getInstance).simplified();
   _info.info[MHDUIY::SoftInfo::PackageName] = packageName;
//   qDebug() << "ind1";

//   /*安装时间2*/
//   QString _cmd = QString("adb -s %1 shell dumpsys package %2|grep -i 'firstInstallTime'").arg(currentDeviceCode).arg(packageName);
//   ret = tool.executeCommand(_cmd).simplified();
//   ret = ret.split("=").last();
//   _info.info[MHDUIY::SoftInfo::InstallTime] = ret;

//   /*安装路径3*/
//   _cmd = QString("adb -s %1 shell dumpsys package %2|grep -i 'resourcePath'").arg(currentDeviceCode).arg(packageName);
//   ret = tool.executeCommand(_cmd).simplified();
//   ret = ret.split("=").last();
//   _info.info[MHDUIY::SoftInfo::InstallPath] = ret;

//   /*版本4*/
//   _cmd = QString("adb -s %1 shell dumpsys package %2|grep -i 'versionName'").arg(currentDeviceCode).arg(packageName);
//   ret = tool.executeCommand(_cmd).simplified();
//   ret = ret.split("=").last();
//   _info.info[MHDUIY::SoftInfo::Version] = ret;

//   /*版本code5*/
//   _cmd = QString("adb -s %1 shell dumpsys package %2|grep -i 'VersionCode'").arg(currentDeviceCode).arg(packageName);
//   ret = tool.executeCommand(_cmd).simplified();
//   QStringList qslist = ret.split(" ");
//   _info.info[MHDUIY::SoftInfo::VersionCode] = qslist.value(0).split("=").last();



//   /*目标sdk6*/
//   _info.info[MHDUIY::SoftInfo::TargetSDK] = qslist.value(2).split("=").last();

//   /*最低sdk7*/
//   _info.info[MHDUIY::SoftInfo::MinSDK] = qslist.value(1).split("=").last();

//   ret = tool.executeCommand(_cmd).simplified();
//   ret = ret.split("=").last();
//   _info.info[MHDUIY::SoftInfo::InstallTime] = ret;


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

/*
    struct SoftInfo {
        static QStringList OUTSTR;
        enum {
            Name = 0,       //软件名
            PackageName,    //包名
            InstallTime,    //安装时间
            InstallPath,    //安装路径
            Version,        //版本
            VersionCode,    //版本code
            TargetSDK,      //目标SDK
            MinSDK,         //最低SDK
            TOTAL
        };
        QVector<QString> info;
        inline SoftInfo():info(TOTAL){}
    };
*/

bool SoftManageTool::operateSoft(OPERATFLAG flag, const QString &packageName)
{
    //if(packageName == ''){}
    switch( flag ){
    case OP_INSTALL:
        break;
    case OP_UNINSTALL:
        break;
    case OP_CLEARDATA:
        break;
    case OP_EXTRACT:
        qDebug() << packageName;
        qDebug() << "1";
        break;
    default:
        break;

    }

    return true;
}

//enum OPERATFLAG {
//    OP_INSTALL = 0, //安装
//    OP_UNINSTALL,   //卸载
//    OP_CLEARDATA,   //清除数据
//    OP_EXTRACT      //提取

SoftManageTool *SoftManageTool::getInstance(QObject *parent)
{
    if(SoftManageTool::instance == nullptr) {
        SoftManageTool::instance = new SoftManageTool(parent);
    }
    return SoftManageTool::instance;
}
