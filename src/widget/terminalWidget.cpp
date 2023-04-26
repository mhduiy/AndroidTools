#include "terminalWidget.h"
#include <QLayout>
#include <QClipboard>
#include <QGuiApplication>

TerminalWidget::TerminalWidget(QWidget *parent) : DWidget (parent)
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
    pasteBtn->setFixedWidth(120);
    clearBtn->setFixedWidth(120);
    controlLayout->setStretch(0,1);
    controlLayout->setStretch(1,1);
    controlLayout->setSpacing(20);
    controlLayout->setAlignment(Qt::AlignLeft);

    controlLayout->addWidget(pasteBtn);
    controlLayout->addWidget(clearBtn);

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
    //读取剪切板数据
    connect(pasteBtn, &DPushButton::clicked, [this](){
        QClipboard *clipboard = QGuiApplication::clipboard();
        QString info = clipboard->text();
        this->textBrowser->append(info);
    });
}
