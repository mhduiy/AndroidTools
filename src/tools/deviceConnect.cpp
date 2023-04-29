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
    for (QString s : l) {
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
            QString deviceMode = ll.value(1);
            if(deviceMode.contains("device", Qt::CaseInsensitive) || deviceMode.contains("recovery", Qt::CaseInsensitive)) {
                qDebug() << ll.value(0);
                info->info[MHDUIY::deviceBaceInfo::DeviceCodeName] = ll.value(0);
                info->info[MHDUIY::deviceBaceInfo::DeviceMode] = deviceMode;
                this->devices.push_back(info);
            }
        }
    }
    emit flashDevicesFinish();
    return this->devices;
}

QVector<MHDUIY::deviceBaceInfo *> DeviceConnect::flashFastBootDevices()
{
    //释放原有设备内存
    for(int i = 0; i < this->fastBootDevices.size(); i++) {
        if(nullptr != this->fastBootDevices[i]) {
            delete this->fastBootDevices[i];
        }
    }
    this->fastBootDevices.resize(0);
    QVector<MHDUIY::deviceBaceInfo *> result;

    ADBTools tool;
    QString ret = tool.executeCommand("fastboot devices");
    QStringList retInfoList = ret.split('\n');
    for(QString &lineInfo : retInfoList) {
        QStringList lineInfoList = lineInfo.simplified().split(' ');
        if(lineInfoList.value(1) == "fastboot") { //读取到已连接的设备
            if(lineInfo.isEmpty()) {continue;}
            MHDUIY::deviceBaceInfo *deviceInfo = new MHDUIY::deviceBaceInfo();
            deviceInfo->info[MHDUIY::deviceBaceInfo::DeviceCodeName] = lineInfoList.value(0);
            deviceInfo->info[MHDUIY::deviceBaceInfo::DeviceMode] = lineInfoList.value(1);
            result.push_back(deviceInfo);
            qDebug() << lineInfoList.value(0);
        }
    }
    this->fastBootDevices = result;
    return result;
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
    if(nullptr == this->currentDevice) {
        return "";
    }
    return this->currentDevice->info[MHDUIY::deviceBaceInfo::DeviceCodeName];
}

MHDUIY::deviceBaceInfo *DeviceConnect::getCurrentDevice()
{
    return this->currentDevice;
}

void DeviceConnect::setCurrentFastBootDevice(MHDUIY::deviceBaceInfo *currentInfo)
{
    this->currentFastBootDevice = currentInfo;
}

void DeviceConnect::setCurrentFastBootDevice(int index)
{
    this->currentFastBootDevice = this->fastBootDevices.value(index);
}

QString DeviceConnect::getCurrentFastBootDeviceCode()
{
    if(nullptr == this->currentFastBootDevice) {
        return "";
    }
    return this->currentFastBootDevice->info[MHDUIY::deviceBaceInfo::DeviceCodeName];

}

MHDUIY::deviceBaceInfo *DeviceConnect::getCurrentFastBootDevice()
{
    return this->currentFastBootDevice;
}
