//
// Created by mhduiy on 2023/7/13.
//

#include "MNotificationBox.h"
#include <QDebug>
#include <QLayout>
#include <QFile>

MNotificationWidget::MNotificationWidget(QWidget *mainWindow) : QWidget(mainWindow){
    setFixedSize(360,60);

    contentLabel = new QLabel;
    iconLabel = new QLabel;
    closeBtn = new MButton("");
    closeBtn->setIcon(QIcon(":/closeIcon.png"));

    auto *mainLayout = new QHBoxLayout(this);

    iconLabel->setFixedSize(30,30);
    closeBtn->setFixedSize(30,30);

    iconLabel->setScaledContents(true);

    QFont font;
    font.setFamily("黑体");
    font.setPixelSize(16);
    contentLabel->setFont(font);
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet("color: #ffffff;");

//    contentLayout->addWidget(iconLabel);
//    contentLayout->addWidget(contentLabel);
//    contentLayout->setSpacing(10);

    mainLayout->addWidget(iconLabel, 1);
    mainLayout->addWidget(contentLabel ,4);
    mainLayout->addWidget(closeBtn, 1);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setAutoFillBackground(true);
    this->setStyleSheet("MNotificationWidget{ background-color: #1d1d1d; border: 4px red solid; border-radius: 12px; }");

//    closeBtn->setVisible(false);

    connect(closeBtn, &QPushButton::clicked, this, &MNotificationWidget::closeBtnClicked);
}

MNotificationWidget::~MNotificationWidget() {
    if(contentLabel != nullptr) {
        contentLabel->deleteLater();
    }
    if(iconLabel != nullptr) {
        iconLabel->deleteLater();
    }
    if(closeBtn != nullptr) {
        closeBtn->deleteLater();
    }
}

void MNotificationWidget::setContent(const QString &content, const QIcon &icon) {
    contentLabel->setText(content);
    iconLabel->setPixmap(icon.pixmap(30,30));
}

MNotificationBox::MNotificationBox(QWidget *cutWidget){

    m_animation = new QPropertyAnimation();
    mainWindow = findMainWindow(cutWidget);
    this->setParent(mainWindow);
    msgWidget = new MNotificationWidget(mainWindow);

    m_animation->setTargetObject(msgWidget);
    m_animation->setEasingCurve(QEasingCurve::OutQuint);
    m_animation->setDuration(500);
    m_animation->setPropertyName("pos");

    m_opacityAnimation = new QPropertyAnimation();
    m_opacityAnimation->setTargetObject(msgWidget);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutQuint);
    m_opacityAnimation->setDuration(500);
    m_opacityAnimation->setPropertyName("windowOpacity");

    msgWidget->setVisible(false);
    msgWidget->setWindowOpacity(0);
    msgWidget->raise();

    connect(&timer, &QTimer::timeout, this, &MNotificationBox::closeMsgWidget);
    connect(msgWidget, &MNotificationWidget::closeBtnClicked, this, &MNotificationBox::closeMsgWidget);
}

void MNotificationBox::sendMsg(const QString &content, const QIcon &icon, int _duration) {
    msgWidget->setContent(content, icon);
    this->duration = _duration;
    openMsgWidget();
}

void MNotificationBox::closeMsgWidget() {
    cutPoint = msgWidget->pos();
    tarPoint = QPoint((mainWindow->width() - msgWidget->width()) / 2, -1 * msgWidget->height());
    m_animation->setStartValue(cutPoint);
    m_animation->setEndValue(tarPoint);
    m_animation->start();

    qreal cutOpacity = msgWidget->windowOpacity();
    qreal tarOpacity = 0;
    m_opacityAnimation->setStartValue(cutOpacity);
    m_opacityAnimation->setEndValue(tarOpacity);
    m_opacityAnimation->start();

    timer.stop();
}

void MNotificationBox::openMsgWidget() {
    msgWidget->move(QPoint((mainWindow->width() - msgWidget->width()) / 2, -1 * msgWidget->height()));

    cutPoint = msgWidget->pos();
    tarPoint = cutPoint;
    tarPoint.setX((mainWindow->width() - msgWidget->width()) / 2);
    tarPoint.setY(35);

    msgWidget->setVisible(true);;

    m_animation->setStartValue(cutPoint);
    m_animation->setEndValue(tarPoint);
    m_animation->start();

    qreal cutOpacity = msgWidget->windowOpacity();
    qreal tarOpacity = 1;

    m_opacityAnimation->setStartValue(cutOpacity);
    m_opacityAnimation->setEndValue(tarOpacity);
    m_opacityAnimation->start();

    timer.start(duration * 1000);
}

QWidget *MNotificationBox::findMainWindow(QObject *obj) {
    if(obj == nullptr) {
        return nullptr;
    }
    if(strcmp(obj->metaObject()->className(), "MainTestWindow") == 0) {
        return qobject_cast<QWidget*>(obj);
    }
    return findMainWindow(obj->parent());
}

void MNotificationBox::sendMsg(const QString &content, MsgIconType type, int _duration) {
    QIcon icon;
    switch (type) {
        case MSG_Success: {
            icon = QIcon(":/successIcon.png");
            break;
        }
        case MSG_Warning: {
            icon = QIcon(":/warningIcon.png");
            break;
        }
        case MSG_Error: {
            icon = QIcon(":/errorIcon.png");
            break;
        }
        default: {

        }
    }
    sendMsg(content, icon, _duration);
}
