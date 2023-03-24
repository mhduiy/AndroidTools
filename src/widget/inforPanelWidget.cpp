#include "inforPanelWidget.h"
#include <QLayout>
#include <QHeaderView>
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

    deviceName = new DLabel("Xiaomi 13 Pro");
//    deviceBox = new DComboBox();
//    flashBtn = new DPushButton("刷新设备");
//    flashBtn->setFixedWidth(80);
//    deviceBox->setFixedWidth(150);

//    deviceBox->addItem("test1");
//    deviceBox->addItem("test2");

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
    deviceInfoTable->setFocus(Qt::FocusReason::ActiveWindowFocusReason);

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


    mainLayout->addLayout(headLayout);
    mainLayout->addLayout(pgLayout);
    mainLayout->addWidget(deviceInfoTable);

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
        item = new DStandardItem(info->OUTSTR[i]);
        tableModel->setItem(i, 1, item);
    }
}
