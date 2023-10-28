//
// Created by mhduiy on 2023/7/13.
//

#ifndef SIMPLYTOOLS_MICON_H
#define SIMPLYTOOLS_MICON_H
#include <QWidget>
#include <QLabel>

class MIcon : public QWidget{
    Q_OBJECT
public:
    explicit MIcon(const QString& title, const QString &text, QWidget *parent = nullptr);
    void setBackgroundColor(const QColor& color);
    void setTitle(const QString &title);
    void setText(const QString &text);

protected:
    void showEvent(QShowEvent *event)override;
private:
    QLabel *textLabel = nullptr;
    QLabel *titleLabel = nullptr;
};


#endif //SIMPLYTOOLS_MICON_H
