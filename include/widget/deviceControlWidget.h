#ifndef DEVICECONTROLWIDGET_H
#define DEVICECONTROLWIDGET_H

#include <DWidget>
#include <DPushButton>
#include "myTypes.h"

DWIDGET_USE_NAMESPACE

class DeviceControlWidget : public DWidget {
    Q_OBJECT
public:
    explicit DeviceControlWidget(QWidget *parent = nullptr);
    ~DeviceControlWidget();

    void initUI();

private:
    QVector<DPushButton*> keySimulationBtns;    //按键模拟按钮组
    QVector<DPushButton*> advancedRestartBtns;  //高级重启按钮组
    QVector<DPushButton*> mediaControlBtns;     //媒体控制按钮组
};


#endif
