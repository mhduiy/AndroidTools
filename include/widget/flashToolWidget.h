#ifndef FLASHTOOLWIDGET_H
#define FLASHTOOLWIDGET_H

#include <DWidget>
//#include <dtickeffect.h>
#include <DLabel>
#include "deviceControlItem.h"
#include <DComboBox>
#include <DIconButton>
#include <DWarningButton>
#include <DSuggestButton>
#include <DRadioButton>
#include <DCheckBox>


DWIDGET_USE_NAMESPACE

class FlashToolWidget : public DWidget {
    Q_OBJECT
public:
    explicit FlashToolWidget(QWidget *parent = nullptr);
    ~FlashToolWidget();

    void initUI();

signals:
    void sendMsgToMainWindow(const QString &msg);
private:
    void responseFastRebootBtn(int i);    //响应快速重启按钮

private:
//    DTickEffect *warningEffect;     //警示控件

    DComboBox *deviceBox;
    DIconButton *updateBtn;

    /*刷写分区*/
    DeviceControlItem *flashPartitionControl;
    QComboBox *targetPartition;
    DLineEdit *FlashImgPathEdit;
    DSuggestButton *flashBtn;
    DSuggestButton *selectFlashImgBtn;
    /*临时启动*/
    DeviceControlItem *tempStartImgControl;
    DLineEdit *tempStartPathEdit;
    DSuggestButton *selectStartImgBtn;
    DSuggestButton *tempStartBtn;
    /*清除分区*/
    DeviceControlItem *clearPartitionControl;
    QComboBox *clearPartitionBox;
    DSuggestButton *clearBtn;
    /*解包*/
    DeviceControlItem *unPackControl;
    DLineEdit *unPackPathEdit;
    DSuggestButton *selectUnPackBtn;
    DCheckBox *isUnPackPayload;  //是否解包Payload.img
    DSuggestButton *unPackBtn;
    DPushButton *openUnPackOutDir;

    /*快捷重启*/
    DeviceControlItem *fastRebootControl;
    QVector<QPushButton *> fastRebootBtns;
    /*快捷链接*/
};


#endif
