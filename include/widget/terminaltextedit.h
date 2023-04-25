#ifndef TERMINALTEXTEDIT_H
#define TERMINALTEXTEDIT_H

#include <QObject>
#include <DTextEdit>
#include <DWidget>

DWIDGET_USE_NAMESPACE

class TerminalTextEdit : public DTextEdit
{
    Q_OBJECT
public:
    explicit TerminalTextEdit(DWidget *parent = nullptr);
    void initUI();
public slots:
    void startInput();                  //开始输入新的命令
    void setCommandRetInfo(const QString &text);           //设置命令的返回信息
protected:
    void keyPressEvent(QKeyEvent *e) override;

signals:
    void returnPressed(const QString &lineInfo);
};

#endif // TERMINALTEXTEDIT_H
