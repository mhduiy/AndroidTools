#ifndef MTABSWITCHBUTTON_H
#define MTABSWITCHBUTTON_H

#include <QWidget>
#include <QPropertyAnimation>

class MTabSwitchButton : public QWidget
{
Q_OBJECT
Q_PROPERTY(QPointF m_curSliderPoint READ silderPos WRITE setSilderPos)
public:
    explicit MTabSwitchButton(QWidget *parent = nullptr);
    void addItem(const QString &item);
    void insertItem(int index, const QString &item);
    void setCurrentIndex(int index);

signals:
    void currentIndexChanged(int cutIndex);
    void currentIndexChanged(int preIndex, int cutIndex);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
private:
    void initUI();
    void paintBackground();
    void paintText();
    void paintSlider();
    void updateRect();
    int getCurIndexFromCursor(const QPoint &point);

    QPointF silderPos();
    void setSilderPos(const QPointF &pos);

    void startSliderPosAni(int preIndex, int tarIndex);

private:
    QList<QString> m_content;
    QList<QRect> m_rects;

    QPointF m_curSliderPoint;
    QPointF m_tarSliderPoint;

    QSizeF m_silderSize;

    int m_hoverIndex = -1;
    int m_checkedIndex = -1;
    int m_pressIndex = -1;

    QBrush m_hoverBrush = QColor(220, 220, 220);
    QBrush m_pressBrush = QColor(200, 200, 200);
    QBrush m_checkBrush = QColor(0, 129, 255);

    QPropertyAnimation *m_aniSliderPos = nullptr;
};

#endif