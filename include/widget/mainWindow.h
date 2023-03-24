#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DWidget>
#include <DPlainTextEdit>
#include <QProcess>
#include "myTypes.h"
#include "inforPanelWidget.h"
#include <DStackedWidget>
#include <QStandardItemModel>


DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();
    void myCmd(QString cmd);

private:
    DWidget *mainW;
    InfoPannelWidget *infoPannelWidget;
    DStackedWidget *mainStackedWidget;
    DListView *funcView;
    QStandardItemModel *model;
};

#endif
