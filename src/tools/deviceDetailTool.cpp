#include "deviceDetailTool.h"

DeviceDetailTool *DeviceDetailTool::instance = nullptr;

DeviceDetailTool::DeviceDetailTool(QObject *parent) : QObject (parent)
{
    this->info = nullptr;
}

DeviceDetailTool::~DeviceDetailTool()
{

}

DeviceDetailTool *DeviceDetailTool::getInstance(QObject *parent)
{
    if(DeviceDetailTool::instance == nullptr) {
        DeviceDetailTool::instance = new DeviceDetailTool(parent);
    }
    return DeviceDetailTool::instance;
}

MHDUIY::deviceDetailsInfo *DeviceDetailTool::flashInfo()
{
    if(nullptr != this->info) {
        delete this->info;
    }
    MHDUIY::deviceDetailsInfo *res = new MHDUIY::deviceDetailsInfo();
    QString currentDeviceCode = DeviceConnect::getInstance()->getCurrentDeviceCode();

    /*厂商*/
    QString command = QString("adb -s %1 shell getprop ro.product.brand").arg(currentDeviceCode);
    QString ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::Manufacturer] = ret;
    /*型号*/
    command = QString("adb -s %1 shell getprop ro.product.model").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::DeviceModel] = ret;
    /*设备代号*/
    command = QString("adb -s %1 shell getprop ro.product.name").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::DeviceCodeName] = ret;
    /*安卓版本*/
    command = QString("adb -s %1 shell getprop ro.build.version.release").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::AndroidVersion] = ret;
    /*分辨率*/
    command = QString("adb -s %1 shell wm size").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::Resolution] = ret.split(' ').last();
    /*开机时间*/

    emit readDeviceInfoFinish(res);
    this->info = res;
    return res;
}
