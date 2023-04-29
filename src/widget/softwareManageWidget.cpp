#include "softwareManageWidget.h"
#include <QLayout>
#include <QHeaderView>
#include <DAlertControl>
#include <DWarningButton>
#include "deviceConnect.h"
#include <QThread>
#include <DDialog>
#include <QStandardPaths>
#include "softtools.h"

SoftwareManageWidget::SoftwareManageWidget(QWidget *parent) : MyBaceWidget(parent)
{
    initUI();
    softTool = SoftManageTool::getInstance();
    connect(SoftTools::getInstance(), &SoftTools::finishOP, this, &SoftwareManageWidget::acceptRetStatus);  //接收执行成功的消息
}

SoftwareManageWidget::~SoftwareManageWidget()
{

}

void SoftwareManageWidget::showSoftList()
{
    QString currentDevice = DeviceConnect::getInstance()->getCurrentDeviceCode();
    if(currentDevice.isEmpty()) {
        emit sendMsgToMainWindow("没有连接任何设备");
        return;
    }
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

void SoftwareManageWidget::responseBtn(const MHDUIY::OPERATFLAG flag)
{
    auto packageNameList =  softListTable->selectionModel()->selectedRows();
    if(packageNameList.size() <= 0 && flag != MHDUIY::OP_INSTALL){
        emit sendMsgToMainWindow("请先在左侧列表中选择软件包！");
        return ;
    }
    QString packageName = packageNameList.value(0).data().toString();
    QString tip;
    switch( flag ){
    case MHDUIY::OP_INSTALL:
        if( !QFile::exists(installSoftPath->text()) || installSoftPath->text().isEmpty() ){
            installSoftPath->showAlertMessage("请选择正确的apk路径！");
            return;
        }
        packageName = installSoftPath->text();
        tip = "正在安装";
        break;
    case MHDUIY::OP_UNINSTALL:
        tip = "正在卸载";
        break;
    case MHDUIY::OP_CLEARDATA:
        tip = "正在清除";
        break;
    case MHDUIY::OP_EXTRACT:
        tip = "正在提取";
        break;
    case MHDUIY::OP_FREEZE:
        tip = "正在冻结";
        break;
    case MHDUIY::OP_UNFREEZE:
        tip = "正在解冻";
        break;
    default:
        break;
    }
    emit startSpinner(tip);
    softTool->operateSoft(flag, packageName);
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
        QLabel *labelValue = new QLabel("");
        softDetailLabels.push_back(labelValue);
        softDetailInfoLayout->addWidget(new QLabel(MHDUIY::SoftInfo::OUTSTR.value(i) + ":"), i-2, 0);
        softDetailInfoLayout->addWidget(labelValue, i-2,1);
    }
    QHBoxLayout *softDetailBtnLayout = new QHBoxLayout();
    softDetailBtnLayout->setSpacing(30);
    extractBtn = new DPushButton("提取软件");

    clearDataBtn = new DWarningButton;
    uninstallBtn = new DWarningButton;
    clearDataBtn->setText("清除数据");
    uninstallBtn->setText("卸载软件");

    softDetailBtnLayout->addWidget(extractBtn);
    softDetailBtnLayout->addWidget(clearDataBtn);
    softDetailBtnLayout->addWidget(uninstallBtn);

    QHBoxLayout *softDetailBtnLayout1 = new QHBoxLayout();
    softDetailBtnLayout->setSpacing(30);
    freezeBtn = new DPushButton("冻结软件");
    unfreezeBtn = new DPushButton("解冻软件");

    softDetailBtnLayout1->addWidget(freezeBtn);
    softDetailBtnLayout1->addWidget(unfreezeBtn);


    detailLayout->addLayout(softDetailInfoLayout);
    detailLayout->addLayout(softDetailBtnLayout);
    detailLayout->addLayout(softDetailBtnLayout1);

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

    //冻结软件响应
    connect(freezeBtn, &DPushButton::clicked, [this](){
        this->responseBtn(MHDUIY::OPERATFLAG::OP_FREEZE);
    });
    //解冻软件响应
    connect(unfreezeBtn, &DPushButton::clicked, [this](){
        this->responseBtn(MHDUIY::OPERATFLAG::OP_UNFREEZE);
    });
    //提取软件响应
    connect(extractBtn, &DPushButton::clicked, [this](){
        this->responseBtn(MHDUIY::OPERATFLAG::OP_EXTRACT);
    });
    //安装软件响应
    connect(installBtn, &DPushButton::clicked, [this](){
        this->responseBtn(MHDUIY::OPERATFLAG::OP_INSTALL);
    });
    //清除数据响应
    connect(clearDataBtn, &DPushButton::clicked, [this](){
        clearData();
    });

    connect(this, &SoftwareManageWidget::_clearYes, [this](){
        this->responseBtn(MHDUIY::OPERATFLAG::OP_CLEARDATA);
    });

    connect(uninstallBtn, &DPushButton::clicked, [this](){
        deleteApp1();
    });
    connect(this, &SoftwareManageWidget::_deleteYes1, [this](){
        deleteApp2();
    });
    connect(this, &SoftwareManageWidget::_deleteYes2, [this](){
        this->responseBtn(MHDUIY::OPERATFLAG::OP_UNINSTALL);
    });

    connect(selectSoftBtn, &DPushButton::clicked, [this](){
        selectApk();
    });
}

void SoftwareManageWidget::clearData(){
    DDialog dlgClear("提示", "确定要清除该软件的数据吗?");
    dlgClear.addButton("是", true, DDialog::ButtonWarning);
    dlgClear.addButton("否", false, DDialog::ButtonNormal);
    dlgClear.setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning));
    int ret = dlgClear.exec();
    qDebug() << ret;
    if(ret != 0) {  //选择了否或者关闭窗口
        return;
    }
    emit this->_clearYes();

}

void SoftwareManageWidget::deleteApp1(){
    DDialog dlgDelete1("提示", "确定要卸载此软件吗?");
    dlgDelete1.addButton("是", true, DDialog::ButtonWarning);
    dlgDelete1.addButton("否", false, DDialog::ButtonNormal);
    dlgDelete1.setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning));
    int ret = dlgDelete1.exec();
    qDebug() << ret;
    if(ret != 0) {  //选择了否或者关闭窗口
        return;
    }
    emit this->_deleteYes1();

}
void SoftwareManageWidget::deleteApp2(){
    DDialog dlgDelete2("二次提示", "确定要卸载此软件吗?");
    dlgDelete2.setStyleSheet("color:red;");
    dlgDelete2.addButton("是", true, DDialog::ButtonWarning);
    dlgDelete2.addButton("否", false, DDialog::ButtonNormal);
    dlgDelete2.setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning));
    int ret = dlgDelete2.exec();
    qDebug() << ret;
    if(ret != 0) {  //选择了否或者关闭窗口
        return;
    }
    emit this->_deleteYes2();

}

void SoftwareManageWidget::selectApk(){

    QString doc_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = QFileDialog::getOpenFileName(this, tr("请选择一个APK"), doc_path, tr("APK Files (*.apk)"));
    installSoftPath->setText(filePath);

    qDebug() << filePath;

    return ;

}

void SoftwareManageWidget::installApp(){

//    this->responseBtn(MHDUIY::OP_INSTALL, installSoftPath->text());
//    return ;
}

void SoftwareManageWidget::acceptRetStatus(MHDUIY::OPERATFLAG flag, bool isSuc)
{
    emit stopSpinner();
    QString tip;
    switch( flag ){
    case MHDUIY::OP_INSTALL:
        tip = "安装";
        break;
    case MHDUIY::OP_UNINSTALL:
        tip = "卸载";
        break;
    case MHDUIY::OP_CLEARDATA:
        tip = "清除";
        break;
    case MHDUIY::OP_EXTRACT:
        tip = "文件保存在系统文档目录中，提取";
        break;
    case MHDUIY::OP_FREEZE:
        tip = "冻结";
        break;
    case MHDUIY::OP_UNFREEZE:
        tip = "解冻";
        break;
    default:
        break;
    }
    if(isSuc) {
        emit sendMsgToMainWindow(tip + "成功!");
    }
    else {
        emit sendMsgToMainWindow(tip + "失败!");
    }
}
