#include "flashToolWidget.h"
#include <DLabel>
#include <QLayout>
#include <DFontSizeManager>
#include <QPalette>
#include "myTypes.h"
#include <DStyledItemDelegate>
#include <QDesktopServices>
#include <QUrl>
#include "deviceConnect.h"
#include <QFile>
#include <DFileDialog>
#include <DDialog>

FlashToolWidget::FlashToolWidget(QWidget *parent)  : MyBaceWidget(parent)
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

    flashTool = new FlashTool();

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

    connect(deviceBox, QOverload<int>::of(&DComboBox::currentIndexChanged), [this](int index){
        DeviceConnect::getInstance()->setCurrentDevice(index);
    });
    connect(updateBtn, &DPushButton::clicked, this, &FlashToolWidget::getFastBootDevices);  //刷新新设备

    QHBoxLayout *funcLayout = new QHBoxLayout();    //左右两边功能区域
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();

    leftLayout->setAlignment(Qt::AlignTop);
    rightLayout->setAlignment(Qt::AlignTop);

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

    /*right Layout*/
    /*解包*/
    DWidget *unPackW = new DWidget(this);
    unPackControl = new DeviceControlItem(unPackW);
    unPackControl->setTitle("解包");
    unPackControl->setDescribe("解压卡刷包，支持解压payload.img");
    QVBoxLayout *unPackLayout = new QVBoxLayout(unPackW);
    QHBoxLayout *selectUnPackLayout = new QHBoxLayout();
    unPackPathEdit = new DLineEdit();
    selectUnPackBtn = new DSuggestButton("选择");
    selectUnPackLayout->addWidget(new DLabel("选择一个卡刷包"));
    selectUnPackLayout->addWidget(unPackPathEdit);
    selectUnPackLayout->addWidget(selectUnPackBtn);
    isUnPackPayload = new DCheckBox();
    isUnPackPayload->setText("是否解压payLoad.img");
    isUnPackPayload->setCheckState(Qt::Unchecked);

    QHBoxLayout *unPackBtnLayout = new QHBoxLayout();
    unPackBtn = new DSuggestButton("开始解压");
    openUnPackOutDir = new DPushButton("打开文件夹");
    unPackBtnLayout->addWidget(unPackBtn);
    unPackBtnLayout->addWidget(openUnPackOutDir);

    unPackLayout->addLayout(selectUnPackLayout);
    unPackLayout->addWidget(isUnPackPayload);
    unPackLayout->addLayout(unPackBtnLayout);

    /*快捷重启*/
    DWidget *fastRebootW = new DWidget(this);
    fastRebootControl = new DeviceControlItem(fastRebootW);
    fastRebootControl->setTitle("快捷重启");
    fastRebootControl->setDescribe("控制设备重启到指定位置");
    QGridLayout *fastReBootLayout = new QGridLayout(fastRebootW);
    fastReBootLayout->setSpacing(10);
    for(int i = 0; i < MHDUIY::FastRebootInfo::TOTAL; i++) {
        static int j = 0;
        DPushButton *btn = new DPushButton(MHDUIY::FastRebootInfo::OUTSTR[i]);
        fastRebootBtns.push_back(btn);
        connect(btn, &DPushButton::clicked, [this, i](){this->responseFastRebootBtn(i);});
        if(i != 0 && i % 3 == 0) {
            j++;
        }
        fastReBootLayout->addWidget(btn, j, i % 3);
    }
    /*快捷链接*/
    quickConnModel = new QStandardItemModel();
    DWidget *quickConnW = new DWidget();
    quickConnectControl = new DeviceControlItem(quickConnW);
    quickConnectControl->setTitle("快捷链接");
    quickConnectControl->setDescribe("收录了可能会用到的网站，双击即可跳转访问");
    QVBoxLayout *quickConnLayout = new QVBoxLayout(quickConnW);
    quickConnPane = new DListView();
    quickConnPane->setModel(quickConnModel);
    for(int i = 0; i < MHDUIY::QuickConnItem::websiteNames.size(); i++) {
        DStandardItem *item = new DStandardItem(MHDUIY::QuickConnItem::websiteNames.value(i));
        item->setData(MHDUIY::QuickConnItem::websiteStrs.value(i));
        item->setFontSize(DFontSizeManager::T5);
        DViewItemAction *itemAction = new DViewItemAction;
        itemAction->setText(MHDUIY::QuickConnItem::websiteDes.value(i));
        itemAction->setFontSize(DFontSizeManager::T8);
        itemAction->setTextColorRole(DPalette::TextTips);
        itemAction->setParent(this);
        item->setTextActionList({itemAction});

        quickConnModel->appendRow(item);
    }

    quickConnPane->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    quickConnPane->setBackgroundType(DStyledItemDelegate::BackgroundType::RoundedBackground);

    connect(quickConnPane, &DListView::doubleClicked, [this](const QModelIndex &index){ //调用默认浏览器打开链接
        QDesktopServices::openUrl(QUrl(index.data(Qt::UserRole+1).toString()));
    });

    quickConnLayout->addWidget(quickConnPane);

    rightLayout->addWidget(unPackControl);
    rightLayout->addWidget(fastRebootControl);
    rightLayout->addWidget(quickConnectControl);
    funcLayout->addLayout(rightLayout);
    funcLayout->setStretch(0,1);
    funcLayout->setStretch(1,1);

    mainLayout->addWidget(alertLabel);
    mainLayout->addLayout(deviceLayout);
    mainLayout->addLayout(funcLayout);
    //刷写分区选择
    connect(selectFlashImgBtn, &DPushButton::clicked, [this](){
        QString doc_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        QString filePath = QFileDialog::getOpenFileName(this, tr("请选择一个镜像文件"), doc_path, tr("IMG Files (*.img)"));
        FlashImgPathEdit->setText(filePath);
    });
    //刷写分区
    connect(flashBtn, &DPushButton::clicked, [this](){
        QString path = this->FlashImgPathEdit->text();
        if(!QFile::exists(path)) {
            this->FlashImgPathEdit->showAlertMessage("请选择正确的路径");
            return;
        }
        if(this->showAlertDlg() != 0) {
            return;
        }
        if(noDevice) {
            emit sendMsgToMainWindow("没有连接任何设备");
            return;
        }
        flashTool->flashPartition(this->targetPartition->currentText(), path);
    });
    //临时启动选择
    connect(selectStartImgBtn, &DPushButton::clicked, [this](){
        QString doc_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        QString filePath = QFileDialog::getOpenFileName(this, tr("请选择一个镜像文件"), doc_path, tr("IMG Files (*.img)"));
        tempStartPathEdit->setText(filePath);
    });
    //临时启动
    connect(tempStartBtn, &DPushButton::clicked, [this](){
        QString path = this->tempStartPathEdit->text();
        if(!QFile::exists(path)) {
            this->tempStartPathEdit->showAlertMessage("请选择正确的路径");
            return;
        }
        if(this->showAlertDlg() != 0) {
            return;
        }
        if(noDevice) {
            emit sendMsgToMainWindow("没有连接任何设备");
            return;
        }
        flashTool->startPartition(path);
    });
    //清除分区
    connect(clearBtn, &DPushButton::clicked, [this](){
        if(this->showAlertDlg() != 0) {
            return;
        }
        if(noDevice) {
            emit sendMsgToMainWindow("没有连接任何设备");
            return;
        }
        flashTool->eraserPartition(clearPartitionBox->currentText());
    });
}

void FlashToolWidget::responseFastRebootBtn(int i)
{
    emit sendMsgToMainWindow("已触发 " + MHDUIY::FastRebootInfo::OUTSTR[i]);
}

void FlashToolWidget::getFastBootDevices()
{
    auto devices = DeviceConnect::getInstance()->flashFastBootDevices();
    this->deviceBox->clear();
    if(devices.size() == 0) {
        emit sendMsgToMainWindow("当前未连接到任何FastBoot设备");
        noDevice = true;
        return;
    }
    noDevice = false;
    for(auto info : devices) {
        this->deviceBox->addItem(info->info[MHDUIY::deviceBaceInfo::DeviceCodeName]);
    }
    deviceBox->setCurrentIndex(0);
    DeviceConnect::getInstance()->setCurrentFastBootDevice(0);
}

int FlashToolWidget::showAlertDlg()
{
    DDialog dlgDelete1("提示", "此操作为高危操作，且无法撤销, 是否继续执行");
    dlgDelete1.addButton("是", true, DDialog::ButtonWarning);
    dlgDelete1.addButton("否", false, DDialog::ButtonNormal);
    dlgDelete1.setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning));
    return dlgDelete1.exec();
}
