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
#include "mybacewidget.h"

DWIDGET_USE_NAMESPACE

class DeviceImageWidget : public MyBaceWidget {
    Q_OBJECT
public:
    explicit DeviceImageWidget(QWidget *parent = nullptr);
    ~DeviceImageWidget();

    void initUI();
    void screenshotFromDevice();
    bool saveCurrentDeviceImage();

signals:

private:
    DLabel *deviceImgLabel;
    DSuggestButton *FlashCurrentImageBtn;
    DSuggestButton *saveImageBtn;
    QImage *deviceCurrentFrameImg;      //设备现在的画面
    ADBTools adbTool;
    DFrame *imageFrame;
};


#endif
