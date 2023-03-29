#include "wirelessConnectWidget.h"

WirelessConnectWidget::WirelessConnectWidget(QWidget *parent) : QDialog (parent)
{
    this->setMinimumSize(640,480);
    this->setWindowTitle("无线连接");
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
    enterPairBtn = new DPushButton("配对设备");
    enterConnectBtn = new DPushButton("连接设备");

    preEdit->setReadOnly(true);
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
    /*配对界面*/
    pairEdit = new DTextEdit();
    ipEdit = new DIpv4LineEdit();
    pairCodeEdit = new DLineEdit();
    pairBtn = new DPushButton("开始配对");
    returnBtn = new DPushButton("返回");

//    ipEdit->set

    pairEdit->setReadOnly(true);
    pairEdit->append("请打开设备无线调试->使用配对码配对设备\n");
    pairEdit->append("填写ip地址，和配对码，然后点击配对设备\n\n");
    pairEdit->append("注意：这里需要填写的ip地址端口来自 '使用配对码配对设备' 界面下，而非无线调试页面中的IP和端口");

    QVBoxLayout *pairLayout = new QVBoxLayout();
    pairLayout->addWidget(pairEdit);
    pairLayout->addWidget(ipEdit);
    pairLayout->addWidget(pairCodeEdit);
    pairLayout->addWidget(pairBtn);
    itemW[PairW]->setLayout(pairLayout);
    /*连接界面*/

    /*检查界面*/
}
