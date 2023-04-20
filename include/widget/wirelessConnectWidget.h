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
#include <DComboBox>
#include "ADBTools.h"


DWIDGET_USE_NAMESPACE

class WirelessConnectWidget : public QDialog {
    Q_OBJECT
public:
    explicit WirelessConnectWidget(QWidget *parent = nullptr);
    ~WirelessConnectWidget()override;
    void initUI();
    int exec()override;
    void startPair();
    void startConnect();
    void CheckConnect();
    void setRightConnFromHistory(int index); //通过历史连接记录在设置正确的信息
    void readConnHistory();

private:
    enum {PrepareW = 0, PairW, ConnectW, CheckW, TOTALW};   //界面枚举定义
    DStackedWidget *mainW = nullptr;          //主界面
    QVector<DWidget*> itemW;        //小界面
    /*准备界面*/
    DTextEdit *preEdit = nullptr;
    DPushButton *enterPairBtn = nullptr;
    DPushButton *enterConnectBtn = nullptr;
    /*配对界面*/
    DTextEdit *pairEdit = nullptr;
    DLineEdit *pairIpEdit = nullptr;
    DLineEdit *pairPortEdit = nullptr;
    DLineEdit *pairCodeEdit = nullptr;
    DPushButton *pairBtn = nullptr;
    DPushButton *pairReturnBtn = nullptr;
    /*连接界面*/
    DTextEdit *conEdit = nullptr;
    DLineEdit *conIpEdit = nullptr;
    DLineEdit *conPortEdit = nullptr;
    DPushButton *conReturnbtn = nullptr;
    DPushButton *conBtn = nullptr;
    DComboBox *historyConnBox;
    /*检查界面*/
    QLabel *connectStatus = nullptr;
    bool connectSuccess = false;
    DPushButton *funcBtn = nullptr;

    ADBTools adbTool;
};


#endif
