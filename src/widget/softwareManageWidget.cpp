#include "softwareManageWidget.h"
#include <QLayout>
#include <DAlertControl>

SoftwareManageWidget::SoftwareManageWidget(QWidget *parent) : DWidget (parent)
{
    initUI();
}

SoftwareManageWidget::~SoftwareManageWidget()
{

}

void SoftwareManageWidget::initUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    /*软件包列表*/
    DWidget *softListW = new DWidget();
    softListControl = new DeviceControlItem(softListW);
    softListControl->setTitle("软件包列表");
    QVBoxLayout * softListLayout = new QVBoxLayout(softListW);

    softListOptionBox = new DComboBox();
    loadSoftListBtn = new DSuggestButton("加载列表");
    softListOptionBox->addItems({"全部","系统应用","第三方应用"});

    QHBoxLayout *softListOptionLayout = new QHBoxLayout();
    softListOptionLayout->addWidget(softListOptionBox);
    softListOptionLayout->addWidget(loadSoftListBtn);

    softListLayout->addLayout(softListOptionLayout);
    /*软件包详细信息*/
    DWidget *detailW = new DWidget();
    detailInfoControl = new DeviceControlItem(detailW);
    detailInfoControl->setTitle("360安全卫士");
    QVBoxLayout * detailLayout = new QVBoxLayout(detailW);
    /*软件安装*/
    DWidget *installW = new DWidget();
    installControl = new DeviceControlItem(installW);
    installControl->setTitle("安装软件");
    installControl->setDescribe("选择一个软件包，发送到设备进行安装");
    QVBoxLayout *installLayout = new QVBoxLayout(installW);

    installSoftPath  = new DLineEdit();
    selectSoftBtn = new DSuggestButton("选择");
    installBtn = new DSuggestButton("安装");

    QHBoxLayout *softPathLayout = new QHBoxLayout();
    softPathLayout->addWidget(new DLabel("软件包路径: "));
    softPathLayout->addWidget(installSoftPath);
    softPathLayout->addWidget(selectSoftBtn);
    installLayout->addLayout(softPathLayout);
    installLayout->addWidget(installBtn);


    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(detailInfoControl);
    rightLayout->addWidget(installControl);
    rightLayout->setAlignment(installControl, Qt::AlignBottom);

    mainLayout->addWidget(softListControl);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretch(0,1);
    mainLayout->setStretch(1,1);
}
