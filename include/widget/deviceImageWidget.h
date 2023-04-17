#ifndef DEVICEIMAGEWIDGET_H
#define DEVICEIMAGEWIDGET_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class DeviceImageWidget : public DWidget {
    Q_OBJECT
public:
    explicit DeviceImageWidget(QWidget *parent = nullptr);
    ~DeviceImageWidget();

    void initUI();

signals:
    void sendMsgToMainWindow(const QString &msg);

private:

};


#endif
