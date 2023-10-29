#ifndef MPROGRESSBAR_H
#define MPROGRESSBAR_H

#include <QWidget>
#include <QVariantAnimation>

class MProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit MProgressBar(QWidget *parent = nullptr);
    void setColor(int start, int end, const QColor &color);
    void clearColor();
    void setValue(int value);
    int value();
    void setTextVisible(bool isVisible = false);

protected:
    void paintEvent(QPaintEvent *e)override;

private:
    void initData();
    void startAni();
    void setValueRect(const QVariant &data);
    QRectF valueToRectF(int value);

private:
    int m_cutValue;
    bool m_textVisible;
    QRectF m_valueRect;
    QRect m_backRect;
    QRect m_textRect;
    QVector<QColor> m_colors;
    QHash<int, int> m_colorHash;

    int m_padding = 4;

    QVariantAnimation *m_valueAni;
};

#endif