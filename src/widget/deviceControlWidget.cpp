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
    dpiEdit = new DLineEdit();
    dpiEdLayout->addWidget(new DLabel("DPI: "));
    dpiEdLayout->addWidget(dpiEdit);

    QHBoxLayout *resuEdLayout = new QHBoxLayout();
    resolutionEditw = new DLineEdit();
    resolutionEdith = new DLineEdit();

    resolutionEditw->setFixedWidth(100);
    resolutionEdith->setFixedWidth(100);
    dpiEdit->setFixedWidth(100);

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
    mainLayout->addLayout(leftKeyLayout);
    mainLayout->addLayout(rightContorlLayout);
    mainLayout->setStretch(0,2);
    mainLayout->setStretch(1,1);
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
