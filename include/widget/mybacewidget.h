#ifndef MYBACEWIDGET_H
#define MYBACEWIDGET_H

#include <DWidget>
DWIDGET_USE_NAMESPACE

class MyBaceWidget : public DWidget
{
    Q_OBJECT
public:
    MyBaceWidget(DWidget *parent = nullptr);
signals:
    void sendMsgToMainWindow(const QString &msg);
    void startSpinner(const QString& tip);
    void stopSpinner();
};

#endif // MYBACEWIDGET_H
