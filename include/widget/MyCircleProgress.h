#ifndef MYCIRCLEPROGRESS_H
#define MYCIRCLEPROGRESS_H

#include <DWidget>
#include <dcircleprogress.h>
#include <QLayout>
#include <DLabel>

DWIDGET_USE_NAMESPACE

class MyCircleProgress : public DWidget {
    Q_OBJECT
public:
    explicit MyCircleProgress(DWidget *parent = nullptr);
    ~MyCircleProgress() override;
    void setTopText(const QString &s);
    void setBottomText(const QString &s);

protected:
    void resizeEvent(QResizeEvent *event)override;

private:
    DCircleProgress * progress;
    DLabel *_topLabel;
    DLabel * _bottomLabel;
    int labelHeight;
    QColor bgColor = QColor(216, 216, 216);    //环背景色
    QColor fgColor = QColor(72, 184, 113);     //环前景色
};

#endif
