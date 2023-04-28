#include "myTypes.h"
using namespace MHDUIY;

QStringList deviceRealTimeInfo::OUTSTR {
    "电池电量",
    "充电电流",
    "电池温度",
    "剩余内存",
    "剩余存储",
    "CPU占用",
    "GPU占用",
    "窗口标识符",
    "当前前台包名",
    "当前前台活动"
};

QStringList deviceDetailsInfo::OUTSTR {
    "厂商",
    "品牌",
    "型号",
    "设备代号",
    "系统信息",
    "安卓版本",
    "CPU信息",
    "屏幕密度",
    "分辨率",
    "序列号"
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
    "上一首",
    "下一首"
};

QStringList mediaControlInfo::CMDSTR {
    "adb -s %1 shell input keyevent 85",
    "adb -s %1 shell input keyevent 86",
    "adb -s %1 shell input keyevent 88",
    "adb -s %1 shell input keyevent 87"
};

QStringList broadcastControlInfo::OUTSTR {
    "网络连接发生变化",
    "屏幕点亮",
    "屏幕熄灭",
    "电量低",
    "电量恢复了",
    "设备启动完毕",
    "存储空间过低",
    "存储空间恢复",
    "安装了新的应用",
    "WiFi连接状态发生变化",
    "电池电量发生变化",
    "系统输入法发生变化",
    "外部电源连接",
    "外部电源断开连接",
    "系统开始休眠",
    "系统停止休眠",
    "插入耳机",
    "卸载外部介质",
    "挂载外部介质",
    "省电模式开启"
};

QStringList broadcastControlInfo::CMDSTR {
    "adb -s %1 shell am broadcast -a android.net.conn.CONNECTIVITY_CHANGE",
    "adb -s %1 shell am broadcast -a android.intent.action.SCREEN_ON",
    "adb -s %1 shell am broadcast -a android.intent.action.SCREEN_OFF",
    "adb -s %1 shell am broadcast -a android.intent.action.BATTERY_LOW",
    "adb -s %1 shell am broadcast -a android.intent.action.BATTERY_OKAY",
    "adb -s %1 shell am broadcast -a android.intent.action.BOOT_COMPLETED",
    "adb -s %1 shell am broadcast -a android.intent.action.DEVICE_STORAGE_LOW",
    "adb -s %1 shell am broadcast -a android.intent.action.DEVICE_STORAGE_OK",
    "adb -s %1 shell am broadcast -a android.intent.action.PACKAGE_ADDED",
    "adb -s %1 shell am broadcast -a android.net.wifi.STATE_CHANGE",
    "adb -s %1 shell am broadcast -a android.intent.action.BATTERY_CHANGED",
    "adb -s %1 shell am broadcast -a android.intent.action.INPUT_METHOD_CHANGED",
    "adb -s %1 shell am broadcast -a android.intent.action.ACTION_POWER_CONNECTED",
    "adb -s %1 shell am broadcast -a android.intent.action.ACTION_POWER_DISCONNECTED",
    "adb -s %1 shell am broadcast -a android.intent.action.DREAMING_STARTED",
    "adb -s %1 shell am broadcast -a android.intent.action.DREAMING_STOPPED",
    "adb -s %1 shell am broadcast -a android.intent.action.HEADSET_PLUG",
    "adb -s %1 shell am broadcast -a android.intent.action.MEDIA_UNMOUNTED",
    "adb -s %1 shell am broadcast -a android.intent.action.MEDIA_MOUNTED",
    "adb -s %1 shell am broadcast -a android.os.action.POWER_SAVE_MODE_CHANGED"
};

QStringList SoftInfo::OUTSTR {
    "软件名",
    "包名",
    "安装时间",
    "安装路径",
    "版本",
    "版本code",
    "目标SDK",
    "最低SDK"
};

QStringList FastRebootInfo::OUTSTR {
    "fastboot重启到系统",
    "fastboot重启到rec",
    "重启fastboot",
    "rec重启到系统",
    "rec重启到fastboot",
    "重启rec"
};

QStringList FastRebootInfo::CMDSTR {
    "",
    "",
    "",
    "",
    "",
    "",
};

QStringList QuickConnItem::websiteNames {
    "XiaoMiROM",
    "PE OS",
    "Pixel OS",
    "fiimeROM",
    "orangefox Recovery"
};

QStringList QuickConnItem::websiteDes {
    "小米官方刷机包集合",
    "PixelExperience类原生系统官网",
    "Pixel OS类原生系统官网",
    "第三方的刷机包及工具集合",
    "橙狐REC官网"
};

QStringList QuickConnItem::websiteStrs {
    "https://xiaomirom.com/",
    "https://get.pixelexperience.org/",
    "https://pixelos.net/",
    "https://mi.fiime.cn/OriginROM/",
    "https://orangefox.download/"
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
