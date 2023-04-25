#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <DWidget>
#include <DTextEdit>
#include "ADBTools.h"
#include "deviceConnect.h"
#include <DSuggestButton>
#include <DLineEdit>
#include "terminaltextedit.h"

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
    TerminalTextEdit *textBrowser;
    ADBTools adbTool;
    DSuggestButton *pasteBtn;
    DPushButton *clearBtn;
};


#endif
