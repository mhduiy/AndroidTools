//
// Created by mhduiy on 2023/7/13.
//

#ifndef SIMPLYTOOLS_MNOTIFICATIONBOX_H
#define SIMPLYTOOLS_MNOTIFICATIONBOX_H
#include <QWidget>
#include <QLabel>
#include "MButton.h"
#include <QIcon>
#include <QTimer>
#include <QPropertyAnimation>

enum MsgIconType {MSG_Success = 0, MSG_Warning, MSG_Error};

class MNotificationWidget : public QWidget {
    Q_OBJECT
public:
    explicit MNotificationWidget(QWidget *mainWindow);
    ~MNotificationWidget() override;
    void setContent(const QString &content, const QIcon& icon = QIcon());

signals:
    void closeBtnClicked();

private:
    QLabel *contentLabel = nullptr;
    QLabel *iconLabel = nullptr;
    MButton *closeBtn = nullptr;;
};

class MNotificationBox : public QObject{
Q_OBJECT
public:
    explicit MNotificationBox(QWidget *cutWidget);
    void sendMsg(const QString &content, const QIcon& icon = QIcon(), int duration = 2);
    void sendMsg(const QString &content, MsgIconType type, int duration = 2);
    void closeMsgWidget();
    void openMsgWidget();

private:
    // 寻找主窗口
    QWidget* findMainWindow(QObject *obj);
    int duration = 3;   //消息对话框持续时间
    QWidget *mainWindow = nullptr;
    MNotificationWidget *msgWidget = nullptr;
    QPropertyAnimation *m_animation = nullptr;        //动画对象指针;
    QPropertyAnimation *m_opacityAnimation = nullptr;        //动画对象指针;

    QPoint cutPoint;
    QPoint tarPoint;

    QTimer timer;
};


#endif //SIMPLYTOOLS_MNOTIFICATIONBOX_H
