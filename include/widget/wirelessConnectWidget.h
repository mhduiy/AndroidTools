#ifndef WIRELESSCONNECTWIDGET_H
#define WIRELESSCONNECTWIDGET_H

#include <QDialog>
#include <DPushButton>
#include <QLayout>
#include <DStackedWidget>
#include <DTextEdit>
#include <DLabel>
#include <DIpv4LineEdit>
#include <DLineEdit>


DWIDGET_USE_NAMESPACE

class WirelessConnectWidget : public QDialog {
    Q_OBJECT
public:
    explicit WirelessConnectWidget(QWidget *parent = nullptr);
    ~WirelessConnectWidget();
    void initUI();

private:
    enum {PrepareW = 0, PairW, ConnectW, CheckW, TOTALW};   //界面枚举定义
    DStackedWidget *mainW;          //主界面
    QVector<DWidget*> itemW;        //小界面
    /*准备界面*/
    DTextEdit *preEdit;
    DPushButton *enterPairBtn;
    DPushButton *enterConnectBtn;
    /*配对界面*/
    DTextEdit *pairEdit;
    DIpv4LineEdit *ipEdit;
    DLineEdit *pairCodeEdit;
    DPushButton *pairBtn;
    DPushButton *returnBtn;
    /*连接界面*/

    /*检查界面*/
};


#endif
