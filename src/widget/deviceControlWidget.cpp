#include "deviceControlWidget.h"
#include <DGroupBox>
#include <QLayout>
#include <QDebug>
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

    /* test */
    rightContorlLayout->addWidget(new DPushButton("占位"));

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

    leftKeyLayout->addWidget(keySimulationBox);
    leftKeyLayout->addWidget(advancedRestartBox);
    leftKeyLayout->addWidget(mediaControlBox);
    mainLayout->addLayout(leftKeyLayout);
    mainLayout->addLayout(rightContorlLayout);
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
            break;
        case MHDUIY::deviceControlCode::AdvancedReBoot:
            tool.executeCommand(MHDUIY::advancedRestartInfo::CMDSTR[i]
                                .arg(currentDevice));
            break;
        case MHDUIY::deviceControlCode::MediaControl:
            tool.executeCommand(MHDUIY::mediaControlInfo::CMDSTR[i]
                                .arg(currentDevice));
            break;
    }
}
