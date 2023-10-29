#include "MTabSwitchButton.h"
#include "Global/globalType.hpp"

#include <QPainter>
#include <QTextOption>
#include <QMouseEvent>
#include <QDebug>

MTabSwitchButton::MTabSwitchButton(QWidget *parent)
:QWidget(parent)
,m_aniSliderPos(new QPropertyAnimation(this, "m_curSliderPoint", this))
{
    initUI();

    setMouseTracking(true);
}

void MTabSwitchButton::initUI()
{
    setFixedHeight(40);

    m_aniSliderPos->setDuration(400);
    m_aniSliderPos->setEasingCurve(QEasingCurve::OutQuart);
}

void MTabSwitchButton::paintEvent(QPaintEvent *event)
{
    paintBackground();
    paintSlider();
    paintText();
    QWidget::paintEvent(event);
}

void MTabSwitchButton::insertItem(int index, const QString &item)
{
    m_content.insert(index, item);
    updateRect();
    update();
}

void MTabSwitchButton::addItem(const QString &item)
{
    m_content.append(item);
    updateRect();
    update();
}

void MTabSwitchButton::paintBackground()
{
    QPainter painter(this);
    /* 尽可能消除锯齿边缘 */
    painter.setRenderHint(QPainter::Antialiasing);
    /* 尽可能消除文本锯齿边缘 */
    painter.setRenderHint(QPainter::TextAntialiasing);
    /* 启用线性插值算法以此来平滑图片 */
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(MColor_OrdinaryForeColor);
    painter.setPen(pen);
    painter.setBrush(Qt::transparent);

    painter.drawRoundedRect(rect().marginsRemoved(QMargins(1, 1, 1, 1)), 10, 10);
}

void MTabSwitchButton::paintText()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.setPen(Qt::black);
    QFont font;
    font.setFamily("黑体");
    font.setPixelSize(14);
    
    painter.setFont(font);

    QTextOption option;
    option.setAlignment(Qt::AlignCenter);

    for(int i = 0; i < qMin(m_content.size(), m_rects.size()); i++)
    {
        if (i == m_checkedIndex) {
            painter.save();
            painter.setPen(Qt::white);
            painter.drawText(m_rects[i], m_content[i], option);
            painter.restore();
        } else {
            painter.drawText(m_rects[i], m_content[i], option);
        }
    }
}

void MTabSwitchButton::paintSlider()
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.setPen(Qt::NoPen);

    // 画当前Press的
    if (m_pressIndex != -1 && m_checkedIndex < m_rects.size() && m_pressIndex != m_checkedIndex) {
        painter.setBrush(MColor_OrdinaryHoverBackColor);
        painter.drawRoundedRect(m_rects.value(m_pressIndex), 10, 10);
    }
    // 画当前Hover的
    if (m_hoverIndex != -1 && m_hoverIndex < m_rects.size() && m_hoverIndex != m_checkedIndex && m_hoverIndex != m_pressIndex) {
        painter.setBrush(MColor_OrdinaryBackColor);
        painter.drawRoundedRect(m_rects.value(m_hoverIndex), 10, 10);
    }
    // 画当前选中的
    if (m_checkedIndex != -1 && m_checkedIndex < m_rects.size()) {
        painter.setBrush(MColor_SuggestForeColor);
        painter.drawRoundedRect(QRectF(m_curSliderPoint, m_silderSize), 10, 10);
    }
}

void MTabSwitchButton::updateRect()
{
    m_rects.clear();

    setFixedWidth(m_content.size() * 80);

    int curRectWidth = geometry().width() - 6;
    int curRectHeight = geometry().height() - 6;

    double itemWidth = double(curRectWidth) / m_content.size();

    for(int i = 0; i < m_content.size(); i++) {
        m_rects.append(QRect(QPoint(i * itemWidth + 3, 3), QSize(itemWidth, curRectHeight)));
    }
    setCurrentIndex(0);

    m_silderSize = QSizeF(itemWidth, curRectHeight);
}

void MTabSwitchButton::mousePressEvent(QMouseEvent* event)
{
    int curIndex = getCurIndexFromCursor(event->pos());
    if (curIndex != m_pressIndex && curIndex != -1) {
        m_pressIndex = curIndex;
        update();
    }
    QWidget::mousePressEvent(event);
}

void MTabSwitchButton::mouseReleaseEvent(QMouseEvent* event)
{
    int curIndex = getCurIndexFromCursor(event->pos());
    if (curIndex != m_checkedIndex && curIndex != -1) {

        setCurrentIndex(curIndex);

        m_pressIndex = -1;
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void MTabSwitchButton::mouseMoveEvent(QMouseEvent* event)
{
    int curIndex = getCurIndexFromCursor(event->pos());
    if (curIndex != m_hoverIndex) {
        m_hoverIndex = curIndex;
        update();
    }
    if (m_hoverIndex != m_pressIndex || event->button() == Qt::NoButton) {
        m_pressIndex = -1;
        update();
    }
    QWidget::mouseMoveEvent(event);
}

int MTabSwitchButton::getCurIndexFromCursor(const QPoint &point)
{
    for (int i = 0; i < m_rects.size(); i++) {
        if (m_rects[i].contains(point)) {
            return i;
        }
    }
    return -1;
}

QPointF MTabSwitchButton::silderPos()
{
    return m_curSliderPoint;
}

void MTabSwitchButton::setSilderPos(const QPointF &pos)
{
    m_curSliderPoint = pos;
    update();
}

void MTabSwitchButton::startSliderPosAni(int preIndex, int tarIndex)
{
    if(m_aniSliderPos->state() == QPropertyAnimation::Running) {
        m_aniSliderPos->stop();
    }
    m_aniSliderPos->setStartValue(m_rects.value(preIndex).topLeft());
    m_aniSliderPos->setEndValue(m_rects.value(tarIndex).topLeft());
    m_aniSliderPos->start();
}

void MTabSwitchButton::setCurrentIndex(int index)
{
    emit currentIndexChanged(index);
    emit currentIndexChanged(m_checkedIndex, index);

    startSliderPosAni(m_checkedIndex, index);

    m_checkedIndex = index;
}