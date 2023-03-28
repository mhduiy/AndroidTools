#include "myTypes.h"
using namespace MHDUIY;

QStringList deviceRealTimeInfo::OUTSTR {
    "电池电量",
    "充电电流",
    "电池温度",
    "剩余内存",
    "剩余存储",
    "CPU占用",
    "GPU占用"
};

QStringList deviceDetailsInfo::OUTSTR {
    "厂商",
    "型号",
    "系统",
    "设备代号",
    "安卓版本",
    "CPU信息",
    "GPU信息",
    "分辨率",
    "开机时间"
};

QStringList deviceBaceInfo::OUTSTR {
    "设备代码"
};

QStringList keySimulationInfo::OUTSTR {
    "返回",
    "HOME",
    "菜单",
    "电源",
    "增加亮度",
    "减小亮度",
    "增加音量",
    "减小音量"
};

QStringList keySimulationInfo::CMDSTR {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
};

QStringList advancedRestartInfo::OUTSTR {
    "关机",
    "重启",
    "重启到Recovery",
    "重启到FastBoot"
};

QStringList advancedRestartInfo::CMDSTR {
    "",
    "",
    "",
    ""
};

QStringList mediaControlInfo::OUTSTR {
    "播放/暂停",
    "停止",
    "下一首",
    "下一首"
};

QStringList mediaControlInfo::CMDSTR {
    "",
    "",
    "",
    ""
};

QMap<QString, QString> MHDUIY::serializationInformation(QString &info)
{
    QMap<QString, QString> res;
    QStringList l = info.split('\n');
    for (QString &s : l) {
        s = s.simplified();
        if(s.isEmpty()) {   //过滤空行
            continue;
        }
        QStringList ll = s.split(':');
        res.insert(ll.value(0).simplified(), ll.value(1).simplified());
    }
    return res;
}
