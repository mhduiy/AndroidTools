#ifndef DEVICECONTROLWIDGET_H
#define DEVICECONTROLWIDGET_H

#include <DWidget>
#include <DPushButton>
#include <DSpinBox>
#include "myTypes.h"
#include "ADBTools.h"
#include "deviceControlItem.h"
#include "deviceDetailTool.h"

DWIDGET_USE_NAMESPACE

class DeviceControlWidget : public DWidget {
    Q_OBJECT
public:
    explicit DeviceControlWidget(QWidget *parent = nullptr);
    ~DeviceControlWidget();

    void initUI();
    void responseBtn(MHDUIY::deviceControlCode code, int i);    //响应按钮

signals:
    void sendMsgToMainWindow(const QString &msg);

private:
    void setDefaultDpiData(MHDUIY::deviceDetailsInfo *);

private:
    QVector<DPushButton*> keySimulationBtns;    //按键模拟按钮组
    QVector<DPushButton*> advancedRestartBtns;  //高级重启按钮组
    QVector<DPushButton*> mediaControlBtns;     //媒体控制按钮组

    //dpi
    DeviceControlItem *dpiControl;
    DSpinBox *dpiEdit;
    DSpinBox *resolutionEditw;
    DSpinBox *resolutionEdith;
    DPushButton *dpiResetBtn;
    DPushButton *dpiSetBtn;
    //输入文本
    DeviceControlItem *inputControl;
    DLineEdit *inputEdit;
    DPushButton *inputBtn;
    //执行脚本
    DeviceControlItem *scriptControl;
    DLineEdit *scriptEdit;
    DPushButton *scriptSelectBtn;
    DPushButton *scriptBtn;


    ADBTools tool;
};


#endif
