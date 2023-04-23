#include "softwareManageWidget.h"
#include <QLayout>
#include <QHeaderView>
#include <DAlertControl>
#include <DWarningButton>

SoftwareManageWidget::SoftwareManageWidget(QWidget *parent) : DWidget (parent)
{
    initUI();
    softTool = SoftManageTool::getInstance();
}

SoftwareManageWidget::~SoftwareManageWidget()
{

}

void SoftwareManageWidget::showSoftList()
{
    QStringList &&list = softTool->getSoftList(static_cast<SoftManageTool::SOFTFLAG>(softListOptionBox->currentData().toInt()));
    softListModel->clear();
    for(auto &it : list) {
        softListModel->appendRow(new QStandardItem(it));
    }
}

void SoftwareManageWidget::showDetailInfo(const QModelIndex &index)
{
    qDebug() << index.data();
    MHDUIY::SoftInfo _info = softTool->getSoftInfo(index.data().toString());

    // 不显示描述，标题位置显示包名
    //detailInfoControl->setTitle(_info.info[MHDUIY::SoftInfo::Name]);
    //detailInfoControl->setDescribe(_info.info[MHDUIY::SoftInfo::PackageName]);
    detailInfoControl->setTitle(_info.info[MHDUIY::SoftInfo::PackageName]);

    for(int i = 2; i < MHDUIY::SoftInfo::TOTAL; i++) {  //去除软件名和包名
//        softDetailLabels.value(i-2)->setText(_info.info.value(i));
        softDetailLabels.value(i-2)->setText( _info.info.value(i).isEmpty() ? "无" : _info.info.value(i) );

    }

}

void SoftwareManageWidget::responseBtn(const SoftManageTool::OPERATFLAG flag)
{
    // QString packageName =  "None";
    auto packageNameList =  softListTable->selectionModel()->selectedRows();
    if(packageNameList.size() <= 0){
        emit sendMsgToMainWindow("请先在左侧列表中选择软件包！");

        return ;
    }
    softTool->operateSoft(flag, packageNameList.first().data().toString());
    return ;
}

void SoftwareManageWidget::initUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    /*软件包列表*/
    DWidget *softListW = new DWidget();
    softListControl = new DeviceControlItem(softListW);
    softListControl->setTitle("软件包列表");
    softListControl->setDescribe("通过下方加载列表按钮来加载设备软件包列表");
    QVBoxLayout * softListLayout = new QVBoxLayout(softListW);

    softListOptionBox = new DComboBox();
    loadSoftListBtn = new DSuggestButton("加载列表");
    softListOptionBox->addItem("全部", QVariant(SoftManageTool::SOFT_TOTAL));
    softListOptionBox->addItem("系统应用", QVariant(SoftManageTool::SOFT_SYS));
    softListOptionBox->addItem("第三方应用", QVariant(SoftManageTool::SOFT_THIRD));

    connect(loadSoftListBtn, &DPushButton::clicked, this, &SoftwareManageWidget::showSoftList);

    softListTable = new DTableView();
    softListTable->setAlternatingRowColors(true);
    softListTable->horizontalHeader()->setVisible(false);
    softListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    softListTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    softListTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    softListTable->setSelectionMode(QAbstractItemView::SingleSelection);    //设置单行选中
    softListTable->setSortingEnabled(true);//设置可以排序
    connect(softListTable, &DTableView::clicked, this, &SoftwareManageWidget::showDetailInfo);


    softListModel = new QStandardItemModel();
    softListTable->setModel(softListModel);


    QHBoxLayout *softListOptionLayout = new QHBoxLayout();
    softListOptionLayout->addWidget(softListOptionBox);
    softListOptionLayout->addWidget(loadSoftListBtn);

    softListLayout->addLayout(softListOptionLayout);
    softListLayout->addWidget(softListTable);
    /*软件包详细信息*/
    DWidget *detailW = new DWidget();
    detailInfoControl = new DeviceControlItem(detailW);
    detailInfoControl->setTitle("360安全卫士");
    //  detailInfoControl->setDescribe("这里是包名");
    QVBoxLayout *detailLayout = new QVBoxLayout(detailW);
    detailLayout->setSpacing(30);
    QGridLayout *softDetailInfoLayout = new QGridLayout();
    softDetailInfoLayout->setSpacing(15);
    softDetailInfoLayout->setColumnStretch(0,1);
    softDetailInfoLayout->setColumnStretch(1,3);
    for(int i = 2; i < MHDUIY::SoftInfo::TOTAL; i++) {  //去除软件名和包名
        QLabel *labelValue = new QLabel("测试数据");
        softDetailLabels.push_back(labelValue);
        softDetailInfoLayout->addWidget(new QLabel(MHDUIY::SoftInfo::OUTSTR.value(i) + ":"), i-2, 0);
        softDetailInfoLayout->addWidget(labelValue, i-2,1);
    }
    QHBoxLayout *softDetailBtnLayout = new QHBoxLayout();
    softDetailBtnLayout->setSpacing(30);
    extractBtn = new DPushButton("提取软件");

    DWarningButton *clearDataBtn = new DWarningButton;
    DWarningButton *uninstallBtn = new DWarningButton;
    clearDataBtn->setText("清除数据");
    uninstallBtn->setText("卸载软件");

    softDetailBtnLayout->addWidget(extractBtn);
    softDetailBtnLayout->addWidget(clearDataBtn);
    softDetailBtnLayout->addWidget(uninstallBtn);

    detailLayout->addLayout(softDetailInfoLayout);
    detailLayout->addLayout(softDetailBtnLayout);

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



    connect(extractBtn, &DPushButton::clicked, [this](){
        this->responseBtn(SoftManageTool::OPERATFLAG::OP_EXTRACT);
    });
    connect(clearDataBtn, &DPushButton::clicked, [this](){
        this->responseBtn(SoftManageTool::OPERATFLAG::OP_EXTRACT);
    });
    connect(uninstallBtn, &DPushButton::clicked, [this](){
        this->responseBtn(SoftManageTool::OPERATFLAG::OP_EXTRACT);
    });
    connect(installBtn, &DPushButton::clicked, [this](){
        this->responseBtn(SoftManageTool::OPERATFLAG::OP_EXTRACT);
    });


}
