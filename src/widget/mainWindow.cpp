#include "mainWindow.h"
#include <DTitlebar>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) : DMainWindow (parent)
{
    this->titlebar()->setTitle("Android Tools");
    initUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;

    funcView = new DListView;
    funcView->setFixedWidth(150);

    //标题栏
    deviceBox = new DComboBox();
    flashBtn = new DPushButton("刷新");

    flashBtn->setFixedWidth(50);
    deviceBox->setFixedWidth(150);

    this->titlebar()->addWidget(deviceBox, Qt::AlignRight);
    this->titlebar()->addWidget(flashBtn, Qt::AlignRight);

    //设置功能区域的项目
    model = new QStandardItemModel;
    model->appendRow(new DStandardItem("信息面板"));
    model->appendRow(new DStandardItem("设备控制"));
    model->appendRow(new DStandardItem("软件管理"));
    model->appendRow(new DStandardItem("文件管理"));
    model->appendRow(new DStandardItem("刷机工具"));
    model->appendRow(new DStandardItem("设备镜像"));
    model->appendRow(new DStandardItem("终端"));
    funcView->setModel(model);
    //设置不可编辑
    funcView->setEditTriggers(QListView::EditTrigger::NoEditTriggers);

    funcView->setCurrentIndex(model->index(0,0));

    mainStackedWidget = new DStackedWidget;
    infoPannelWidget = new InfoPannelWidget;

    mainStackedWidget->addWidget(infoPannelWidget);
    mainStackedWidget->setCurrentIndex(0);

    //将左边的功能区和右边的内容显示区域加入到布局中
    mainLayout->addWidget(funcView);
    mainLayout->addWidget(mainStackedWidget);

    mainW = new DWidget(this);
    mainW->setLayout(mainLayout);

    this->setCentralWidget(mainW);

    flashThreadTool = FlashThreadTool::getInstance();
    flashThread = new QThread();
    flashThreadTool->moveToThread(flashThread);
    flashThread->start();
    connect(&timer, &QTimer::timeout, flashThreadTool, &FlashThreadTool::FlashPGInfo);
    connect(flashThreadTool, &FlashThreadTool::readDeviceInfoFinish, infoPannelWidget, &InfoPannelWidget::setInfoToRealTimePG);

    //寻找新设备
    connect(flashBtn, &DPushButton::clicked, [this](){
        this->deviceBox->clear();
        timer.stop();
        QVector<MHDUIY::deviceBaceInfo *> devices = DeviceConnect::getInstance()->flashDevices();   //刷新设备
        //没有找到任何设备
        if(devices.size() <= 0) {
            //发送消息
            this->sendMessage(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning), "当前没有连接到任何设备，请检查数据线的连接并确保打开了USB调试");
            return;
        }
        DeviceConnect::getInstance()->setCurrentDevice(0);    //设置默认设备为第一个

        for(MHDUIY::deviceBaceInfo* info : devices) {   //添加信息的box
            this->deviceBox->addItem(info->info[MHDUIY::deviceBaceInfo::DeviceCodeName]);
        }
        this->deviceBox->setCurrentIndex(0);
        timer.start(1000);  //开启刷新信息的定时器
    });
    connect(deviceBox, QOverload<int>::of(&QComboBox::activated),[](int index){
        DeviceConnect::getInstance()->setCurrentDevice(index);
    });

}

void MainWindow::myCmd(QString cmd)
{

}

// 前端调用，
