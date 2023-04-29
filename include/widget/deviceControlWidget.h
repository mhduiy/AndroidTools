#ifndef DEVICECONTROLWIDGET_H
#define DEVICECONTROLWIDGET_H

#include <DWidget>
#include <DPushButton>
#include <DSpinBox>
#include "myTypes.h"
#include "ADBTools.h"
#include "deviceControlItem.h"
#include "deviceDetailTool.h"
#include "mybacewidget.h"

DWIDGET_USE_NAMESPACE

enum BatteryControlFlag {
    Bty_SetLevel,
    Bty_StartCharge,
    Bty_StopCharge,
    Bty_BreakCharge,
    Bty_ResetCharge,
    TOTAL
};

class DeviceControlWidget : public MyBaceWidget {
    Q_OBJECT
public:
    explicit DeviceControlWidget(QWidget *parent = nullptr);
    ~DeviceControlWidget();

    void initUI();
    void responseBtn(MHDUIY::deviceControlCode code, int i);    //响应按钮

//signals:
//    void sendMsgToMainWindow(const QString &msg);

private:
    void setDefaultDpiData(MHDUIY::deviceDetailsInfo *);
    void responseBtn(BatteryControlFlag flag);

private:
    QVector<DPushButton*> keySimulationBtns;    //按键模拟按钮组
    QVector<DPushButton*> advancedRestartBtns;  //高级重启按钮组
    QVector<DPushButton*> mediaControlBtns;     //媒体控制按钮组
    QVector<DPushButton*> broadcastControlBtns; //广播控制按钮组

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
    //电量伪装
    DeviceControlItem *BtyCamouflageControl;
    DSpinBox *BtyLevelEdit;
    DPushButton *setBtyLevelBtn;
    DPushButton *startChargeBtn;
    DPushButton *stopChargeBtn;
    DPushButton *breakChargeBtn;
    DPushButton *resetChargeBtn;

    ADBTools tool;
};


#endif
