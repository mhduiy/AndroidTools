#ifndef FLASHINGWIDGET_H
#define FLASHINGWIDGET_H

#include <QWidget>

class FlashingWidget : public QWidget {
    Q_OBJECT
public:
    explicit FlashingWidget(QWidget *parent = nullptr);
    ~FlashingWidget();
};


#endif
