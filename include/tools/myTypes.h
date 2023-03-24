#ifndef MYTYPES_H
#define MYTYPES_H

#include <QStringList>
#include <QVector>

namespace JKB {
    struct DeviceInfo {
        static QStringList OutputStr;
        enum {
            BatteryLevel = 0,
            BatteryTEMP,
            MemoryCapacity,
            MemoryUsed,
            TOTAL
        };
        QVector<QString> info;
        inline DeviceInfo():info(TOTAL){}
    };
}

#endif
