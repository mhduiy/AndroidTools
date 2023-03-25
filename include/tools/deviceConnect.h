#ifndef DEVICECONNECT_H
#define DEVICECONNECT_H

#include <QObject>
#include "myTypes.h"
#include "ADBTools.h"

class DeviceConnect : QObject {
    Q_OBJECT
public:
    explicit DeviceConnect(QObject *parent = nullptr);
    ~DeviceConnect();

    static DeviceConnect *getInstance(QObject *parent = nullptr);

    QVector<MHDUIY::deviceBaceInfo*> getDevices();
    QVector<MHDUIY::deviceBaceInfo *> flashDevices();

    void setCurrentDevice(MHDUIY::deviceBaceInfo *currentInfo);
    void setCurrentDevice(int index);
    QString getCurrentDeviceCode();
    MHDUIY::deviceBaceInfo *getCurrentDevice();

signals:
    void flashDevicesFinish();

private:
    static DeviceConnect *instance;
    QVector<MHDUIY::deviceBaceInfo*> devices;
    MHDUIY::deviceBaceInfo * currentDevice = nullptr;
};

#endif
