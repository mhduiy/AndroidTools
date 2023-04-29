#include "deviceControlItem.h"
#include <QDebug>
#include <DFontSizeManager>

DeviceControlItem::DeviceControlItem(Dtk::Widget::DWidget *mainW, Dtk::Widget::DWidget *parent) : DWidget (parent)
{
    initUI(mainW);
    this->w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

DeviceControlItem::~DeviceControlItem()
{

}

void DeviceControlItem::initUI(DWidget *mainW)
{
    title = new DLabel();
    describe = new DLabel();
    box = new DGroupBox();
    QPalette paTitle = title->palette();
    paTitle.setColor(QPalette::WindowText, Qt::black);
    title->setPalette(paTitle);
    DFontSizeManager::instance()->bind(title, DFontSizeManager::T5);

    QPalette paDes = describe->palette();
    paDes.setColor(QPalette::WindowText, Qt::gray);
    describe->setPalette(paDes);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(box);

    QVBoxLayout *boxLayout = new QVBoxLayout(box);
    boxLayout->addWidget(title);
    boxLayout->addWidget(describe);
    w = mainW;
    boxLayout->addWidget(mainW);
}

void DeviceControlItem::setTitle(const QString &title)
{
    this->title->setText(title);
}

void DeviceControlItem::setWidget(DWidget *w)
{
    this->w = w;
}

void DeviceControlItem::setDescribe(const QString &describe)
{
    this->describe->setText(describe);
}

void DeviceControlItem::setDesVisible(bool visible)
{
    this->describe->setVisible(visible);
}
