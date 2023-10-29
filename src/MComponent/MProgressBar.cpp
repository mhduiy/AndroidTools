#include "MProgressBar.h"
#include "Global/globalType.hpp"
#include <QPainter>
#include <QTimer>
#include <QRgb>
#include <QDebug>

MProgressBar::MProgressBar(QWidget *parent)
: QWidget(parent)
, m_cutValue(100)
, m_textVisible(true)
, m_valueAni(new QVariantAnimation(this))
{
    setFixedHeight(36);
    m_valueAni->setDuration(300);
    m_valueAni->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_valueAni, &QVariantAnimation::valueChanged, this, &MProgressBar::setValueRect);

    QTimer::singleShot(10, this, [this](){
        m_backRect = rect().marginsRemoved(QMargins(1, 1, 1, 1));
        m_valueRect = valueToRectF(100);
        m_textRect = rect();
    });

}

void MProgressBar::setColor(int start, int end, const QColor &color)
{
    qWarning() << color;
    if (start < 0 || end > 101 || start > end) {
        return;
    }
    int colorIndex = m_colors.indexOf(color);
    if(colorIndex < 0) {
        colorIndex = m_colors.size();
        m_colors.push_back(color);
    }
    for(int i = start; i < end; i++) {
        m_colorHash[i] = colorIndex;
    }
    qWarning() << m_colors;
    update();
}
void MProgressBar::setValue(int value)
{
    if (value < 0 || value > 100) {
        return;
    }
    m_valueAni->setStartValue(valueToRectF(m_cutValue));
    m_cutValue = value;
    m_valueAni->setEndValue(valueToRectF(m_cutValue));
    startAni();
}
int MProgressBar::value()
{
    return m_cutValue;
}
void MProgressBar::setTextVisible(bool isVisible)
{
    m_textVisible = isVisible;
    update();
}

void MProgressBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景
    painter.setBrush(Qt::NoBrush);
    QPen pen;
    pen.setWidth(2);
    QColor foreColor;
    if (m_colorHash.find(m_cutValue) != m_colorHash.end()) {
        foreColor = m_colors.value(m_colorHash[m_cutValue]);
    } else {
        foreColor = MColor_SuggestForeColor;
    }
    pen.setColor(foreColor);
    painter.setPen(pen);
    painter.drawRoundedRect(m_backRect, 10, 10);
    // 中间的条
    painter.setPen(Qt::NoPen);
    painter.setBrush(foreColor);
    painter.drawRoundedRect(m_valueRect, 8, 8);
    // 文字
    if (!m_textVisible) {
        return;
    }

    // if(m_cutValue < 48) {
        painter.setPen(Qt::black);
    // } else {
    //     qWarning() << "***";
    //     QColor color(foreColor);
    //     QRgba64 rgb = color.rgba64();
    //     rgb.setRed(255 - rgb.red());
    //     rgb.setGreen(255 - rgb.green());
    //     rgb.setBlue(255 - rgb.blue());
    //     color.setRgba64(rgb);
    //     painter.setPen(color);
    // }
    painter.setBrush(Qt::NoBrush);
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);
    QFont font;
    font.setFamily("黑体");
    font.setPixelSize(14);
    painter.setFont(font);
    painter.drawText(m_textRect, QString::number(m_cutValue) + "%", textOption);
}

void MProgressBar::clearColor()
{
    m_colors.clear();
    m_colorHash.clear();
    update();
}

void MProgressBar::initData()
{

}

void MProgressBar::startAni()
{
    if(m_valueAni->state() == QAbstractAnimation::Running) {
        return;
    }
    m_valueAni->start();
}
void MProgressBar::setValueRect(const QVariant &data)
{
    m_valueRect = data.value<QRectF>();
    update();
}
QRectF MProgressBar::valueToRectF(int value)
{
    return QRectF(m_backRect.topLeft() + QPoint(m_padding, m_padding), QSize((m_backRect.width() - m_padding * 2) * value / 100.0, m_backRect.height() - m_padding * 2));
}