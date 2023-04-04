#include "mainWindow.h"
#include <DTitlebar>
#include <QLayout>
#include "deviceDetailTool.h"
#include <DSuggestButton>

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
    flashBtn = new DIconButton();
    wirelessBtn = new DSuggestButton("无线连接");

    flashBtn->setIcon(QIcon(":/Icon/Refresh.png"));

    wirelessBtn->setFixedWidth(80);
    deviceBox->setFixedWidth(150);

    this->titlebar()->addWidget(deviceBox, Qt::AlignRight);
    this->titlebar()->addWidget(flashBtn, Qt::AlignRight);
    this->titlebar()->addWidget(wirelessBtn, Qt::AlignRight);

    this->titlebar()->setIcon(QIcon(":/Icon/appIcon.png"));

    wirelessConWidget = new WirelessConnectWidget();

    //设置托盘图标
    sysIcon = new QSystemTrayIcon(this);
    sysIcon->setToolTip("Android-Tools：当前未连接到任何设备");
    this->paintBtyIcon(100);
    sysIcon->show();

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
//    setSidebarWidget(funcView);
//    setSidebarWidth(200);
    //设置不可编辑
    funcView->setEditTriggers(QListView::EditTrigger::NoEditTriggers);

    funcView->setCurrentIndex(model->index(0,0));

    mainStackedWidget = new DStackedWidget;

    infoPannelWidget = new InfoPannelWidget;
    deviceControlWidget = new DeviceControlWidget;
    softwareManageWidget = new SoftwareManageWidget;
    fileManageWidget = new FileManageWidget;
    flashToolWidget = new FlashToolWidget;
    deviceImageWidget = new DeviceImageWidget;
    terminalWidget = new TerminalWidget;

    mainStackedWidget->addWidget(infoPannelWidget);
    mainStackedWidget->addWidget(deviceControlWidget);
    mainStackedWidget->addWidget(softwareManageWidget);
    mainStackedWidget->addWidget(fileManageWidget);
    mainStackedWidget->addWidget(flashToolWidget);
    mainStackedWidget->addWidget(deviceImageWidget);
    mainStackedWidget->addWidget(terminalWidget);

    mainStackedWidget->setCurrentIndex(0);

    //将左边的功能区和右边的内容显示区域加入到布局中
    mainLayout->addWidget(funcView);
    mainLayout->addWidget(mainStackedWidget);

    mainW = new DWidget(this);
    mainW->setLayout(mainLayout);

    this->setCentralWidget(mainW);

    updateThreadTool = UpdateThread::getInstance();
    flashThread = new QThread();
    updateThreadTool->moveToThread(flashThread);
    flashThread->start();
    connect(&timer, &QTimer::timeout, updateThreadTool, &UpdateThread::FlashPGInfo);
    connect(updateThreadTool, &UpdateThread::readDeviceInfoFinish, infoPannelWidget, &InfoPannelWidget::setInfoToRealTimePG);
    connect(updateThreadTool, &UpdateThread::readDeviceInfoFinish, this, [this](MHDUIY::deviceRealTimeInfo *info){
        this->paintBtyIcon(info->valueInfo[MHDUIY::deviceRealTimeInfo::BatteryLevel]);
        this->sysIcon->setToolTip(QString("当前设备电量：%1%").arg(info->valueInfo[MHDUIY::deviceRealTimeInfo::BatteryLevel]));
    });

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
        auto res = DeviceDetailTool::getInstance()->flashInfo();    //刷新详细信息
        infoPannelWidget->setInfoToDetialsTable(res);   //设置详细信息

        for(MHDUIY::deviceBaceInfo* info : devices) {   //添加信息的box
            this->deviceBox->addItem(info->info[MHDUIY::deviceBaceInfo::DeviceCodeName]);
        }
        this->deviceBox->setCurrentIndex(0);
        timer.start(1000);  //开启刷新信息的定时器
    });

    //选择了其他设备
    connect(deviceBox, QOverload<int>::of(&QComboBox::activated),[this](int index){
        DeviceConnect::getInstance()->setCurrentDevice(index);  //设置新设备
        auto res = DeviceDetailTool::getInstance()->flashInfo();    //刷新详细信息
        infoPannelWidget->setInfoToDetialsTable(res);   //设置详细信息
    });

    //链接左边的功能区域和右边的设备
    connect(funcView, &DListView::clicked, [this](const QModelIndex &index){
        //实现点击左侧功能按钮右边界面切换
        this->mainStackedWidget->setCurrentIndex(index.row());
    });

    connect(deviceControlWidget, &DeviceControlWidget::sendMsgToMainWindow, this, &MainWindow::noticeMsg);

    //无线连接按钮
    connect(wirelessBtn, &DPushButton::clicked, this, [this](){
        int ret = this->wirelessConWidget->exec();
        if(ret == 0) {
            return;
        }
        emit flashBtn->clicked();
    });

    emit flashBtn->clicked();   //启动时自动触发一次刷新设备

}

void MainWindow::myCmd(QString cmd)
{

}

void MainWindow::noticeMsg(const QString &msg)
{
    this->sendMessage(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning), msg);
}

void MainWindow::paintBtyIcon(int level)
{
    static int l = -1;
    if(l == level) {//防止重复绘制
        return;
    }
    //创建一个QImage对象，作为绘图的画布
    QImage image(32, 32, QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    //打开抗锯齿
    painter.setRenderHints(QPainter::Antialiasing);
    QPen pen = painter.pen();
    pen.setWidth(2);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    //绘制外层矩形
    painter.drawRoundedRect(1,5,30,20,4,4);
    painter.setPen(Qt::NoPen);
    //绘制内层矩形
    if(level <= 0) {
        painter.setBrush(Qt::red);
        painter.drawRoundedRect(4,8,25,14,1,1);
    }
    else if (level < 20){
        painter.setBrush(Qt::red);
        painter.drawRoundedRect(4,8,4,14,1,1);
    }
    else if (level < 40){
        painter.setBrush(Qt::yellow);
        painter.drawRoundedRect(4,8,8,14,1,1);
    }
    else if (level < 60){
        painter.setBrush(Qt::yellow);
        painter.drawRoundedRect(4,8,12,14,1,1);
    }
    else if (level < 80){
        painter.setBrush(Qt::green);
        painter.drawRoundedRect(4,8,16,14,1,1);
    }
    else if (level < 100){
        painter.setBrush(Qt::green);
        painter.drawRoundedRect(4,8,20,14,1,1);
    }
    else if (level >= 100){
        painter.setBrush(Qt::blue);
        painter.drawRoundedRect(4,8,25,14,1,1);
    }

    // 将QImage对象转换为QIcon对象，并设置为托盘图标
    sysIcon->setIcon(QIcon(QPixmap::fromImage(image).scaled(32, 32, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    l = level;
}
