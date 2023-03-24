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
}

void MainWindow::myCmd(QString cmd)
{

}
// 前端调用，
