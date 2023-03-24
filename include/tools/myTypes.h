#ifndef MYTYPES_H
#define MYTYPES_H

#include <QStringList>
#include <QVector>

namespace MHDUIY {
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
}

#endif
