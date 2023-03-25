#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DWidget>
#include <DPlainTextEdit>
#include <QProcess>
#include "myTypes.h"
#include "inforPanelWidget.h"
#include <DStackedWidget>
#include <QStandardItemModel>
#include <QTimer>
#include "flashThreadTool.h"
#include <QThread>
#include <DComboBox>
#include <DPushButton>
#include "deviceConnect.h"


DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();
    void myCmd(QString cmd);
    QString getCurrentDeviceCode();

private:
    DWidget *mainW;
    InfoPannelWidget *infoPannelWidget;
    DStackedWidget *mainStackedWidget;
    DListView *funcView;
    QStandardItemModel *model;
    QTimer timer;
    FlashThreadTool *flashThreadTool;
    QThread *flashThread;
    DPushButton *flashBtn;
    DComboBox *deviceBox;
};

#endif
