#include "inforPanelWidget.h"
#include <QLayout>
#include <QHeaderView>
#include "ADBTools.h"

InfoPannelWidget::InfoPannelWidget(QWidget *parent) : DWidget (parent)
{
    initUI();

    ADBTools tool;
    QString ret = tool.testCmd("adb devices");
    qDebug() << "ret" << ret;
}

InfoPannelWidget::~InfoPannelWidget()
{

}

void InfoPannelWidget::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *headLayout = new QHBoxLayout();

    deviceName = new DLabel("Xiaomi 13 Pro");
    deviceBox = new DComboBox();
    deviceBox->setFixedWidth(150);

    deviceBox->addItem("test1");
    deviceBox->addItem("test2");

    headLayout->addWidget(deviceName);
    headLayout->addWidget(deviceBox);

    //设置字体大小
    QFont font = deviceName->font();
    font.setPointSize(20);
    deviceName->setFont(font);

    QHBoxLayout *pgLayout = new QHBoxLayout();
    btyLevelPg = new MyCircleProgress;
//    btyLevelPg->setTextVisible(true);
//    btyLevelPg->
    btyTEMPPg = new MyCircleProgress;
    memoryPg = new MyCircleProgress;
    CPUPg = new MyCircleProgress;
    GPUPg = new MyCircleProgress;

    btyLevelPg->setFixedSize(100,150);
    btyTEMPPg->setFixedSize(100,150);
    memoryPg->setFixedSize(100,150);
    CPUPg->setFixedSize(100,150);
    GPUPg->setFixedSize(100,150);

    btyLevelPg->setTopText("电量");
    btyTEMPPg->setTopText("温度");
    memoryPg->setTopText("内存");
    CPUPg->setTopText("CPU");
    GPUPg->setTopText("GPU");

    btyLevelPg->setBottomText("50%");
    btyTEMPPg->setBottomText("20℃");
    memoryPg->setBottomText("2.1/8.0");
    CPUPg->setBottomText("80%");
    GPUPg->setBottomText("10%");

    pgLayout->setAlignment(Qt::AlignLeft);
    pgLayout->addWidget(btyLevelPg);
    pgLayout->addWidget(btyTEMPPg);
    pgLayout->addWidget(memoryPg);
    pgLayout->addWidget(CPUPg);
    pgLayout->addWidget(GPUPg);

    deviceInfo = new DTableView;
    deviceInfo->horizontalHeader()->hide(); //隐藏表头
    deviceInfo->verticalHeader()->hide();   //隐藏垂直表头

    deviceInfo->horizontalHeader()->setStretchLastSection(true);

    /*test*/
    tableModel = new QStandardItemModel();
    deviceInfo->setModel(tableModel);

    tableModel->setColumnCount(2);
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));
    tableModel->appendRow(new QStandardItem("安卓版本"));

    deviceInfo->setColumnWidth(0, int(deviceInfo->width() * 0.3));
    for(int i = 0; i < 11; i++) {
        deviceInfo->setRowHeight(i, 50);
    }
//    deviceInfo->setColumnWidth(1, int(deviceInfo->width() * 0.7));


    mainLayout->addLayout(headLayout);
    mainLayout->addLayout(pgLayout);
    mainLayout->addWidget(deviceInfo);

    this->setLayout(mainLayout);

}
