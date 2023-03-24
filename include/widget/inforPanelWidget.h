#ifndef INFORPANELWIDGET_H
#define INFORPANELWIDGET_H


#include <DWidget>
#include <DObject>
#include <DListView>
#include <DStackedWidget>
#include <DTextEdit>
//#include <dcircleprogress.h>
#include "MyCircleProgress.h"
#include <DLabel>
#include <DWaterProgress>
#include <DTableView>
#include <QStandardItemModel>
#include <DComboBox>


DWIDGET_USE_NAMESPACE

class InfoPannelWidget : public DWidget {
    Q_OBJECT
public:
    explicit InfoPannelWidget(QWidget *parent = nullptr);
    ~InfoPannelWidget();

    void initUI();
private:
    DLabel *deviceName;
    MyCircleProgress *btyLevelPg;
    MyCircleProgress *btyTEMPPg;
    MyCircleProgress *memoryPg;
    MyCircleProgress *CPUPg;
    MyCircleProgress *GPUPg;
    DComboBox *deviceBox;

    DTableView *deviceInfo;

    /*test*/
    QStandardItemModel *tableModel;
};

#endif
