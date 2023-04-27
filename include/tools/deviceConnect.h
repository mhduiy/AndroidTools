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
    QVector<MHDUIY::deviceBaceInfo*> flashDevices();
    QVector<MHDUIY::deviceBaceInfo*> flashFastBootDevices();

    void setCurrentDevice(MHDUIY::deviceBaceInfo *currentInfo);
    void setCurrentDevice(int index);
    QString getCurrentDeviceCode();
    MHDUIY::deviceBaceInfo *getCurrentDevice();

    void setCurrentFastBootDevice(MHDUIY::deviceBaceInfo *currentInfo);
    void setCurrentFastBootDevice(int index);
    QString getCurrentFastBootDeviceCode();
    MHDUIY::deviceBaceInfo *getCurrentFastBootDevice();

signals:
    void flashDevicesFinish();

private:
    static DeviceConnect *instance;
    QVector<MHDUIY::deviceBaceInfo*> devices;
    QVector<MHDUIY::deviceBaceInfo*> fastBootDevices;
    MHDUIY::deviceBaceInfo * currentDevice = nullptr;
    MHDUIY::deviceBaceInfo * currentFastBootDevice = nullptr;
};

#endif
