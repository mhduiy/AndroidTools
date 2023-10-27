#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "InfoPanel/inforPanelWidget.h"
#include "DeviceControl/deviceControlWidget.h"
#include "AppManage/appManageWidget.h"
#include "FlashingTool/flashingToolWidget.h"
#include "ScreenMirroring/screenMirroringWidget.h"
#include "TerminalTool/terminalToolWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    InfoPanelWidget *infoPanelWidget;         //信息面板
    DeviceControlWidget *deviceControlWidget;   //设备控制
    AppManageWidget *appManageWidget; //软件管理
    FlashingWidget *flashingWidget;           //刷机工具
    ScreenMirroringWidget *ScreenMirroringWidget;                   //设备镜像
    TerminalToolWidget *terminalToolWidget;             //终端
};

#endif
