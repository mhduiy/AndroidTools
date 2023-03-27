#ifndef DEVICECONTROLWIDGET_H
#define DEVICECONTROLWIDGET_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class DeviceControlWidget : public DWidget {
    Q_OBJECT
public:
    explicit DeviceControlWidget(QWidget *parent = nullptr);
    ~DeviceControlWidget();

    void initUI();

private:

};


#endif
