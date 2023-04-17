#ifndef DEVICECONTROLITEM_H
#define DEVICECONTROLITEM_H

#include <DWidget>
#include <QLayout>
#include <DGroupBox>
#include <DLabel>
#include <DPushButton>
#include <DLineEdit>


DWIDGET_USE_NAMESPACE

class DeviceControlItem : public DWidget{
public:
    explicit DeviceControlItem(DWidget *mainW,  DWidget *parent = nullptr);
    ~DeviceControlItem();
    void initUI(DWidget *mainW);
    void setTitle(const QString &title);
    void setWidget(DWidget *w);
    void setDescribe(const QString &describe);
private:
    DGroupBox *box;         //控件盒
    DLabel *title;          //标题
    DLabel *describe;       //描述
    DWidget *w = nullptr;             //下方widget
};

#endif
