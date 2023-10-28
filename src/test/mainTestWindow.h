#ifndef MAINTESTWINDOW_H
#define MAINTESTWINDOW_H

#include <QMainWindow>
#include "MButton.h"
#include "MLineedit.h"
#include "MNotificationBox.h"
#include "MSidebar.h"
#include "MTabSwitchButton.h"

class MainTestWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainTestWindow(QWidget *parent = nullptr);
private:
    MButton *m_btnOrdinary;
    MButton *m_btnSuggest;
    MButton *m_btnWarning;
    MLineEdit *m_lineEdit;
    MNotificationBox *m_notificationBox;
    MSidebar *m_sideBar;
    MTabSwitchButton *m_tabSwitchButton;
};

#endif