//
// Created by mhduiy on 2023/7/11.
//

#include "MButton.h"
#include "Global/globalType.hpp"

#include <QDebug>
#include <QPainter>

MButton::MButton(const QString &text, Category type, QWidget *parent)
: QWidget(parent)
, m_category(type)
, m_text(text)
, m_backColorAni(new QVariantAnimation(this))
{
    initData();
    setFixedHeight(36);
}

void MButton::setCategory(Category category)
{
    m_category = category;
    initData();
    update();
}

void MButton::setText(const QString &text)
{
    m_text = text;
    update();
}

void MButton::initData()
{
    m_backColorAni->setDuration(300);
    m_backColorAni->setEasingCurve(QEasingCurve::Linear);
    if (m_category == MBtn_ordinary) {
        m_foregroundColor = MColor_OrdinaryForeColor;
        m_backgroundColor = MColor_OrdinaryBackColor;
        m_backColorAni->setStartValue(MColor_OrdinaryBackColor);
        m_backColorAni->setEndValue(MColor_OrdinaryHoverBackColor);
    } else if (m_category == MBtn_suggested) {
        m_foregroundColor = MColor_SuggestForeColor;
        m_backgroundColor = MColor_SuggestBackColor;
        m_backColorAni->setStartValue(MColor_SuggestBackColor);
        m_backColorAni->setEndValue(MColor_SuggestHoverBackColor);
    } else {
        m_foregroundColor = MColor_WarningForeColor;
        m_backgroundColor = MColor_WarningBackColor;
        m_backColorAni->setStartValue(MColor_WarningBackColor);
        m_backColorAni->setEndValue(MColor_WarningHoverBackColor);
    }

    connect(m_backColorAni, &QVariantAnimation::valueChanged, this, [this](const QVariant &data){
        setBackgroundColor(data.value<QColor>());
    });
}

void MButton::startAni()
{
    if(m_hover) {
        m_backColorAni->setDirection(QAbstractAnimation::Forward);
    } else {
        m_backColorAni->setDirection(QAbstractAnimation::Backward);
    }
    m_backColorAni->start();
}

void MButton::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

void MButton::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    update();
}

void MButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 防止边缘绘制奇怪
    QRect btnRect = rect().marginsRemoved(QMargins(1, 1, 1, 1));

    QPen pen;
    pen.setColor(m_foregroundColor);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(m_backgroundColor);
    painter.drawRoundedRect(btnRect, 10, 10);

    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);
    QFont font;
    font.setFamily("黑体");
    painter.drawText(btnRect, m_text, textOption);

    if(!m_icon.isNull())
        painter.drawPixmap(btnRect, m_icon.pixmap(rect().size()));

    QWidget::paintEvent(e);
}
void MButton::enterEvent(QEvent *e)
{
    m_hover = true;
    startAni();
    update();
    QWidget::enterEvent(e);
}
void MButton::leaveEvent(QEvent *e)
{
    m_hover = false;
    startAni();
    update();
    QWidget::leaveEvent(e);
}
void MButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(rect().contains(mapFromGlobal(QCursor::pos())))
        emit clicked();

    QWidget::mouseReleaseEvent(e);
}