#include "terminalWidget.h"
#include <QLayout>
#include <QClipboard>
#include <QGuiApplication>
#include <QApplication>

TerminalWidget::TerminalWidget(QWidget *parent)  : MyBaceWidget(parent)
{
    initUI();
}

TerminalWidget::~TerminalWidget()
{

}

void TerminalWidget::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    textBrowser = new TerminalTextEdit();
    textBrowser->setFocusPolicy(Qt::StrongFocus);   //设置强焦点

    QHBoxLayout *controlLayout = new QHBoxLayout();
    pasteBtn = new DSuggestButton("从剪切板粘贴");
    clearBtn = new DSuggestButton("清除");
    openExternalTerminalBtn = new DSuggestButton("打开系统终端");
    pasteBtn->setFixedWidth(120);
    clearBtn->setFixedWidth(120);
    openExternalTerminalBtn->setFixedWidth(120);
    controlLayout->setStretch(0,1);
    controlLayout->setStretch(1,1);
    controlLayout->setSpacing(20);
    controlLayout->setAlignment(Qt::AlignLeft);

    controlLayout->addWidget(pasteBtn);
    controlLayout->addWidget(clearBtn);
    controlLayout->addWidget(openExternalTerminalBtn);

    mainLayout->addWidget(textBrowser);
    mainLayout->addLayout(controlLayout);
    //按下回车键， 执行命令
    connect(textBrowser, &TerminalTextEdit::returnPressed, [this](const QString &cmd){
        if(cmd.isEmpty()) {
            return;
        }
        QString &&ret = adbTool.executeCommand(cmd);
        this->textBrowser->setCommandRetInfo(ret);
    });

    connect(clearBtn, &DPushButton::clicked, [this](){  //按下清除按钮
        textBrowser->clear();
    });
    //打开系统终端，指向程序的adb目录
    connect(openExternalTerminalBtn, &DPushButton::clicked, [this](){
        QProcess::startDetached(QString("deepin-terminal -w %1").arg(QApplication::applicationDirPath() + "/../tools/platform-tools"));
    });
    //读取剪切板数据
    connect(pasteBtn, &DPushButton::clicked, [this](){
        QClipboard *clipboard = QGuiApplication::clipboard();
        QString info = clipboard->text();
        this->textBrowser->append(info);
    });
}
