//
// Created by mhduiy on 2023/7/13.
//

#include "MIcon.h"
#include <QLayout>

MIcon::MIcon(const QString& title, const QString &text, QWidget *parent) : QWidget(parent){
    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(true);
    titleLabel = new QLabel(title, this);
    textLabel = new QLabel(text);

    titleLabel->setStyleSheet(R"(QLabel {background-color: transparent;  font-size: 15px; color: #FFFFFF;font-family: 黑体; padding: 0px; border: 1px black solid;})");
    textLabel->setStyleSheet(R"(QLabel {background-color: transparent;  font-size: 28px; color: #FFFFFF;font-family: 黑体; padding 0px; border: 1px black solid;})");
    textLabel->setAlignment(Qt::AlignHCenter);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(textLabel);

    setContentsMargins(0,0,0,0);
    mainLayout->setMargin(0);

    setStyleSheet("MIcon{ border-radius: 10px; background-color: #FB7299;}");
    setFixedSize(150, 90);
}

void MIcon::setBackgroundColor(const QColor& color) {
    auto p = this->palette();
    p.setColor(QPalette::Background, color);
    this->setPalette(p);
}

void MIcon::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    titleLabel->move( 5, 0);
}

void MIcon::setTitle(const QString &title) {
    titleLabel->setText(title);
}

void MIcon::setText(const QString &text) {
    textLabel->setText(text);
}
