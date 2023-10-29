#include "MSwitchButton.h"
#include <QDebug>
#include "Global/globalType.hpp"

MSwitchButton::MSwitchButton(QWidget *parent)
: QWidget(parent)
, m_hover(false)
, m_isOn(false)
, m_posAni(new QVariantAnimation(this))
, m_foreColorAni(new QVariantAnimation(this))
, m_backColorAni(new QVariantAnimation(this))   
, m_backHoverColorAni(new QVariantAnimation(this))
{
    setFixedSize(50, 25);
    btnRect = rect().marginsRemoved(QMargins(1, 1, 1, 1));
    if (m_isOn) {
        m_foreColor = MColor_SuggestForeColor;
        m_backColor = MColor_SuggestBackColor;
        m_ballRect = QRectF(btnRect.topRight() - QPoint(m_padding + btnRect.height() - 2 * m_padding, -1 * m_padding), QSize(btnRect.height() - 2 * m_padding, btnRect.height() - 2 * m_padding));
    } else {
        m_backColor = MColor_OrdinaryBackColor;
        m_foreColor = MColor_OrdinaryForeColor;
        m_ballRect = QRectF(btnRect.topLeft() + QPoint(m_padding, m_padding), QSize(btnRect.height() - 2 * m_padding, btnRect.height() - 2 * m_padding));
    }
    initData();
}

void MSwitchButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 画矩形
    QPen pen;
    pen.setWidth(2);
    pen.setColor(m_foreColor);
    painter.setPen(pen);
    painter.setBrush(m_backColor);
    painter.drawRoundedRect(btnRect, 10, 10);
    // 画内部圆形
    painter.setBrush(m_foreColor);
    painter.drawEllipse(m_ballRect);

    QWidget::paintEvent(e);
}

void MSwitchButton::enterEvent(QEvent *e)
{
    m_hover = true;
    initData();
    startHoverAni();
}

void MSwitchButton::leaveEvent(QEvent *e)
{
    m_hover = false;
    initData();
    startHoverAni();
}

void MSwitchButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_posAni->state() == QAbstractAnimation::Running) {
        return;
    }
    m_isOn = !m_isOn;
    initData();
    if(rect().contains(mapFromGlobal(QCursor::pos())))
        emit stateChanged(m_isOn);

    startPosAni();
}

void MSwitchButton::initData()
{
    disconnect(m_posAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setBallRect);
    disconnect(m_foreColorAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setForeColor);
    disconnect(m_backColorAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setBackColor);
    disconnect(m_backHoverColorAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setBackColor);
    m_posAni->setDuration(300);
    m_posAni->setEasingCurve(QEasingCurve::InOutExpo);
    m_posAni->setStartValue(QRectF(btnRect.topLeft() + QPoint(m_padding, m_padding), QSize(btnRect.height() - 2 * m_padding, btnRect.height() - 2 * m_padding)));
    m_posAni->setEndValue(QRectF(btnRect.topRight() - QPoint(m_padding + btnRect.height() - 2 * m_padding, -1 * m_padding), QSize(btnRect.height() - 2 * m_padding, btnRect.height() - 2 * m_padding)));

    m_foreColorAni->setDuration(300);
    m_foreColorAni->setEasingCurve(QEasingCurve::Linear);
    m_foreColorAni->setStartValue(MColor_OrdinaryForeColor);
    m_foreColorAni->setEndValue(MColor_SuggestForeColor);

    m_backColorAni->setDuration(300);
    m_backColorAni->stop();
    m_backColorAni->setEasingCurve(QEasingCurve::Linear);

    if (m_hover) {
        m_backColorAni->setStartValue(MColor_OrdinaryHoverBackColor);
        m_backColorAni->setEndValue(MColor_SuggestHoverBackColor);
    } else {
        m_backColorAni->setStartValue(MColor_OrdinaryBackColor);
        m_backColorAni->setEndValue(MColor_SuggestBackColor);
    }

    m_backHoverColorAni->setDuration(300);
    m_backHoverColorAni->setEasingCurve(QEasingCurve::Linear);

    if (m_isOn) {
        m_backHoverColorAni->setStartValue(MColor_SuggestBackColor);
        m_backHoverColorAni->setEndValue(MColor_SuggestHoverBackColor);
    } else {
        m_backHoverColorAni->setStartValue(MColor_OrdinaryBackColor);
        m_backHoverColorAni->setEndValue(MColor_OrdinaryHoverBackColor);
    }
    connect(m_posAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setBallRect, Qt::QueuedConnection);
    connect(m_foreColorAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setForeColor, Qt::QueuedConnection);
    connect(m_backColorAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setBackColor, Qt::QueuedConnection);
    connect(m_backHoverColorAni, &QVariantAnimation::valueChanged, this, MSwitchButton::setBackColor, Qt::QueuedConnection);
}

void MSwitchButton::setForeColor(const QVariant &data)
{
    const QColor &color = data.value<QColor>();
    m_foreColor = color;
    update();
}
void MSwitchButton::setBackColor(const QVariant &data)
{
    const QColor &color = data.value<QColor>();
    m_backColor = color;
    update();
}
void MSwitchButton::setBallRect(const QVariant &data)
{
    const QRectF &rect = data.value<QRectF>();
    m_ballRect = rect;
    update();
}

void MSwitchButton::startHoverAni()
{
    if (m_hover) {
        m_backHoverColorAni->setDirection(QAbstractAnimation::Forward);
    } else {
        m_backHoverColorAni->setDirection(QAbstractAnimation::Backward);
    }
    m_backHoverColorAni->start();
}
void MSwitchButton::startPosAni()
{
    if (m_isOn) {
        m_posAni->setDirection(QAbstractAnimation::Forward);
        m_foreColorAni->setDirection(QAbstractAnimation::Forward);
        m_backColorAni->setDirection(QAbstractAnimation::Forward);
    } else {
        m_posAni->setDirection(QAbstractAnimation::Backward);
        m_foreColorAni->setDirection(QAbstractAnimation::Backward);
        m_backColorAni->setDirection(QAbstractAnimation::Backward);
    }
    m_posAni->start();
    m_foreColorAni->start();
    m_backColorAni->start();
}

void MSwitchButton::setSwitchState(bool on)
{
    m_isOn = on;
    initData();
    startPosAni();
}
bool MSwitchButton::switchState()
{
    return m_isOn;
}