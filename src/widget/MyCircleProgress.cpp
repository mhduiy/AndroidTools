#include "MyCircleProgress.h"
#include <QResizeEvent>


MyCircleProgress::MyCircleProgress(Dtk::Widget::DWidget *parent) : DWidget(parent)
{
    labelHeight = 20;
    QVBoxLayout *vLayout= new QVBoxLayout();
    //水平居中
    vLayout->setAlignment(Qt::AlignHCenter);

    progress = new DCircleProgress();
    _topLabel = new DLabel();
    _bottomLabel = new DLabel();

    _topLabel->setAlignment(Qt::AlignHCenter);
    _bottomLabel->setAlignment(Qt::AlignHCenter);

    _topLabel->setFixedHeight(labelHeight);
    _bottomLabel->setFixedHeight(labelHeight);


    progress->setFixedSize(100,100);

    progress->setBackgroundColor(bgColor);
    progress->setChunkColor(fgColor);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setAlignment(Qt::AlignHCenter);
    hLayout->addWidget(progress);

    vLayout->addWidget(_topLabel);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(_bottomLabel);
    //设置环形框的宽度
    progress->setLineWidth(12);

    this->setLayout(vLayout);
}

MyCircleProgress::~MyCircleProgress()
{

}

void MyCircleProgress::setTopText(const QString &s)
{
    this->_topLabel->setText(s);
}

void MyCircleProgress::setBottomText(const QString &s)
{
    this->_bottomLabel->setText(s);
}

DCircleProgress *MyCircleProgress::getPG()
{
    return this->progress;
}

void MyCircleProgress::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    _topLabel->setFixedWidth(w);
    _bottomLabel->setFixedWidth(w);
    int proW = w < h - labelHeight - labelHeight ? w : h - labelHeight - labelHeight;
    progress->setFixedSize(proW, proW);
}
