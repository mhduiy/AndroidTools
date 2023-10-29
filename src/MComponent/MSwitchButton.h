#ifndef MSWITCHBUTTON_H
#define MSWITCHBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QVariantAnimation>

class MSwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit MSwitchButton(QWidget *parent = nullptr);
    void setSwitchState(bool on = false);
    bool switchState();

signals:
    void stateChanged(bool isOn);

protected:
    void paintEvent(QPaintEvent *e)override;
    void enterEvent(QEvent *e)override;
    void leaveEvent(QEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *)override;

private:
    void initData();
    void setForeColor(const QVariant &color);
    void setBackColor(const QVariant &color);
    void setBallRect(const QVariant &rect);
    void startHoverAni();
    void startPosAni();

private:
    bool m_hover;
    bool m_isOn;

    QRect btnRect;

    const int m_padding = 4;  //内部间隔

    QRectF m_ballRect;
    QColor m_foreColor;
    QColor m_backColor;

    QVariantAnimation *m_posAni = nullptr;
    QVariantAnimation *m_foreColorAni = nullptr;
    QVariantAnimation *m_backColorAni = nullptr;
    QVariantAnimation *m_backHoverColorAni = nullptr;
};

#endif