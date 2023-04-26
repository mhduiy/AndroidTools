#ifndef DEVICEIMAGEWIDGET_H
#define DEVICEIMAGEWIDGET_H

#include <DWidget>
#include <QLayout>
#include "ADBTools.h"
#include "deviceConnect.h"
#include "deviceControlItem.h"
#include <DFrame>
#include <QImage>
#include <QLabel>
#include <DSuggestButton>

DWIDGET_USE_NAMESPACE

class DeviceImageWidget : public DWidget {
    Q_OBJECT
public:
    explicit DeviceImageWidget(QWidget *parent = nullptr);
    ~DeviceImageWidget();

    void initUI();
    void screenshotFromDevice();
    bool saveCurrentDeviceImage();

signals:
    void sendMsgToMainWindow(const QString &msg);

private:
    DLabel *deviceImgLabel;
    DSuggestButton *FlashCurrentImageBtn;
    DSuggestButton *saveImageBtn;
    QImage *deviceCurrentFrameImg;      //设备现在的画面
    ADBTools adbTool;
    DFrame *imageFrame;
};


#endif
