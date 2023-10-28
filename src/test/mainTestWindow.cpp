#include "mainTestWindow.h"
#include <QLayout>

MainTestWindow::MainTestWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    mainLayout->setAlignment(Qt::AlignHCenter);

    m_btnOrdinary = new MButton("发送成功通知消息", MBtn_ordinary);
    m_btnSuggest = new MButton("发送警告通知消息", MBtn_suggested);
    m_btnWarning = new MButton("发送错误通知消息", MBtn_warning);
    m_lineEdit = new MLineEdit();
    m_sideBar = new MSidebar();
    m_tabSwitchButton = new MTabSwitchButton();
    m_notificationBox = new MNotificationBox(this);

    m_lineEdit->setTipText("输入账户名");
    m_lineEdit->setFixedWidth(200);

    m_tabSwitchButton->addItem("测试1");
    m_tabSwitchButton->addItem("测试2");
    m_tabSwitchButton->addItem("测试3");

    mainLayout->addWidget(m_tabSwitchButton);
    mainLayout->addWidget(m_lineEdit);
    mainLayout->addWidget(m_btnOrdinary);
    mainLayout->addWidget(m_btnSuggest);
    mainLayout->addWidget(m_btnWarning);

    connect(m_btnOrdinary, &MButton::clicked, this, [this](){
        m_notificationBox->sendMsg("这是一条测试消息", MsgIconType::MSG_Success, 2);
    });
    connect(m_btnSuggest, &MButton::clicked, this, [this](){
        m_notificationBox->sendMsg("这是一条测试消息", MsgIconType::MSG_Warning, 2);
    });
    connect(m_btnWarning, &MButton::clicked, this, [this](){
        m_notificationBox->sendMsg("这是一条测试消息", MsgIconType::MSG_Error, 2);
    });

    setCentralWidget(mainWidget);
}