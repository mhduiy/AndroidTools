#include "MLineEdit.h"
#include <QLayout>
#include <QDebug>
#include <QPainterPath>
#include <QApplication>

MLineEdit::MLineEdit(QWidget *parent)
:QWidget(parent)
,m_lineEdit(new QLineEdit())
,m_placeholderRectAni(new QPropertyAnimation(this, "m_placeholderRect", this))
,m_placeholderFontSizeAni(new QPropertyAnimation(this, "m_placeholderFontSize", this))
,m_backgroundColorAni(new QPropertyAnimation(this, "m_backGroundColor", this))
{
    setFixedHeight(50);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    initUI();
}

void MLineEdit::initUI()
{
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_lineEdit);
    mainLayout->setMargin(4);

    m_lineEdit->setStyleSheet("background: transparent; border: 0px;");

    m_placeholderFont.setPointSizeF(m_placeholderFontSize);
    m_foldPlaceholderFont.setPointSizeF(m_foldPlaceholderFontSize);

    m_placeholderRectAni->setEasingCurve(QEasingCurve::InOutQuint);
    m_placeholderFontSizeAni->setEasingCurve(QEasingCurve::InOutQuint);
    m_backgroundColorAni->setEasingCurve(QEasingCurve::InOutQuint);

    m_placeholderRectAni->setDuration(500);
    m_placeholderFontSizeAni->setDuration(500);
    m_backgroundColorAni->setDuration(200);

    m_backgroundColorAni->setStartValue(m_isNoInputBackColor);
    m_backgroundColorAni->setEndValue(m_isInputBackColor);
    m_placeholderFontSizeAni->setStartValue(m_placeholderFontSize);
    m_placeholderFontSizeAni->setEndValue(m_foldPlaceholderFontSize);

    m_lineEdit->hide();

    m_lineEdit->installEventFilter(this);
}

void MLineEdit::showEvent(QShowEvent *event)
{
    updateLayout();
    QWidget::showEvent(event);
}

void MLineEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    /* 尽可能消除锯齿边缘 */
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;

    path.addRoundedRect(rect().marginsRemoved(QMargins(1, topMargin, 1, topMargin)), 8, 8);

    // 在输入中,则剪切圆角矩形右上角部分
    if(isInput || !m_lineEdit->text().isEmpty()) {
        QPainterPath clipPath;
        clipPath.addRoundedRect(m_placeholderRect, 5, 5);
        path = path.subtracted(clipPath);
    }

    painter.setBrush(m_backGroundColor);
    painter.setPen(Qt::NoPen);

    // 绘制路径(背景和右上角矩形)
    painter.drawPath(path);

    // 绘制提示占位文字
    if(isInput) {
        painter.setPen(QColor(0, 129, 255));
    } else {
        painter.setPen(Qt::darkGray);
    }
    QFont font;
    font.setPointSizeF(m_placeholderFontSize);
    painter.setFont(font);
    QTextOption placeholderTextOption;
    placeholderTextOption.setAlignment(Qt::AlignCenter);

    painter.drawText(m_placeholderRect, m_placeholderText, placeholderTextOption);

    QWidget::paintEvent(event);
}

void MLineEdit::setTipText(const QString& text)
{
    m_placeholderText = text;
    updateLayout();
}

QString MLineEdit::text() const
{
    return m_lineEdit->text();
}

void MLineEdit::setText(const QString &text)
{
    m_lineEdit->setText(text);
    updateLayout();
}

void MLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    isInput = true;
    startplaceholderAni();
    m_lineEdit->show();
    m_lineEdit->setFocus();
    QPalette palette = m_lineEdit->palette();
    palette.setColor(QPalette::Text, Qt::white);
    m_lineEdit->setPalette(palette);
    QWidget::mouseReleaseEvent(event);
}

void MLineEdit::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
}

void MLineEdit::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
}

void MLineEdit::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
}

void MLineEdit::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event);
}

bool MLineEdit::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_lineEdit && event->type() == QEvent::FocusOut) {
        if (m_lineEdit->text().isEmpty()) {
            m_lineEdit->hide();
        }
        QPalette palette = m_lineEdit->palette();
        palette.setColor(QPalette::Text, QColor(50, 50, 50));
        m_lineEdit->setPalette(palette);
        isInput = false;
        startplaceholderAni();
    } else if(obj == m_lineEdit && event->type() == QEvent::MouseButtonRelease) {
        QApplication::sendEvent(this, event);
    }
    return QWidget::eventFilter(obj, event);
}
void MLineEdit::resizeEvent(QResizeEvent *event)
{
    setTipText(m_placeholderText);  // 刷新以下
    updateLayout();
    return QWidget::resizeEvent(event);
}

double MLineEdit::placeHolderFontSize()
{
    return m_placeholderFontSize;
}
void MLineEdit::setplaceHolderFontSize(double size)
{
    m_placeholderFontSize = size;
    update();
}

QRectF MLineEdit::placeholderRect()
{
    return m_placeholderRect;
}
void MLineEdit::setPlaceholderRect(const QRectF &rect)
{
    m_placeholderRect = rect;
    update();
}

QColor MLineEdit::backGroundColor()
{
    return m_backGroundColor;
}
void MLineEdit::setBackGroundColor(const QColor &color)
{
    m_backGroundColor = color;
    update();
}

void MLineEdit::startplaceholderAni()
{
    if(isInput == lastIsInput) {
        return;
    }
    lastIsInput = isInput;
    if (m_placeholderRectAni->state() == QPropertyAnimation::Running) {
        m_placeholderRectAni->stop();
    }

    if (m_placeholderFontSizeAni->state() == QPropertyAnimation::Running) {
        m_placeholderFontSizeAni->stop();
    }

    if (m_backgroundColorAni->state() == QPropertyAnimation::Running) {
        m_backgroundColorAni->stop();
    }

    if (isInput) {
        m_placeholderRectAni->setDirection(QPropertyAnimation::Forward);
        m_placeholderFontSizeAni->setDirection(QPropertyAnimation::Forward);
        m_backgroundColorAni->setDirection(QPropertyAnimation::Forward);
    } else {
        m_placeholderRectAni->setDirection(QPropertyAnimation::Backward);
        m_placeholderFontSizeAni->setDirection(QPropertyAnimation::Backward);
        m_backgroundColorAni->setDirection(QPropertyAnimation::Backward);
    }

    if(m_lineEdit->text().isEmpty()) {
        m_placeholderRectAni->start();
        m_placeholderFontSizeAni->start();
    }
    m_backgroundColorAni->start();
}

void MLineEdit::updateLayout()
{
    updateData();
    // 如果有内容
    if (!m_lineEdit->text().isEmpty()) {
        m_lineEdit->show();
        setplaceHolderFontSize(m_foldPlaceholderFontSize);
        setPlaceholderRect(m_placeholderRectAni->endValue().toRectF());
    }
    else {
        if(isInput) {
            setPlaceholderRect(m_placeholderRectAni->endValue().toRectF());
        }
    }
}

void MLineEdit::updateData()
{
    QFontMetrics fontMetrics(m_placeholderFont);
    QSize textSize = fontMetrics.size(0, " " + m_placeholderText + " ");  // 获取文本的大小
    m_placeholderRect = QRect(QPoint(leftPadding, (geometry().height() - textSize.height()) / 2), textSize);

    QFontMetrics foldFontMetrics(m_foldPlaceholderFont);
    QSize foldTextSize = foldFontMetrics.size(0, " " + m_placeholderText + " ");  // 获取文本的大小
    m_foldPlaceholderRect = QRect(QPoint(width() - foldTextSize.width(), (topMargin * 2 - foldTextSize.height()) / 2 + 2), foldTextSize);

    qWarning() << m_placeholderRect << geometry().height() << textSize.height();

    m_placeholderRectAni->setStartValue(m_placeholderRect);
    m_placeholderRectAni->setEndValue(m_foldPlaceholderRect);
}