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
#include "mybacewidget.h"

DWIDGET_USE_NAMESPACE

class SoftwareManageWidget : public MyBaceWidget {
    Q_OBJECT
public:
    explicit SoftwareManageWidget(QWidget *parent = nullptr);
    ~SoftwareManageWidget();
    void showSoftList();
    void showDetailInfo(const QModelIndex &index);
    void responseBtn(const MHDUIY::OPERATFLAG flag);
    void clearData();
    void deleteApp1();
    void deleteApp2();
    void selectApk();
    void installApp();
    void acceptRetStatus(MHDUIY::OPERATFLAG, bool isSuc);

    void initUI();

signals:
//    void sendMsgToMainWindow(const QString &msg);
    void _clearYes();
    void _deleteYes1();
    void _deleteYes2();

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
    DPushButton *freezeBtn;
    DPushButton *unfreezeBtn;

    //软件安装
    DeviceControlItem *installControl;
    DLineEdit *installSoftPath;
    DSuggestButton *selectSoftBtn;
    DSuggestButton *installBtn;
    SoftManageTool *softTool;
};


#endif
