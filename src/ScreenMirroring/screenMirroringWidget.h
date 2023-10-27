#ifndef SCREENMIRRORING_H
#define SCREENMIRRORING_H

#include <QWidget>

class ScreenMirroringWidget : public QWidget {
    Q_OBJECT
public:
    explicit ScreenMirroringWidget(QWidget *parent = nullptr);
    ~ScreenMirroringWidget();
};

#endif
