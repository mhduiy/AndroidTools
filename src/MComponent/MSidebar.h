//
// Created by mhduiy on 2023/7/11.
//

#ifndef SIMPLYTOOLS_MSIDEBAR_H
#define SIMPLYTOOLS_MSIDEBAR_H

#include <QWidget>
#include <QListWidget>
#include "MButton.h"
#include <QTimer>
#include <QMouseEvent>
#include <QPropertyAnimation>

class MSidebar : public QWidget{
Q_OBJECT
public:
    explicit MSidebar(QWidget *parent = nullptr);
    void addWidgetItem(const QString &text, const QIcon& icon);
    void setCurrentIndex(int index);

signals:
    void currentIndexChanged(int cutIndex);

protected:
    void showEvent(QShowEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
public slots:
    void foldPage(bool toFolded = true);
private:
    // 初始化界面
    void initUI();
    bool isFolded = false;
    QListWidget *listWidget = nullptr;
    QPushButton *foldBtn = nullptr;
    QTimer animationTimer;

    QPoint cutPos;
    QPoint tarPos;
    QPixmap arrowIcon;

    bool isFirstShow = true;
    QPropertyAnimation *m_animation;        //动画对象指针
};

#endif //SIMPLYTOOLS_MSIDEBAR_H
