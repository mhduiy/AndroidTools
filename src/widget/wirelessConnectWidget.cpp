#include "wirelessConnectWidget.h"
#include <DDialog>
#include <DFontSizeManager>
#include <DSuggestButton>
#include <QDebug>
#include <DMessageBox>
#include <QDir>
#include <QTextStream>

const QString connCachePath = QDir::homePath() + QDir::separator() + ".config/AndroidTool";
const QString connCacheFileName = "connHistory.log";

WirelessConnectWidget::WirelessConnectWidget(QWidget *parent) : QDialog (parent)
{
    this->setMinimumSize(640,480);
    this->setWindowTitle("无线连接");
    connectSuccess = false;
    initUI();
}

WirelessConnectWidget::~WirelessConnectWidget()
{

}

void WirelessConnectWidget::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainW = new DStackedWidget();
    mainW->setCurrentIndex(0);
    mainLayout->addWidget(mainW);

    for(int i = 0; i < this->TOTALW; i++) {
        DWidget *w = new DWidget();
        itemW.push_back(w);
        mainW->addWidget(w);
    }

    /*准备界面*/
    preEdit = new DTextEdit();
    enterPairBtn = new DSuggestButton("配对设备");
    enterConnectBtn = new DSuggestButton("连接设备");
    preEdit->setReadOnly(true);
    preEdit->setFocusPolicy(Qt::NoFocus);
    preEdit->append("进行无线连接操作之前，需要保证待连接设备满足以下条件：\n");
    preEdit->append("1. 待连接设备安卓版本至少为安卓11\n");
    preEdit->append("2. 打开开发者模式中的无线调试\n");
    preEdit->append("3. PC与待连接设备处于同一局域网中\n\n");
    preEdit->append("若设备没有与电脑连接过或者还未配对该电脑，请选择 '配对设备' 按钮\n");
    preEdit->append("若已经完成配对，请选择 '连接设备' 按钮");


    QVBoxLayout *preLayout = new QVBoxLayout();
    preLayout->addWidget(preEdit);
    preLayout->addWidget(enterPairBtn);
    preLayout->addWidget(enterConnectBtn);
    itemW[PrepareW]->setLayout(preLayout);

    connect(enterPairBtn, &DPushButton::clicked, this, [this](){mainW->setCurrentIndex(PairW);});
    connect(enterConnectBtn, &DPushButton::clicked, this, [this](){mainW->setCurrentIndex(ConnectW);});
    /*配对界面*/
    pairEdit = new DTextEdit();
    pairIpEdit = new DLineEdit();
    pairPortEdit = new DLineEdit();
    pairCodeEdit = new DLineEdit();
    pairBtn = new DSuggestButton("开始配对");
    pairReturnBtn = new DPushButton("返回");

    pairIpEdit->setPlaceholderText("IP地址");
    pairPortEdit->setPlaceholderText("端口号");
    pairCodeEdit->setPlaceholderText("配对码");

    QHBoxLayout *pairBtnsLayout = new QHBoxLayout();
    pairBtnsLayout->addWidget(pairReturnBtn);
    pairBtnsLayout->addWidget(pairBtn);

    QGridLayout *pairGridLayout = new QGridLayout();
    pairGridLayout->setColumnStretch(0,1);
    pairGridLayout->setColumnStretch(1,2);
    pairGridLayout->setColumnStretch(2,1);
    pairGridLayout->addWidget(new DLabel("IP地址:端口: "), 0, 0);
    pairGridLayout->addWidget(pairIpEdit, 0, 1);
    pairGridLayout->addWidget(pairPortEdit, 0, 2);
    pairGridLayout->addWidget(new DLabel("配对码: "), 1, 0);
    pairGridLayout->addWidget(pairCodeEdit, 1, 1, 1, 2);

    pairEdit->setReadOnly(true);
    pairEdit->setFocusPolicy(Qt::NoFocus);
    pairEdit->append("请打开设备无线调试->使用配对码配对设备\n");
    pairEdit->append("填写ip地址，和配对码，然后点击配对设备\n\n");
    pairEdit->append("注意：这里需要填写的ip地址端口来自 '使用配对码配对设备' 界面下，而非无线调试页面中的IP和端口");

    QVBoxLayout *pairLayout = new QVBoxLayout();
    pairLayout->addWidget(pairEdit);
    pairLayout->addLayout(pairGridLayout);
    pairLayout->addLayout(pairBtnsLayout);
    itemW[PairW]->setLayout(pairLayout);

    connect(pairReturnBtn, &DPushButton::clicked, [this](){this->mainW->setCurrentIndex(PrepareW);});
    connect(pairBtn, &DPushButton::clicked, this, &WirelessConnectWidget::startPair);
    /*连接界面*/
    conEdit = new DTextEdit();
    conIpEdit = new DLineEdit();
    conPortEdit = new DLineEdit();
    conBtn = new DSuggestButton("开始连接");
    conReturnbtn = new DPushButton("返回");

    conEdit->setReadOnly(true);
    conEdit->setFocusPolicy(Qt::NoFocus);
    conEdit->append("请打开设备无线调试, 找到ip地址和端口\n");
    conEdit->append("填写ip地址和端口，然后点击连接设备\n\n");

    conIpEdit->setPlaceholderText("IP地址");
    conPortEdit->setPlaceholderText("端口");

    QHBoxLayout *conIpLayout = new QHBoxLayout();
    conIpLayout->addWidget(new DLabel("IP地址:端口: "));
    conIpLayout->addWidget(conIpEdit);
    conIpLayout->addWidget(conPortEdit);

    historyConnBox = new DComboBox();
    QHBoxLayout *histortConnLayout = new QHBoxLayout();
    histortConnLayout->addWidget(new DLabel("通过历史连接记录自动填写"));
    histortConnLayout->addWidget(historyConnBox);

    readConnHistory();

    connect(historyConnBox, QOverload<int>::of(&DComboBox::currentIndexChanged), this, &WirelessConnectWidget::setRightConnFromHistory);

    QHBoxLayout *conBtnsLayout = new QHBoxLayout();
    conBtnsLayout->addWidget(conReturnbtn);
    conBtnsLayout->addWidget(conBtn);

    QVBoxLayout *conLayout = new QVBoxLayout();
    conLayout->addWidget(conEdit);
    conLayout->addLayout(conIpLayout);
    conLayout->addLayout(histortConnLayout);
    conLayout->addLayout(conBtnsLayout);
    itemW[ConnectW]->setLayout(conLayout);

    connect(conReturnbtn, &DPushButton::clicked, [this](){this->mainW->setCurrentIndex(PrepareW);});
    connect(conBtn, &DPushButton::clicked, this, &WirelessConnectWidget::startConnect);
    /*检查界面*/
    connectStatus = new DLabel("检查连接状态...");
    funcBtn = new DSuggestButton("确定");

    connectStatus->setAlignment(Qt::AlignCenter);
    DFontSizeManager::instance()->bind(connectStatus, DFontSizeManager::T4);

    QVBoxLayout *checkLayout = new QVBoxLayout();
    checkLayout->addWidget(connectStatus);
    checkLayout->addWidget(funcBtn);
    itemW[CheckW]->setLayout(checkLayout);

    connect(funcBtn, &DPushButton::clicked, this, [this](){
        if(this->connectSuccess) {
            if(!QFile::exists(connCachePath + QDir::separator() +connCacheFileName)) {
                QDir dir;
                dir.mkdir(connCachePath);
                QFile file(connCachePath + QDir::separator() +connCacheFileName);
                file.open(QIODevice::WriteOnly);
                file.close();
            }
            //保存历史连接记录
            QFile connHisFile(connCachePath + QDir::separator() + connCacheFileName);
            if(connHisFile.open(QIODevice::ReadOnly)) { //读取文件
                QString fileinfo = QString(connHisFile.readAll());
                fileinfo.append(QString(conIpEdit->text() + ':' + conPortEdit->text()));
                QStringList fileinfoList = fileinfo.split('\n');
                int fileinfoSize = fileinfoList.size();
                connHisFile.close();
                if(connHisFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {//清空文件
                    connHisFile.close();
                }
                if(connHisFile.open(QIODevice::WriteOnly)) {//写入文件
                    for(int i = fileinfoSize<=5? 0:fileinfoSize-5; i < fileinfoSize; i++) {
                        connHisFile.write(QString(fileinfoList.value(i) + '\n').toLocal8Bit());
                    }
                    connHisFile.close();
                }

                readConnHistory();
            }
            this->accept();
        }
        else {
            this->reject();
        }
    });
}

int WirelessConnectWidget::exec() {
    mainW->setCurrentIndex(0);
    return QDialog::exec();
}

void WirelessConnectWidget::startPair()
{
    QString ip = pairIpEdit->text();
    QString port = pairPortEdit->text();
    QString pairCode = pairCodeEdit->text();
    if(ip.isEmpty()) {
        pairIpEdit->showAlertMessage("IP地址不能为空");
    }
    if(port.isEmpty()) {
        pairPortEdit->showAlertMessage("端口不能为空");
    }
    if(pairCode.isEmpty()) {
        pairCodeEdit->showAlertMessage("配对码不能为空");
    }
    if(ip.isEmpty() || port.isEmpty() || pairCode.isEmpty()) {
        return;
    }

    bool isPairSuccess = adbTool.pairDevice(ip + ":" + port, pairCode);
    if(!isPairSuccess) {
        DDialog dlg("提示", "配对失败，请检查信息是否填写正确");
        dlg.addButton("好的", true, DDialog::ButtonRecommend);
        dlg.setIcon(QIcon::fromTheme("dialog-information"));
        dlg.exec();
        return;
    }
    DDialog dlg("提示", "配对成功");
    dlg.addButton("好的", true, DDialog::ButtonRecommend);
    dlg.setIcon(QIcon::fromTheme("dialog-information"));
    dlg.exec();
    mainW->setCurrentIndex(PrepareW);
}

void WirelessConnectWidget::startConnect()
{
    QString ip = conIpEdit->text();
    QString port = conPortEdit->text();
    if(ip.isEmpty()) {
        conIpEdit->showAlertMessage("IP地址不能为空");
    }
    if(port.isEmpty()) {
        conPortEdit->showAlertMessage("端口不能为空");
    }
    if(ip.isEmpty() || port.isEmpty()) {
        return;
    }
    QString command = "adb connect %1:%2";
    command = command.arg(ip).arg(port);
    QString&& ret = adbTool.executeCommand(command);
    if(!ret.startsWith("connected to")) {
        DDialog dlg("提示", "连接失败，请检查信息是否填写正确");
        dlg.addButton("好的", true, DDialog::ButtonRecommend);
        dlg.setIcon(QIcon::fromTheme("dialog-information"));
        dlg.exec();
        return;
    }
    DDialog dlg("提示", "连接成功");
    dlg.addButton("好的", true, DDialog::ButtonRecommend);
    dlg.setIcon(QIcon::fromTheme("dialog-information"));
    dlg.exec();
    mainW->setCurrentIndex(CheckW);
    CheckConnect();
}

void WirelessConnectWidget::CheckConnect()
{
    QString ip = conIpEdit->text();
    QString port = conPortEdit->text();
    QString command = "adb -s %1:%2 shell echo suc";
    command = command.arg(ip).arg(port);
    QString&& ret = adbTool.executeCommand(command);
    ret = ret.simplified();
    if(ret != "suc") {
        connectStatus->setText("设备验证失败, 请尝试重新连接");
        connectSuccess = false;
        return;
    }
    else {
        connectStatus->setText("设备验证成功, 点击确定返回");
        connectSuccess = true;
    }
}

void WirelessConnectWidget::setRightConnFromHistory(int index)
{
    if(index == 0) {return;}
    QString &&currentIp = historyConnBox->itemText(index);
    QStringList IPInfo = currentIp.split(":");
    if(IPInfo.size() != 2) {return;}
    conIpEdit->setText(IPInfo.first());
    conPortEdit->setText(IPInfo.last());
}

void WirelessConnectWidget::readConnHistory()
{
    //读取连接历史
    historyConnBox->clear();
    historyConnBox->addItem("请选择");
    QFile connHisFile(connCachePath + QDir::separator() +connCacheFileName);
    connHisFile.open(QIODevice::ReadOnly);
    QTextStream connHisFileStream(&connHisFile);
    QString lineInfo;
    while(!connHisFileStream.atEnd()) {
        lineInfo = connHisFileStream.readLine();
        if(!lineInfo.isEmpty()) {
            historyConnBox->addItem(lineInfo);
        }
    }
    connHisFile.close();
}
