#ifndef INFORPANELWIDGET_H
#define INFORPANELWIDGET_H

#include <QWidget>

class InfoPanelWidget : public QWidget {
    Q_OBJECT
public:
    explicit InfoPanelWidget(QWidget *parent = nullptr);
    ~InfoPanelWidget();
};

#endif
