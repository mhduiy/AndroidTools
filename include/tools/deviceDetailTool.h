#ifndef DEVICEDETAILTOOL_H
#define DEVICEDETAILTOOL_H

#include <QObject>
#include "myTypes.h"
#include "ADBTools.h"
#include "deviceConnect.h"

class DeviceDetailTool : public QObject{
    Q_OBJECT
public:
    explicit DeviceDetailTool(QObject *parent = nullptr);
    ~DeviceDetailTool();
    static DeviceDetailTool* getInstance(QObject *parent = nullptr);
    MHDUIY::deviceDetailsInfo *flashInfo();
    MHDUIY::deviceDetailsInfo *getInfo();

signals:
    void readDeviceInfoFinish(MHDUIY::deviceDetailsInfo *info);

private:
    MHDUIY::deviceDetailsInfo *info;
    static DeviceDetailTool *instance;
    ADBTools tool;
};

#endif
