//
// Created by mhduiy on 2023/7/11.
//

#ifndef SIMPLYTRANSLATE_MBUTTON_H
#define SIMPLYTRANSLATE_MBUTTON_H

#include <QPushButton>
#include <QVariantAnimation>

enum Category{
    MBtn_ordinary,
    MBtn_suggested,
    MBtn_warning
};

class MButton : public QWidget{
    Q_OBJECT
public:
    explicit MButton(const QString &text = "", Category type = MBtn_ordinary, QWidget *parent = nullptr);
    void setCategory(Category category);
    void setText(const QString &text);
    void setIcon(const QIcon &icon);

protected:
    void paintEvent(QPaintEvent *e)override;
    void enterEvent(QEvent *e)override;
    void leaveEvent(QEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *)override;
signals:
    void clicked();
private:
    void initData();
    void startAni();
    void setBackgroundColor(const QColor &color);

private:
    Category m_category;
    QColor m_backgroundColor;
    QColor m_foregroundColor;
    QString m_text;
    QIcon m_icon;
    bool m_hover;
    QVariantAnimation *m_backColorAni;
};

#endif //SIMPLYTRANSLATE_MBUTTON_H
