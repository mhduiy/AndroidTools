#include "flashToolWidget.h"
#include <DLabel>
#include <QLayout>
#include <DFontSizeManager>
#include <QPalette>

FlashToolWidget::FlashToolWidget(QWidget *parent) : DWidget (parent)
{
    initUI();
}

FlashToolWidget::~FlashToolWidget()
{

}

void FlashToolWidget::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    DLabel *alertLabel = new DLabel("道路千万条，安全第一条，刷机不规范，救砖两行泪");
    alertLabel->setAlignment(Qt::AlignCenter);
    DFontSizeManager::instance()->bind(alertLabel, DFontSizeManager::T3);
    QPalette labelPalette = alertLabel->palette();
    labelPalette.setColor(QPalette::WindowText, Qt::red);
    alertLabel->setPalette(labelPalette);

    deviceBox = new DComboBox();
    updateBtn = new DIconButton();
    updateBtn->setIcon(QIcon(":/Icon/Refresh.png"));
    deviceBox->setFixedWidth(200);
    updateBtn->setFixedSize(36,36);
    QHBoxLayout *deviceLayout = new QHBoxLayout();
    deviceLayout->setSpacing(20);
    deviceLayout->addWidget(deviceBox);
    deviceLayout->addWidget(updateBtn);
    deviceLayout->addWidget(new DLabel("请将设备重启到FastBoot模式，然后点击左边刷新按钮"));

    QHBoxLayout *funcLayout = new QHBoxLayout();    //左右两边功能区域
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();

    /*刷写分区*/
    DWidget *flashPartitionW = new DWidget(this);
    flashPartitionControl = new DeviceControlItem(flashPartitionW);
    flashPartitionControl->setTitle("刷写分区");
    flashPartitionControl->setDescribe("指定一个分区和一个镜像文件，开始刷入");
    QVBoxLayout *flashPartitionLayout = new QVBoxLayout(flashPartitionW);
    QHBoxLayout *flashSelectPartitionLayout = new QHBoxLayout();
    QHBoxLayout *flashSelectImgPathLayout = new QHBoxLayout();

    targetPartition = new DComboBox();
    targetPartition->addItem("boot");
    targetPartition->addItem("recovery");
    targetPartition->addItem("system");
    flashSelectPartitionLayout->addWidget(new DLabel("选择要刷入的分区"));
    flashSelectPartitionLayout->addWidget(targetPartition);

    selectFlashImgBtn = new DSuggestButton("选择");
    FlashImgPathEdit = new DLineEdit();
    flashSelectImgPathLayout->addWidget(new DLabel("选择镜像文件路径"));
    flashSelectImgPathLayout->addWidget(FlashImgPathEdit);
    flashSelectImgPathLayout->addWidget(selectFlashImgBtn);

    flashBtn = new DSuggestButton();
    flashBtn->setText("开始刷入");
    flashPartitionLayout->addLayout(flashSelectPartitionLayout);
    flashPartitionLayout->addLayout(flashSelectImgPathLayout);
    flashPartitionLayout->addWidget(flashBtn);
    /*临时启动*/
    DWidget *tempStartW = new DWidget(this);
    tempStartImgControl = new DeviceControlItem(tempStartW);
    tempStartImgControl->setTitle("临时启动");
    tempStartImgControl->setDescribe("临时启动镜像，一般用于Twrp的刷入");
    QVBoxLayout *tempStartLayout = new QVBoxLayout(tempStartW);
    QHBoxLayout *tempStartSelectLayout = new QHBoxLayout();
    tempStartPathEdit = new DLineEdit();
    selectStartImgBtn = new DSuggestButton("选择");
    tempStartSelectLayout->addWidget(new DLabel("选择一个镜像文件"));
    tempStartSelectLayout->addWidget(tempStartPathEdit);
    tempStartSelectLayout->addWidget(selectStartImgBtn);
    tempStartBtn = new DSuggestButton("开始临时启动");
    tempStartLayout->addLayout(tempStartSelectLayout);
    tempStartLayout->addWidget(tempStartBtn);
    /*清除分区*/
    DWidget *clearPartitionW = new DWidget(this);
    clearPartitionControl = new DeviceControlItem(clearPartitionW);
    clearPartitionControl->setTitle("清除分区");
    clearPartitionControl->setDescribe("清除分区数据, 可能导致设备无法启动，请谨慎操作");
    QVBoxLayout *clearPartitionLayout = new QVBoxLayout(clearPartitionW);
    QHBoxLayout *clearPartitionSelectLayout = new QHBoxLayout();
    clearPartitionBox = new QComboBox();
    clearPartitionBox->addItem("boot");
    clearPartitionBox->addItem("recovery");
    clearPartitionBox->addItem("system");
    clearPartitionSelectLayout->addWidget(new DLabel("选择目标分区"));
    clearPartitionSelectLayout->addWidget(clearPartitionBox);
    clearBtn = new DSuggestButton("清除分区");
    clearPartitionLayout->addLayout(clearPartitionSelectLayout);
    clearPartitionLayout->addWidget(clearBtn);


    leftLayout->addWidget(flashPartitionControl);
    leftLayout->addWidget(tempStartImgControl);
    leftLayout->addWidget(clearPartitionControl);
    funcLayout->addLayout(leftLayout);
    DPushButton *testBtn = new DPushButton("占位");
    rightLayout->addWidget(testBtn);
    funcLayout->addLayout(rightLayout);
    funcLayout->setStretch(0,1);
    funcLayout->setStretch(1,1);

    mainLayout->addWidget(alertLabel);
    mainLayout->addLayout(deviceLayout);
    mainLayout->addLayout(funcLayout);
}
