#include "deviceControlWidget.h"
#include <DGroupBox>
#include <QLayout>
#include <QDebug>
#include <DLabel>
#include <DSuggestButton>
#include "deviceConnect.h"

DeviceControlWidget::DeviceControlWidget(QWidget *parent) : DWidget(parent)
{
    initUI();
}

DeviceControlWidget::~DeviceControlWidget()
{

}

void DeviceControlWidget::initUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();

    QVBoxLayout *leftKeyLayout = new QVBoxLayout();
    QVBoxLayout *rightContorlLayout = new QVBoxLayout();

//    /* test */
//    rightContorlLayout->addWidget(new DPushButton("占位"));
    rightContorlLayout->setAlignment(Qt::AlignTop);

    DGroupBox *keySimulationBox = new DGroupBox();
    DGroupBox *advancedRestartBox = new DGroupBox();
    DGroupBox *mediaControlBox = new DGroupBox();

    QGridLayout *keySimulationLayout = new QGridLayout();
    QGridLayout *advancedRestartLayout = new QGridLayout();
    QGridLayout *mediaControlLayout = new QGridLayout();

    keySimulationBox->setLayout(keySimulationLayout);
    advancedRestartBox->setLayout(advancedRestartLayout);
    mediaControlBox->setLayout(mediaControlLayout);

    keySimulationBox->setTitle("按键模拟");
    advancedRestartBox->setTitle("高级重启");
    mediaControlBox->setTitle("媒体控制");

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

//    DGroupBox *dpiBox = new DGroupBox();
//    QVBoxLayout *dpiBoxLayout = new QVBoxLayout(dpiBox);
//    dpiBoxLayout->setAlignment(Qt::AlignTop);
//    DLabel *l = new DLabel("修改设备的分辨率和DPI");
//    QPalette pa = l->palette();
//    pa.setColor(QPalette::WindowText, Qt::gray);
//    l->setPalette(pa);
//    dpiBoxLayout->addWidget(l);
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

    leftKeyLayout->addWidget(keySimulationBox);
    leftKeyLayout->addWidget(advancedRestartBox);
    leftKeyLayout->addWidget(mediaControlBox);
    rightContorlLayout->addWidget(dpiControl);
    rightContorlLayout->addWidget(inputControl);
    rightContorlLayout->addWidget(scriptControl);
    mainLayout->addLayout(leftKeyLayout,4);
    mainLayout->addLayout(rightContorlLayout,3);
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
            tool.executeCommand(MHDUIY::advancedRestartInfo::CMDSTR[i]
                                .arg(currentDevice));
            emit sendMsgToMainWindow(QString("已触发 %1").arg(MHDUIY::advancedRestartInfo::OUTSTR[i]));
            break;
        case MHDUIY::deviceControlCode::MediaControl:
            tool.executeCommand(MHDUIY::mediaControlInfo::CMDSTR[i]
                                .arg(currentDevice));
            emit sendMsgToMainWindow(QString("已触发 %1").arg(MHDUIY::mediaControlInfo::OUTSTR[i]));
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

