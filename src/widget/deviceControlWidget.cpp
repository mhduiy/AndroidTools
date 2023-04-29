#include "deviceControlWidget.h"
#include <DGroupBox>
#include <QLayout>
#include <QDebug>
#include <DLabel>
#include <DSuggestButton>
#include "deviceConnect.h"
#include <DDialog>
#include <DScrollArea>

DeviceControlWidget::DeviceControlWidget(QWidget *parent) : MyBaceWidget(parent)
{
    initUI();
}

DeviceControlWidget::~DeviceControlWidget()
{

}

void DeviceControlWidget::initUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();

//    /* test */
//    rightContorlLayout->addWidget(new DPushButton("占位"));

    DWidget *keySimulationBoxW = new DWidget(this);
    DWidget *advancedRestartBoxW = new DWidget(this);
    DWidget *mediaControlBoxW = new DWidget(this);
    DWidget *broadcastControlBoxW = new DWidget(this);

    DeviceControlItem *keySimulationBox = new DeviceControlItem(keySimulationBoxW);
    DeviceControlItem *advancedRestartBox = new DeviceControlItem(advancedRestartBoxW);
    DeviceControlItem *mediaControlBox = new DeviceControlItem(mediaControlBoxW);
    DeviceControlItem *broadcastControlBox = new DeviceControlItem(broadcastControlBoxW);

    QGridLayout *keySimulationLayout = new QGridLayout(keySimulationBoxW);
    QGridLayout *advancedRestartLayout = new QGridLayout(advancedRestartBoxW);
    QGridLayout *mediaControlLayout = new QGridLayout(mediaControlBoxW);
    QGridLayout *broadcastControlLayout = new QGridLayout(broadcastControlBoxW);

    keySimulationLayout->setSpacing(20);
    advancedRestartLayout->setSpacing(20);
    mediaControlLayout->setSpacing(20);
    broadcastControlLayout->setSpacing(20);

    keySimulationBox->setTitle("按键模拟");
    advancedRestartBox->setTitle("高级重启");
    mediaControlBox->setTitle("媒体控制");
    broadcastControlBox->setTitle("广播控制");

    keySimulationBox->setDescribe("可以实现模拟手机按下某个按键");
    advancedRestartBox->setDescribe("重启到对应位置，这个重启可能会没有动画提示");
    mediaControlBox->setDescribe("控制手机的多媒体播放状态，例如音乐或者视频");
    broadcastControlBox->setDescribe("发送特定全局广播到手机，模拟某些状态的发生");

    //添加按钮，设置按钮响应
    for(int i = 0; i < MHDUIY::keySimulationInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::keySimulationInfo::OUTSTR[i]);
        if(i != 0 && i % 4 == 0) {
            j++;
        }
        keySimulationLayout->addWidget(btn, j, i % 4);
        keySimulationBtns.push_back(btn);
        connect(btn, &DPushButton::clicked, this, [this, i](){
            this->responseBtn(MHDUIY::deviceControlCode::KeySimulation, i);
        });
    }

    for(int i = 0; i < MHDUIY::advancedRestartInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::advancedRestartInfo::OUTSTR[i]);
        if(i != 0 && i % 2 == 0) {
            j++;
        }
        advancedRestartLayout->addWidget(btn, j, i % 2);
        advancedRestartBtns.push_back(btn);
        connect(btn, &DPushButton::clicked, this, [this, i](){
            this->responseBtn(MHDUIY::deviceControlCode::AdvancedReBoot, i);
        });
    }

    for(int i = 0; i < MHDUIY::mediaControlInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::mediaControlInfo::OUTSTR[i]);
        if(i != 0 && i % 2 == 0) {
            j++;
        }
        mediaControlLayout->addWidget(btn, j, i % 2);
        mediaControlBtns.push_back(btn);
        connect(btn, &DPushButton::clicked, this, [this, i](){
            this->responseBtn(MHDUIY::deviceControlCode::MediaControl, i);
        });
    }

    for(int i = 0; i < MHDUIY::broadcastControlInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::broadcastControlInfo::OUTSTR[i]);
        if(i != 0 && i % 2 == 0) {
            j++;
        }
        broadcastControlLayout->addWidget(btn, j, i % 2);
        broadcastControlBtns.push_back(btn);
        connect(btn, &DPushButton::clicked, this, [this, i](){
            this->responseBtn(MHDUIY::deviceControlCode::broadcastControl, i);
        });
    }


    /*dpi&分辨率设置*/
    DWidget *dpiControlW  = new DWidget();
    dpiControl = new DeviceControlItem(dpiControlW);
    dpiControl->setTitle("DPI&分辨率");
    dpiControl->setDescribe("设置dpi和分辨率可能会导致设备显示异常");
    QVBoxLayout *dpiLayout = new QVBoxLayout(dpiControlW);

    QHBoxLayout *dpiEdLayout = new QHBoxLayout();
    dpiEdit = new DSpinBox();
    dpiEdLayout->addWidget(new DLabel("DPI: "));
    dpiEdLayout->addWidget(dpiEdit);

    QHBoxLayout *resuEdLayout = new QHBoxLayout();
    resolutionEditw = new DSpinBox();
    resolutionEdith = new DSpinBox();

    resolutionEditw->setFixedWidth(100);
    resolutionEdith->setFixedWidth(100);
    dpiEdit->setFixedWidth(100);

    resolutionEditw->setEnabledEmbedStyle(true);
    resolutionEdith->setEnabledEmbedStyle(true);
    dpiEdit->setEnabledEmbedStyle(true);

    dpiEdit->setMaximum(10000);
    resolutionEditw->setMaximum(10000);
    resolutionEdith->setMaximum(10000);

    DLabel *resolutionChat = new DLabel("x");
    resolutionChat->setFixedWidth(10);
    resolutionChat->setAlignment(Qt::AlignCenter);

    QHBoxLayout *resolutionLineEditLayout = new QHBoxLayout();
    resolutionLineEditLayout->addWidget(resolutionEditw);
    resolutionLineEditLayout->addWidget(resolutionChat);
    resolutionLineEditLayout->addWidget(resolutionEdith);

    resuEdLayout->addWidget(new DLabel("分辨率: "));
    resuEdLayout->addLayout(resolutionLineEditLayout, Qt::AlignRight);

    QHBoxLayout *dpiBtnLayout = new QHBoxLayout();
    dpiResetBtn = new DPushButton("恢复");
    dpiSetBtn = new DSuggestButton("设置");
    dpiBtnLayout->addWidget(dpiResetBtn);
    dpiBtnLayout->addWidget(dpiSetBtn);

    dpiLayout->addLayout(dpiEdLayout);
    dpiLayout->addLayout(resuEdLayout);
    dpiLayout->addLayout(dpiBtnLayout);
    connect(DeviceDetailTool::getInstance(), &DeviceDetailTool::readDeviceInfoFinish, this, &DeviceControlWidget::setDefaultDpiData);
    connect(dpiSetBtn, &DPushButton::clicked, [this](){

        if(this->dpiEdit->text().isEmpty()) {
            this->dpiEdit->showAlertMessage("信息不完整");
        }
        if(this->resolutionEditw->text().isEmpty()) {
            this->resolutionEditw->showAlertMessage("信息不完整");
        }
        if(this->resolutionEdith->text().isEmpty()) {
            this->resolutionEdith->showAlertMessage("信息不完整");
        }
        QString currentDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
        if(currentDevice.isEmpty()) {
            emit this->sendMsgToMainWindow("没有连接任何设备");
            return;
        }
        QString dpiStr = dpiEdit->text();
        QString xStr = resolutionEditw->text();
        QString yStr = resolutionEdith->text();
        QString sizeCommand = QString("adb -s %1 shell wm size %2x%3").arg(currentDevice).arg(xStr).arg(yStr);
        QString dpiCommand = QString("adb -s %1 shell wm density %2").arg(currentDevice).arg(dpiStr);
        tool.executeCommand(sizeCommand);
        tool.executeCommand(dpiCommand);
        emit this->sendMsgToMainWindow("设置成功");
    });

    connect(dpiResetBtn, &DPushButton::clicked, [this](){
        QString currentDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
        if(currentDevice.isEmpty()) {
            emit this->sendMsgToMainWindow("没有连接任何设备");
            return;
        }
        QString sizeCommand = QString("adb -s %1 shell wm size reset").arg(DeviceConnect::getInstance()->getCurrentDeviceCode());
        QString dpiCommand = QString("adb -s %1 shell wm density reset").arg(DeviceConnect::getInstance()->getCurrentDeviceCode());
        tool.executeCommand(sizeCommand);
        tool.executeCommand(dpiCommand);
        emit this->sendMsgToMainWindow("恢复成功");
        DeviceDetailTool::getInstance()->flashInfo();
    });
    /*输入文本*/
    DWidget *inputW = new DWidget();
    inputControl = new DeviceControlItem(inputW);
    inputControl->setTitle("文本输入");
    inputControl->setDescribe("在焦点处于某文本框时，可以控制输入文本");

    QVBoxLayout *inputLayout = new QVBoxLayout(inputW);
    QHBoxLayout *inputEdLayout = new QHBoxLayout();
    inputEdit = new DLineEdit();
    inputEdLayout->addWidget(new DLabel("文本: "));
    inputEdLayout->addWidget(inputEdit);
    inputBtn = new DSuggestButton("发送");

    connect(inputBtn, &DPushButton::clicked, [this](){
        QString inputStr = inputEdit->text();
        if(inputStr.isEmpty()) {
            emit this->inputEdit->showAlertMessage("请输入信息");
            return;
        }
        QString command = QString("adb -s %1 shell input text '%2'").arg(DeviceConnect::getInstance()->getCurrentDeviceCode()).arg(inputStr);
        tool.executeCommand(command);
        emit this->inputEdit->showAlertMessage("发送成功");
    });

    inputLayout->addLayout(inputEdLayout);
    inputLayout->addWidget(inputBtn);
    /*执行脚本*/
    DWidget *scriptW = new DWidget();
    scriptControl = new DeviceControlItem(scriptW);
    scriptControl->setTitle("执行脚本");
    scriptControl->setDescribe("选择一个脚本，发送到设备执行");

    QVBoxLayout *scriptLayout = new QVBoxLayout(scriptW);
    QHBoxLayout *scriptEdLayout = new QHBoxLayout();
    scriptEdit = new DLineEdit();
    scriptSelectBtn = new DSuggestButton("选择");
    scriptBtn = new DSuggestButton("执行");

    scriptEdLayout->addWidget(new DLabel("脚本路径"));
    scriptEdLayout->addWidget(scriptEdit);
    scriptEdLayout->addWidget(scriptSelectBtn);

    scriptLayout->addLayout(scriptEdLayout);
    scriptLayout->addWidget(scriptBtn);
    /*电量伪装*/
    DWidget *btyCamouflageW = new DWidget(this);
    BtyCamouflageControl = new DeviceControlItem(btyCamouflageW);
    BtyCamouflageControl->setTitle("电量伪装");
    BtyCamouflageControl->setDescribe("模拟手机的电池或者充电状态");
    QGridLayout *btyCamouflageLayout = new QGridLayout(btyCamouflageW);
    btyCamouflageLayout->setSpacing(20);
    BtyLevelEdit = new DSpinBox();
    setBtyLevelBtn = new DPushButton("模拟电量");
    startChargeBtn = new DPushButton("模拟开始充电");
    stopChargeBtn = new DPushButton("模拟插上不充电");
    breakChargeBtn = new DPushButton("模拟断开充电");
    resetChargeBtn = new DPushButton("恢复状态");
    BtyLevelEdit->setMaximum(100);
    BtyLevelEdit->setMinimum(0);
    BtyLevelEdit->setValue(100);
    BtyLevelEdit->setEnabledEmbedStyle(true);

    btyCamouflageLayout->addWidget(BtyLevelEdit, 0, 0);
    btyCamouflageLayout->addWidget(setBtyLevelBtn, 0, 1);
    btyCamouflageLayout->addWidget(startChargeBtn, 1, 0);
    btyCamouflageLayout->addWidget(stopChargeBtn, 1, 1);
    btyCamouflageLayout->addWidget(breakChargeBtn, 2, 0);
    btyCamouflageLayout->addWidget(resetChargeBtn, 2, 1);

    connect(setBtyLevelBtn, &DPushButton::clicked, [this](){this->responseBtn(Bty_SetLevel);});
    connect(startChargeBtn, &DPushButton::clicked, [this](){this->responseBtn(Bty_StartCharge);});
    connect(stopChargeBtn, &DPushButton::clicked, [this](){this->responseBtn(Bty_StopCharge);});
    connect(breakChargeBtn, &DPushButton::clicked, [this](){this->responseBtn(Bty_BreakCharge);});
    connect(resetChargeBtn, &DPushButton::clicked, [this](){this->responseBtn(Bty_ResetCharge);});

    DScrollArea *leftArea = new DScrollArea();
    DScrollArea *rightArea = new DScrollArea();
    DWidget *leftW = new DWidget();
    DWidget *rightW = new DWidget();
    QVBoxLayout *leftKeyLayout = new QVBoxLayout(leftW);
    QVBoxLayout *rightContorlLayout = new QVBoxLayout(rightW);

    leftArea->setWidgetResizable(true);
    rightArea->setWidgetResizable(true);

    leftKeyLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    rightContorlLayout->setAlignment(Qt::AlignTop);

    leftKeyLayout->addWidget(keySimulationBox);
    leftKeyLayout->addWidget(advancedRestartBox);
    leftKeyLayout->addWidget(mediaControlBox);
    leftKeyLayout->addWidget(broadcastControlBox);
    rightContorlLayout->addWidget(dpiControl);
    rightContorlLayout->addWidget(inputControl);
    rightContorlLayout->addWidget(scriptControl);
    rightContorlLayout->addWidget(BtyCamouflageControl);
    leftArea->setWidget(leftW);
    rightArea->setWidget(rightW);
    mainLayout->addWidget(leftArea,4);
    mainLayout->addWidget(rightArea,3);
    this->setLayout(mainLayout);
}

void DeviceControlWidget::responseBtn(MHDUIY::deviceControlCode code, int i)
{
    QString currentDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    if(currentDevice.isEmpty()) {
        emit sendMsgToMainWindow("没有连接任何设备");
        return;
    }
    switch (code) {
        case MHDUIY::deviceControlCode::KeySimulation:
            tool.executeCommand(MHDUIY::keySimulationInfo::CMDSTR[i]
                                .arg(currentDevice));
            emit sendMsgToMainWindow(QString("已触发 %1").arg(MHDUIY::keySimulationInfo::OUTSTR[i]));
            break;
        case MHDUIY::deviceControlCode::AdvancedReBoot:
    {
            DDialog dlg("提示", "确定要执行此操作吗?");
            dlg.addButton("是", true, DDialog::ButtonWarning);
            dlg.addButton("否", false, DDialog::ButtonNormal);
            // dlg.setIcon(QIcon::fromTheme("dialog-inform ation"));
            // dlg.setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning));
            dlg.setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation));
            int ret = dlg.exec();
            qDebug() << ret;
            if(ret != 0) {  //选择了否或者关闭窗口
                return;
            }
            tool.executeCommand(MHDUIY::advancedRestartInfo::CMDSTR[i]
                                .arg(currentDevice));
            emit sendMsgToMainWindow(QString("已触发 %1").arg(MHDUIY::advancedRestartInfo::OUTSTR[i]));
            break;
    }
        case MHDUIY::deviceControlCode::MediaControl:
            tool.executeCommand(MHDUIY::mediaControlInfo::CMDSTR[i]
                                .arg(currentDevice));
            emit sendMsgToMainWindow(QString("已触发 %1").arg(MHDUIY::mediaControlInfo::OUTSTR[i]));
            break;
        case MHDUIY::deviceControlCode::broadcastControl:
            tool.executeCommand(MHDUIY::broadcastControlInfo::CMDSTR[i]
                                .arg(currentDevice));
            emit sendMsgToMainWindow(QString("已触发 %1").arg(MHDUIY::broadcastControlInfo::OUTSTR[i]));
            break;
    }
}

void DeviceControlWidget::setDefaultDpiData(MHDUIY::deviceDetailsInfo * info)
{
    if(nullptr == info) {
        return;
    }

    this->dpiEdit->setValue(info->info[MHDUIY::deviceDetailsInfo::Dpi].toInt());
    QString sizeInfo = info->info[MHDUIY::deviceDetailsInfo::Resolution];

    this->resolutionEditw->setValue(sizeInfo.split('x').value(0).toUInt());
    this->resolutionEdith->setValue(sizeInfo.split('x').value(1).toUInt());
}

void DeviceControlWidget::responseBtn(BatteryControlFlag flag)
{
    static QStringList CMDlist {
        "adb -s %1 shell dumpsys battery set level %2",
        "adb -s %1 shell dumpsys battery set status 2",
        "adb -s %1 shell dumpsys battery set status 1",
        "adb -s %1 shell dumpsys battery unplug",
        "adb -s %1 shell dumpsys battery reset"
    };
    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    if(cutDevice.isEmpty()) {
        emit sendMsgToMainWindow("没有设备连接");
        return;
    }
    int inputBtyLevel = 0;
    switch (flag) {
    case Bty_SetLevel:
        inputBtyLevel = BtyLevelEdit->value();
        tool.executeCommand(CMDlist.value(Bty_SetLevel).arg(cutDevice).arg(inputBtyLevel));
        break;
    case Bty_StartCharge:
        tool.executeCommand(CMDlist.value(Bty_StartCharge).arg(cutDevice));
        break;
    case Bty_StopCharge:
        tool.executeCommand(CMDlist.value(Bty_StopCharge).arg(cutDevice));
        break;
    case Bty_BreakCharge:
        tool.executeCommand(CMDlist.value(Bty_BreakCharge).arg(cutDevice));
        break;
    case Bty_ResetCharge:
        tool.executeCommand(CMDlist.value(Bty_ResetCharge).arg(cutDevice));
        break;
    default:
        return;
    }
    emit sendMsgToMainWindow("设置成功");
}

