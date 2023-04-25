#ifndef MYTYPES_H
#define MYTYPES_H

#include <QStringList>
#include <QVector>
#include <QMap>

namespace MHDUIY {
    enum class deviceControlCode {
        KeySimulation,
        AdvancedReBoot,
        MediaControl
    };

    //设备实时更新的信息
    struct deviceRealTimeInfo {
        static QStringList OUTSTR;
        enum {
            BatteryLevel = 0,   //电量
            Electricity,        //电流
            BatteryTEMP,        //电池温度
            MemoryUsed,         //内存
            StorageUsed,        //存储
            CPUUsed,            //CPU使用率
            GPUUsed,            //GPU使用率
            TOTAL
        };
        QVector<QString> info;
        QVector<int> valueInfo;
        inline deviceRealTimeInfo():info(TOTAL), valueInfo(TOTAL){}
    };

    //设备详细信息
    struct deviceDetailsInfo {
        static QStringList OUTSTR;
        enum {
            Manufacturer = 0,   //厂商
            DeviceModel,        //型号
            SystemInfo,         //系统
            DeviceCodeName,     //设备代号
            AndroidVersion,     //安卓版本
            CPUInfo,            //CPU信息
            GPUInfo,            //GPU信息
            Resolution,         //分辨率
            PoweredOnTime,      //开机时间
            TOTAL
        };
        QVector<QString> info;
        inline deviceDetailsInfo():info(TOTAL){}
    };

    struct deviceBaceInfo {
        static QStringList OUTSTR;
        enum {
            DeviceCodeName,
            TOTAL
        };
        QVector<QString> info;
        inline deviceBaceInfo():info(TOTAL){}
    };

    //按键模拟
    struct keySimulationInfo {
        static QStringList OUTSTR;
        static QStringList CMDSTR;
        enum {
            MYRETURN = 0,       //返回
            HOME,               //HOME
            MENU,               //菜单
            POWER,              //电源
            inBrightness,       //增加亮度
            deBrightness,       //减小亮度
            inVolume,           //增加音量
            deVolume,           //减小音量
            TOTAL
        };
        inline keySimulationInfo(){}
    };

    //高级重启
    struct advancedRestartInfo {
        static QStringList OUTSTR;
        static QStringList CMDSTR;
        enum {
            POWEROFF = 0,       //关机
            REBOOT,             //重启
            REBOOTTOREC,        //重启到REC
            REBOOTTOFAST,       //重启到FASTBOOT
            TOTAL
        };
        inline advancedRestartInfo(){}
    };

    //媒体控制
    struct mediaControlInfo {
        static QStringList OUTSTR;
        static QStringList CMDSTR;
        enum {
            PLAY = 0,           //播放
            STOP,               //停止
            Previous,           //上一首
            Next,               //下一首
            TOTAL
        };
        inline mediaControlInfo(){}
    };

    //软件包信息
    struct SoftInfo {
        static QStringList OUTSTR;
        enum {
            Name = 0,       //软件名       0
            PackageName,    //包名        1
            InstallTime,    //安装时间     2
            InstallPath,    //安装路径     3
            Version,        //版本        4
            VersionCode,    //版本code    5
            TargetSDK,      //目标SDK     6
            MinSDK,         //最低SDK     7
            TOTAL
        };
        QVector<QString> info;
        inline SoftInfo():info(TOTAL){}
    };

    //刷机-快捷重启
    struct FastRebootInfo {
        static QStringList OUTSTR;
        static QStringList CMDSTR;
        enum {
            FastBootToSys = 0,      //fastboot重启到系统
            FastBootToRec,          //fastboot重启到rec
            FastBootToFastBoot,     //重启fastboot
            RecToSys,               //rec重启到系统
            RecToFastBoot,          //rec重启到fastboot
            RecToRec,               //重启rec
            TOTAL
        };
        inline FastRebootInfo(){}
    };

    struct QuickConnItem {
        static QStringList websiteNames;
        static QStringList websiteDes;
        static QStringList websiteStrs;
    };

    QMap<QString, QString> serializationInformation(QString &info);
}

#endif
