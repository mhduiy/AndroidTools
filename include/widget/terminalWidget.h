#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <DWidget>

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

};


#endif
