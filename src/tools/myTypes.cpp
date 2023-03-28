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
    "adb -s %1 shell input keyevent 4",
    "adb -s %1 shell input keyevent 3",
    "adb -s %1 shell input keyevent 82",
    "adb -s %1 shell input keyevent 26",
    "adb -s %1 shell input keyevent 221",
    "adb -s %1 shell input keyevent 220",
    "adb -s %1 shell input keyevent 24",
    "adb -s %1 shell input keyevent 25"
};

QStringList advancedRestartInfo::OUTSTR {
    "关机",
    "重启",
    "重启到Recovery",
    "重启到FastBoot"
};

QStringList advancedRestartInfo::CMDSTR {
    "adb -s %1 shutdown",
    "adb -s %1 reboot",
    "adb -s %1 reboot recovery",
    "adb -s %1 reboot bootloader"
};

QStringList mediaControlInfo::OUTSTR {
    "播放/暂停",
    "停止",
    "下一首",
    "下一首"
};

QStringList mediaControlInfo::CMDSTR {
    "adb -s %1 shell input keyevent 85",
    "adb -s %1 shell input keyevent 86",
    "adb -s %1 shell input keyevent 88",
    "adb -s %1 shell input keyevent 87"
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
