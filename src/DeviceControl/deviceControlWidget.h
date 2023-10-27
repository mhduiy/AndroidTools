#ifndef DEVICECONTROLWIDGET_H
#define DEVICECONTROLWIDGET_H

#include <QWidget>

class DeviceControlWidget : public QWidget {
    Q_OBJECT
public:
    explicit DeviceControlWidget(QWidget *parent = nullptr);
    ~DeviceControlWidget();
};


#endif
