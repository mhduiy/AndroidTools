#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <DWidget>
#include <DTextEdit>
#include "ADBTools.h"
#include "deviceConnect.h"
#include <DSuggestButton>
#include <DLineEdit>
#include "terminaltextedit.h"
#include "mybacewidget.h"


DWIDGET_USE_NAMESPACE

class TerminalWidget : public MyBaceWidget {
    Q_OBJECT
public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    ~TerminalWidget();

    void initUI();

signals:

private:
    TerminalTextEdit *textBrowser;
    ADBTools adbTool;
    DSuggestButton *pasteBtn;
    DPushButton *clearBtn;
    DPushButton *openExternalTerminalBtn;   //打开外部终端
};


#endif
