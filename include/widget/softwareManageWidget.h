#ifndef SOFTWAREMANAGEWIDGET_H
#define SOFTWAREMANAGEWIDGET_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class SoftwareManageWidget : public DWidget {
    Q_OBJECT
public:
    explicit SoftwareManageWidget(QWidget *parent = nullptr);
    ~SoftwareManageWidget();

    void initUI();

private:

};


#endif
