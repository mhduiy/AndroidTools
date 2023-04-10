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

DWIDGET_USE_NAMESPACE

class SoftwareManageWidget : public DWidget {
    Q_OBJECT
public:
    explicit SoftwareManageWidget(QWidget *parent = nullptr);
    ~SoftwareManageWidget();

    void initUI();

signals:
    void sendMsgToMainWindow(const QString &msg);

private:
    //软件包列表
    DeviceControlItem *softListControl;
    DComboBox *softListOptionBox;
    DPushButton *loadSoftListBtn;

    //软件包详细信息
    DeviceControlItem *detailInfoControl;

    //软件安装
    DeviceControlItem *installControl;
    DLineEdit *installSoftPath;
    DSuggestButton *selectSoftBtn;
    DSuggestButton *installBtn;

};


#endif
