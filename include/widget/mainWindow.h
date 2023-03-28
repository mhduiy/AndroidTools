#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DWidget>
#include <DPlainTextEdit>
#include <QProcess>
#include "myTypes.h"
#include <DStackedWidget>
#include <QStandardItemModel>
#include <QTimer>
#include "updateThreadTool.h"
#include <QThread>
#include <DComboBox>
#include <DPushButton>
#include "deviceConnect.h"
#include <QSystemTrayIcon>

#include "inforPanelWidget.h"
#include "deviceControlWidget.h"
#include "softwareManageWidget.h"
#include "fileManageWidget.h"
#include "flashToolWidget.h"
#include "deviceImageWidget.h"
#include "terminalWidget.h"


DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();
    void myCmd(QString cmd);
    QString getCurrentDeviceCode();

    void noticeMsg(const QString &msg); //发出提示消息
    void paintBtyIcon(int level);       //画一个电池图标

private:
    DWidget *mainW;

    InfoPannelWidget *infoPannelWidget;         //信息面板
    DeviceControlWidget *deviceControlWidget;   //设备控制
    SoftwareManageWidget *softwareManageWidget; //软件管理
    FileManageWidget *fileManageWidget;         //文件管理
    FlashToolWidget *flashToolWidget;           //刷机工具
    DeviceImageWidget *deviceImageWidget;       //设备镜像
    TerminalWidget *terminalWidget;             //终端

    DStackedWidget *mainStackedWidget;
    DListView *funcView;
    QStandardItemModel *model;
    QTimer timer;
    UpdateThread *updateThreadTool;
    QThread *flashThread;
    DPushButton *flashBtn;
    DComboBox *deviceBox;
    QSystemTrayIcon *sysIcon;                   //托盘图标
};

#endif
