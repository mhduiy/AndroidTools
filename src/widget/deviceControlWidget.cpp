#include "deviceControlWidget.h"
#include <DGroupBox>
#include <QLayout>
#include <QDebug>

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

    for(int i = 0; i < MHDUIY::keySimulationInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::keySimulationInfo::OUTSTR[i]);
        if(i != 0 && i % 4 == 0) {
            j++;
        }
        qDebug() << i % 4 << j;
        keySimulationLayout->addWidget(btn, j, i % 4);
        keySimulationBtns.push_back(btn);
    }

    for(int i = 0; i < MHDUIY::advancedRestartInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::advancedRestartInfo::OUTSTR[i]);
        if(i != 0 && i % 2 == 0) {
            j++;
        }
        advancedRestartLayout->addWidget(btn, j, i % 2);
        advancedRestartBtns.push_back(btn);
    }

    for(int i = 0; i < MHDUIY::mediaControlInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::mediaControlInfo::OUTSTR[i]);
        if(i != 0 && i % 2 == 0) {
            j++;
        }
        mediaControlLayout->addWidget(btn, j, i % 2);
        mediaControlBtns.push_back(btn);
    }

    leftKeyLayout->addWidget(keySimulationBox);
    leftKeyLayout->addWidget(advancedRestartBox);
    leftKeyLayout->addWidget(mediaControlBox);
    mainLayout->addLayout(leftKeyLayout);
    mainLayout->addLayout(rightContorlLayout);
    this->setLayout(mainLayout);
    qDebug() << "test";
}
