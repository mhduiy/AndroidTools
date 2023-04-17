#ifndef FLASHTOOLWIDGET_H
#define FLASHTOOLWIDGET_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class FlashToolWidget : public DWidget {
    Q_OBJECT
public:
    explicit FlashToolWidget(QWidget *parent = nullptr);
    ~FlashToolWidget();

    void initUI();

signals:
    void sendMsgToMainWindow(const QString &msg);

private:

};


#endif
