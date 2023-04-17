#ifndef SOFTWAREMANAGEWIDGET_H
#define SOFTWAREMANAGEWIDGET_H

#include <DWidget>
#include "deviceControlItem.h"
#include <DLineEdit>
#include <DSuggestButton>
#include <DWarningButton>
#include <DPushButton>
#include <DFileDialog>
#include <DComboBox>
#include <DTableView>
#include <DTableWidget>
#include <QStandardItemModel>
#include "softManageTool.h"
#include <DWarningButton>

DWIDGET_USE_NAMESPACE

class SoftwareManageWidget : public DWidget {
    Q_OBJECT
public:
    explicit SoftwareManageWidget(QWidget *parent = nullptr);
    ~SoftwareManageWidget();
    void showSoftList();
    void showDetailInfo(const QModelIndex &index);

    void initUI();

signals:
    void sendMsgToMainWindow(const QString &msg);

private:
    //软件包列表
    DeviceControlItem *softListControl;
    DComboBox *softListOptionBox;
    DPushButton *loadSoftListBtn;
    DTableView *softListTable;
    QStandardItemModel *softListModel;

    //软件包详细信息
    DeviceControlItem *detailInfoControl;
    DTableWidget *softDetailTable;
    QVector<QLabel*> softDetailLabels;
    DPushButton *extractBtn;
    DPushButton *clearDataBtn;
    DPushButton *uninstallBtn;

    //软件安装
    DeviceControlItem *installControl;
    DLineEdit *installSoftPath;
    DSuggestButton *selectSoftBtn;
    DSuggestButton *installBtn;
    SoftManageTool *softTool;
};


#endif
