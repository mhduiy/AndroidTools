#include "terminalWidget.h"
#include <QLayout>

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
    textBrowser = new DTextBrowser();
    QHBoxLayout *controlLayout = new QHBoxLayout();
    execBtn = new DSuggestButton("执行");
    clearBtn = new DSuggestButton("清除");
    commandEdit = new DLineEdit();
    commandEdit->setPlaceholderText("在这里输入命令");
    controlLayout->addWidget(commandEdit);
    controlLayout->addWidget(execBtn);
    controlLayout->addWidget(clearBtn);
    controlLayout->setStretch(0,5);
    controlLayout->setStretch(1,1);
    controlLayout->setStretch(2,1);

    mainLayout->addWidget(textBrowser);
    mainLayout->addLayout(controlLayout);

    connect(execBtn, &DPushButton::clicked, [this](){   //按下执行按钮
        QString &&cmd = commandEdit->text();
        QString &&ret = adbTool.executeCommand(cmd);
        textBrowser->append(QString(R"(命令:  %1  )").arg(cmd) + "执行结果：\n" + ret + "\n");
        commandEdit->clear();
    });
    connect(clearBtn, &DPushButton::clicked, [this](){  //按下清除按钮
        commandEdit->clear();
        textBrowser->clear();
    });
    connect(commandEdit, &DLineEdit::returnPressed, [this](){
        if(commandEdit->hasFocus()){
            QString &&cmd = commandEdit->text();
            QString &&ret = adbTool.executeCommand(cmd);
            textBrowser->append(QString(R"(命令:  %1  )").arg(cmd) + "执行结果：\n" + ret + "\n");
            commandEdit->clear();
        }
    });
}
