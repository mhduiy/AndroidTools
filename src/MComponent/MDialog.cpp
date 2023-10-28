//
// Created by mhduiy on 2023/7/15.
//

#include <QGraphicsBlurEffect>
#include "MDialog.h"
#include <QEventLoop>
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QDebug>

MDialog::MDialog(QWidget *parent) : QWidget(parent){
    initUI();
}
void MDialog::initUI() {
    setWindowModality(Qt::ApplicationModal);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::Dialog);

    m_vLayout = new QVBoxLayout(this);
    auto *btnLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    confirmBtn = new MButton("确认", MBtn_ordinary);
    cancelBtn = new MButton("取消", MBtn_warning);

    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(confirmBtn);

    m_vLayout->addLayout(mainLayout);
    m_vLayout->addLayout(btnLayout);

    setMinimumWidth(300);

    connect(confirmBtn, &MButton::clicked, this, &MDialog::on_confirmBtn_clicked);
    connect(cancelBtn, &MButton::clicked, this, &MDialog::on_cancelBtn_clicked);

}

MDialog::~MDialog() {
}


int MDialog::addItem(const QString &label, const QString &defaultStr) {
    auto *_ed = new MLineEdit();
    _ed->setTipText(label);
    _ed->setText(defaultStr);

    mainLayout->addWidget(_ed);

    lineEditVector.append(_ed);

    return lineEditVector.size() - 1;
}

QString MDialog::getItemInfo(int id) {
    auto _ed = lineEditVector.value(id);
    if(_ed == nullptr) {
        return {};
    }
    return _ed->text();
}

QString MDialog::getItemInfo(const QString &label) {
    const MLineEdit *_ed = nullptr;
    foreach(auto &_lineEdit, lineEditVector) {
        if(_lineEdit->text() == label) {
            _ed = _lineEdit;
            break;
        }
    }
    if(_ed == nullptr) {
        return {};
    }
    return _ed->text();
}

void MDialog::setLabelById(const QString& label, int id) {
    if(id >= lineEditVector.size() || id < 0) {
        return;
    }
    lineEditVector.value(id)->setTipText(label);
}

void MDialog::setDefaultStrById(const QString& defaultStr, int id) {
    if(id >= lineEditVector.size() || id < 0) {
        return;
    }
    lineEditVector.value(id)->setText(defaultStr);
}

void MDialog::on_confirmBtn_clicked() {
    m_exitStatCode = 1;
    eventLoop.quit();
}


void MDialog::on_cancelBtn_clicked() {
    m_exitStatCode = 0;
    eventLoop.quit();
}

void MDialog::addWidget(QWidget *widget)
{
    m_vLayout->insertWidget(0, widget);
}

QWidget *MDialog::findMainWindow(QObject *obj) {
    if(obj == nullptr) {
        return nullptr;
    }
    if(strcmp(obj->metaObject()->className(), "MainWindow") == 0) {
        return qobject_cast<QWidget*>(obj);
    }
    return findMainWindow(obj->parent());
}

void MDialog::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - width()) / 2, (desktop->height() - height()) / 2);
}

void MDialog::closeEvent(QCloseEvent *event) {
    if(mainWindow != nullptr) {
        mainWindow->setGraphicsEffect(nullptr);
    }
    QWidget::closeEvent(event);
}

int MDialog::exec() {
    QWidget::show();
    eventLoop.exec();
    close();
    return m_exitStatCode;
}
