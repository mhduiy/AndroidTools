#ifndef TERMINALTOOLWIDGET_H
#define TERMINALTOOLWIDGET_H

#include <QWidget>

class TerminalToolWidget : public QWidget {
    Q_OBJECT
public:
    explicit TerminalToolWidget(QWidget *parent = nullptr);
    ~TerminalToolWidget();
};


#endif
