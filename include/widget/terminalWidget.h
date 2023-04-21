#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <DWidget>
#include <DTextBrowser>
#include "ADBTools.h"
#include "deviceConnect.h"
#include <DSuggestButton>
#include <DLineEdit>

DWIDGET_USE_NAMESPACE

class TerminalWidget : public DWidget {
    Q_OBJECT
public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    ~TerminalWidget();

    void initUI();

signals:
    void sendMsgToMainWindow(const QString &msg);

private:
    DTextBrowser *textBrowser;  //临时功能
    ADBTools adbTool;
    DPushButton *execBtn;
    DPushButton *clearBtn;
    DLineEdit *commandEdit;
};


#endif
