#include "deviceConnect.h"

DeviceConnect *DeviceConnect::instance = nullptr;

DeviceConnect::DeviceConnect(QObject *parent) : QObject (parent)
{

}

DeviceConnect::~DeviceConnect()
{

}

DeviceConnect *DeviceConnect::getInstance(QObject *parent)
{
    if(DeviceConnect::instance == nullptr) {
        DeviceConnect::instance = new DeviceConnect(parent);
    }
    return DeviceConnect::instance;
}

QVector<MHDUIY::deviceBaceInfo *> DeviceConnect::getDevices()
{
    return this->devices;
}

QVector<MHDUIY::deviceBaceInfo *> DeviceConnect::flashDevices()
{
    //释放原有设备内存
    for(int i = 0; i < this->devices.size(); i++) {
        if(nullptr != this->devices[i]) {
            delete this->devices[i];
        }
    }
    this->devices.resize(0);

    ADBTools tool;
    QString ret = tool.executeCommand("adb devices");
    QStringList l = ret.split('\n');

    bool readFlag = false;
    for (QString &s : l) {
        s = s.simplified();
        if(s.isEmpty()) {
            continue;
        }
        if(s.startsWith("*")) {
            return {};
        }
        if(s == "List of devices attached") {
            readFlag = true;
        }
        if(readFlag == true) {  //读取到新设备
            MHDUIY::deviceBaceInfo *info = new MHDUIY::deviceBaceInfo();
            QStringList ll = s.split(' ');
            if(ll.value(1) == "device") {
                qDebug() << ll.value(0);
                info->info[MHDUIY::deviceBaceInfo::DeviceCodeName] = ll.value(0);
                this->devices.push_back(info);
            }
        }
    }
    emit flashDevicesFinish();
    return this->devices;
}

void DeviceConnect::setCurrentDevice(MHDUIY::deviceBaceInfo *currentInfo)
{
    this->currentDevice = currentInfo;
}

void DeviceConnect::setCurrentDevice(int index)
{
    this->currentDevice = this->devices.value(index);
}

QString DeviceConnect::getCurrentDeviceCode()
{
    return this->currentDevice->info[MHDUIY::deviceBaceInfo::DeviceCodeName];
}

MHDUIY::deviceBaceInfo *DeviceConnect::getCurrentDevice()
{
    return this->currentDevice;
}
