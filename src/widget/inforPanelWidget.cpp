#include "inforPanelWidget.h"
#include <QLayout>
#include <QHeaderView>
#include <QPalette>
#include "ADBTools.h"

InfoPannelWidget::InfoPannelWidget(QWidget *parent) : DWidget (parent)
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

    headLayout->addWidget(deviceName);
//    headLayout->addWidget(flashBtn);
//    headLayout->addWidget(deviceBox);

    //设置字体大小
    QFont font = deviceName->font();
    font.setPointSize(20);
    deviceName->setFont(font);

    QHBoxLayout *pgLayout = new QHBoxLayout();

    deviceRealTimePG.resize(MHDUIY::deviceRealTimeInfo::TOTAL);
    pgLayout->setAlignment(Qt::AlignLeft);
    for (int i = 0; i < MHDUIY::deviceRealTimeInfo::TOTAL; i++) {
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
    deviceInfoTable->setPalette(palette);
    /*test*/
    tableModel = new QStandardItemModel();
    deviceInfoTable->setModel(tableModel);
    //设置列数为2
    tableModel->setColumnCount(2);
    for(QString &s : MHDUIY::deviceDetailsInfo::OUTSTR) {
        QStandardItem *item = new QStandardItem(s);
        item->setBackground(QBrush(QColor(247, 247, 247)));
//        QFont font = item->font();
//        font.setBold(true);
//        item->setFont(font);
        tableModel->appendRow(item);
    }
    //设置表格列宽和行高
    deviceInfoTable->setColumnWidth(0, int(deviceInfoTable->width() * 0.3));
    for(int i = 0; i < MHDUIY::deviceDetailsInfo::TOTAL; i++) {
        deviceInfoTable->setRowHeight(i, 40);
    }
//    deviceInfo->setColumnWidth(1, int(deviceInfo->width() * 0.7));

    DFrame *frame = new DFrame();
    frame->setFrameRounded(true);
    QVBoxLayout *frameLayout = new QVBoxLayout();
    frame->setLayout(frameLayout);
    frameLayout->addWidget(deviceInfoTable);

    mainLayout->addLayout(headLayout);
    mainLayout->addLayout(pgLayout);
    mainLayout->addWidget(frame);

    this->setLayout(mainLayout);

//    connect(flashBtn, &DPushButton::clicked, this, &InfoPannelWidget::flashDevice);

}

void InfoPannelWidget::setInfoToRealTimePG(MHDUIY::deviceRealTimeInfo *info)
{
    for(int i = 0; i < info->TOTAL ; i++) {
        deviceRealTimePG[i]->setBottomText(info->info[i]);
        deviceRealTimePG[i]->getPG()->setValue(info->valueInfo[i]);
    }
}

void InfoPannelWidget::setInfoToDetialsTable(MHDUIY::deviceDetailsInfo *info)
{
    QStandardItem *item;
    for(int i = 0; i < info->TOTAL; i++) {
        item = new DStandardItem(info->info[i]);
        tableModel->setItem(i, 1, item);
    }
    deviceName->setText(info->info[MHDUIY::deviceDetailsInfo::Manufacturer]
            + " "
            + info->info[MHDUIY::deviceDetailsInfo::DeviceModel]);
}
