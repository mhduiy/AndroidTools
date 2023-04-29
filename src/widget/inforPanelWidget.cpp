#include "inforPanelWidget.h"
#include <QLayout>
#include <QHeaderView>
#include <QPalette>
#include "ADBTools.h"
#include "deviceConnect.h"
#include <DTextBrowser>

InfoPannelWidget::InfoPannelWidget(QWidget *parent)  : MyBaceWidget(parent)
{
    initUI();
}

InfoPannelWidget::~InfoPannelWidget()
{

}

void InfoPannelWidget::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *headLayout = new QHBoxLayout();

    deviceName = new DLabel("Android Tools");
    rebootAdbServerBtn = new DWarningButton();
    rebootAdbServerBtn->setFixedWidth(100);
    rebootAdbServerBtn->setText("重启ADB");
    rebootAdbServerBtn->setToolTip("重启ADB服务，可以解决一些未知问题或卡顿");
    headLayout->addWidget(deviceName);
    headLayout->addWidget(rebootAdbServerBtn, Qt::AlignRight);
    //设置字体大小
    QFont font = deviceName->font();
    font.setPointSize(20);
    deviceName->setFont(font);

    QHBoxLayout *pgLayout = new QHBoxLayout();

    deviceRealTimePG.resize(MHDUIY::deviceRealTimeInfo::PG_StorageUsed+1);
    pgLayout->setAlignment(Qt::AlignLeft);
    for (int i = 0; i < MHDUIY::deviceRealTimeInfo::PG_StorageUsed+1; i++) {
        deviceRealTimePG[i] = new MyCircleProgress();
        deviceRealTimePG[i]->setFixedSize(100,150);
        deviceRealTimePG[i]->setTopText(MHDUIY::deviceRealTimeInfo::OUTSTR[i]);
        deviceRealTimePG[i]->getPG()->setValue(100);
        deviceRealTimePG[i]->setBottomText("待测试");
        pgLayout->addWidget(deviceRealTimePG[i]);
    }

    deviceInfoTable = new DTableView;
    deviceInfoTable->horizontalHeader()->hide(); //隐藏表头
    deviceInfoTable->verticalHeader()->hide();   //隐藏垂直表头
    deviceInfoTable->horizontalHeader()->setStretchLastSection(true);
    deviceInfoTable->setSelectionMode(QAbstractItemView::NoSelection);  //设置不可选择
    deviceInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑    
    // 设置无边框
    deviceInfoTable->setFrameStyle(QFrame::NoFrame);

    // 隐藏网格线
    deviceInfoTable->setShowGrid(false);
    deviceInfoTable->viewport()->setAutoFillBackground(true);
    deviceInfoTable->setAlternatingRowColors(true);
    deviceInfoTable->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    deviceInfoTable->setWindowFlags(Qt::FramelessWindowHint);   //设置无边框窗口
    QPalette palette = deviceInfoTable->palette();
    palette.setColor(QPalette::Inactive, QPalette::Text, palette.color(QPalette::Text));
    palette.setColor(QPalette::Inactive, QPalette::AlternateBase, palette.color(QPalette::AlternateBase));
    deviceInfoTable->setPalette(palette);
    /*test*/
    tableModel = new QStandardItemModel();
    deviceInfoTable->setModel(tableModel);
    //设置列数为2
    tableModel->setColumnCount(2);
    for(QString &s : MHDUIY::deviceDetailsInfo::OUTSTR) {
        QStandardItem *item = new QStandardItem(s);
        tableModel->appendRow(item);
    }
    //设置表格列宽和行高
    deviceInfoTable->setColumnWidth(0, 100);
    for(int i = 0; i < MHDUIY::deviceDetailsInfo::TOTAL; i++) {
        deviceInfoTable->setRowHeight(i, 40);
    }
    QHBoxLayout *deviceInfoLayout = new QHBoxLayout();

    DWidget *baseInfoW = new DWidget(this);
    baseInfoControl = new DeviceControlItem(baseInfoW);
    baseInfoControl->setTitle("设备基础信息");
    baseInfoControl->setDesVisible(false);
    QVBoxLayout *baseInfoLayout = new QVBoxLayout(baseInfoW);
    baseInfoLayout->addWidget(deviceInfoTable);

    DWidget *currentActivityW = new DWidget(this);
    currentActivityControl = new DeviceControlItem(currentActivityW);
    currentActivityControl->setDesVisible(false);
    currentActivityControl->setTitle("设备当前活动");
    QGridLayout *cutActivityLayout = new QGridLayout(currentActivityW);
    cutActivityLayout->setColumnStretch(0, 1);
    cutActivityLayout->setColumnStretch(1, 4);
    for(int i = 0; i < 3; i++) {
        DLabel *l = new DLabel();
        l->setWordWrap(true);
        currentActivityLabels.push_back(l);
        cutActivityLayout->addWidget(new DLabel(MHDUIY::deviceRealTimeInfo::OUTSTR.value(i+5)), i, 0);
        cutActivityLayout->addWidget(l, i, 1);
    }
    stopCutAppBtn = new DWarningButton();
    connect(stopCutAppBtn, &DPushButton::clicked, this, &InfoPannelWidget::stopCutApp);
    stopCutAppBtn->setText("停止当前应用");
    cutActivityLayout->addWidget(stopCutAppBtn, 3, 0, 1, 2);

    DWidget *btyInfoW = new DWidget(this);
    btyInfoControl = new DeviceControlItem(btyInfoW);
    btyInfoControl->setTitle("设备电池信息");
    btyInfoControl->setDesVisible(false);
    QVBoxLayout *btyInfoLayout = new QVBoxLayout(btyInfoW);
    btyTextBrowser = new DTextBrowser();
    DFontSizeManager::instance()->bind(btyTextBrowser, DFontSizeManager::T8);
    btyInfoLayout->addWidget(btyTextBrowser);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(currentActivityControl);
    rightLayout->addWidget(btyInfoControl);
    deviceInfoLayout->addWidget(baseInfoControl, 1);
    deviceInfoLayout->addLayout(rightLayout, 1);

    mainLayout->addLayout(headLayout);
    mainLayout->addLayout(pgLayout);
    mainLayout->addLayout(deviceInfoLayout);

    this->setLayout(mainLayout);

    connect(rebootAdbServerBtn, &DPushButton::clicked, [this](){
        ADBTools tool;
        tool.executeCommandNoLimit("adb kill-server");
        tool.executeCommandNoLimit("adb start-server");
        emit sendMsgToMainWindow("重启成功，请刷新设备");
    });

}

void InfoPannelWidget::setInfoToRealTimePG(MHDUIY::deviceRealTimeInfo *info)
{
    for(int i = 0; i < int(info->PG_StorageUsed) + 1 ; i++) {
        deviceRealTimePG[i]->setBottomText(info->info[i]);
        deviceRealTimePG[i]->getPG()->setValue(info->valueInfo[i]);
    }
    currentActivityLabels.value(0)->setText(info->info[MHDUIY::deviceRealTimeInfo::AC_WindowsCode]);
    currentActivityLabels.value(1)->setText(info->info[MHDUIY::deviceRealTimeInfo::AC_CurrentPackage]);
    currentActivityLabels.value(2)->setText(info->info[MHDUIY::deviceRealTimeInfo::AC_CurrentActivity]);
    btyTextBrowser->setText(info->info[MHDUIY::deviceRealTimeInfo::BTY_btyInfo]);
}

void InfoPannelWidget::setInfoToDetialsTable(MHDUIY::deviceDetailsInfo *info)
{
    QStandardItem *item;
    for(int i = 0; i < info->TOTAL; i++) {
        item = new DStandardItem(info->info[i]);
        tableModel->setItem(i, 1, item);
    }
    deviceName->setText(info->info[MHDUIY::deviceDetailsInfo::Manufacturer]
            + "-"
            + info->info[MHDUIY::deviceDetailsInfo::DeviceBrand]
            + " "
            + info->info[MHDUIY::deviceDetailsInfo::DeviceModel]);
}

void InfoPannelWidget::stopCutApp()
{
    QString package= currentActivityLabels.value(1)->text();
    if(package == "无前台应用" || package.isEmpty()) {
        emit sendMsgToMainWindow("没有活动可以停止");
        return;
    }
    QString cutDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    if(cutDevice.isEmpty()) {
        emit sendMsgToMainWindow("当前无设备连接");
        return;
    }
    QString command = QString("adb -s %1 shell am force-stop '%2'").arg(cutDevice).arg(package);
    ADBTools tool;
    tool.executeCommand(command);
    emit sendMsgToMainWindow("已停止");
}
