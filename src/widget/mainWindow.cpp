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

    timer.start(1000);

    connect(flashBtn, &DPushButton::clicked, [this](){
        for(int i = 0; i < this->devices.size(); i++) {
            delete this->devices[i];
        }
        this->devices.resize(0);
        this->deviceBox->clear();

        ADBTools tool;
        QString ret = tool.executeCommand("adb devices");
    //    ret = ret.simplified();
    //    info->info[MHDUIY::deviceBaceInfo::DeviceCodeName] =
        QStringList l = ret.split('\n');
        QVector<MHDUIY::deviceBaceInfo*> res;
        bool readFlag = false;
        for (QString &s : l) {
            if(s.isEmpty()) {
                continue;
            }
            if(s.startsWith("*")) {
                return;
            }
            if(s == "List of devices attached") {
                readFlag = true;
            }
            if(readFlag == true) {  //读取到新设备
                MHDUIY::deviceBaceInfo *info = new MHDUIY::deviceBaceInfo();
                s = s.simplified();
                QStringList ll = s.split(' ');
                if(ll.value(1) == "device") {
                    qDebug() << ll.value(0);
                    info->info[MHDUIY::deviceBaceInfo::DeviceCodeName] = ll.value(0);
                    this->deviceBox->addItem(ll.value(0));
                }
                res.push_back(info);
            }
        }
        this->devices = res;
    });

}

void MainWindow::myCmd(QString cmd)
{

}
// 前端调用，
