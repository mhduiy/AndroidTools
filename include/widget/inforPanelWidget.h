#ifndef INFORPANELWIDGET_H
#define INFORPANELWIDGET_H


#include <DWidget>
#include <DObject>
#include <DListView>
#include <DStackedWidget>
#include <DTextEdit>
//#include <dcircleprogress.h>
#include "MyCircleProgress.h"
#include <DLabel>
#include <DWaterProgress>
#include <DTableView>
#include <QStandardItemModel>
#include <DComboBox>
#include "myTypes.h"
#include <DPushButton>
#include <DFrame>
#include "deviceControlItem.h"


DWIDGET_USE_NAMESPACE

class InfoPannelWidget : public DWidget {
    Q_OBJECT
public:
    explicit InfoPannelWidget(QWidget *parent = nullptr);
    ~InfoPannelWidget();
    void initUI();
    void setInfoToRealTimePG(MHDUIY::deviceRealTimeInfo *info);
    void setInfoToDetialsTable(MHDUIY::deviceDetailsInfo *info);
signals:
    void flashDevice();
    void sendMsgToMainWindow(const QString &msg);

private:
    DLabel *deviceName;
    QVector<MyCircleProgress*> deviceRealTimePG;    //实时面板
    DTableView *deviceInfoTable;    //设备信息表格
    QStandardItemModel *tableModel;
    DeviceControlItem *baseInfoControl;     //设备基础信息列表
    DeviceControlItem *currentActivityControl;  //设备当前活动
};

#endif
