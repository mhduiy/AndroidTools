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
    QString command = QString("adb -s %1 shell getprop ro.product.manufacturer").arg(currentDeviceCode);
    QString ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::Manufacturer] = ret;
    /*品牌*/
    command = QString("adb -s %1 shell getprop ro.product.brand").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::DeviceBrand] = ret;
    /*型号*/
    command = QString("adb -s %1 shell getprop ro.product.model").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::DeviceModel] = ret;
    /*设备代号*/
    command = QString("adb -s %1 shell getprop ro.product.product.device").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::DeviceCodeName] = ret;
    /*系统信息*/
    command = QString("adb -s %1 shell getprop ro.custom.version").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::SystemInfo] = ret;

    /*安卓版本*/
    command = QString("adb -s %1 shell getprop ro.build.version.release").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::AndroidVersion] = ret;
    /*CPU*/
    command = QString("adb -s %1 shell cat /proc/cpuinfo").arg(currentDeviceCode);
    ret = tool.executeCommand(command);
    auto serialInfo = MHDUIY::serializationInformation(ret);
    res->info[MHDUIY::deviceDetailsInfo::CPUInfo] = serialInfo["Hardware"];
    /*Dpi*/
    command = QString("adb -s %1 shell getprop ro.sf.lcd_density").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::Dpi] = ret.simplified();
    /*分辨率*/
    command = QString("adb -s %1 shell wm size").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::Resolution] = ret.split(' ').last();
    /*序列号*/
    command = QString("adb -s %1 shell getprop ro.serialno").arg(currentDeviceCode);
    ret = tool.executeCommand(command).simplified();
    res->info[MHDUIY::deviceDetailsInfo::SerialNum] = ret.split(' ').value(0);

    /*
ro.product.model
ro.product.manufacturer
ro.product.brand
*/

    emit readDeviceInfoFinish(res);
    this->info = res;
    return res;
}

MHDUIY::deviceDetailsInfo *DeviceDetailTool::getInfo()
{
    return this->info;
}
