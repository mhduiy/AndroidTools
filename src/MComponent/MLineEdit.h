#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QInputMethodEvent>
#include <QLineEdit>
#include <QPropertyAnimation>
#include <QCursor>

class MLineEdit : public QWidget {
    Q_OBJECT
    Q_PROPERTY(double m_placeholderFontSize READ placeHolderFontSize WRITE setplaceHolderFontSize)
    Q_PROPERTY(QRectF m_placeholderRect READ placeholderRect WRITE setPlaceholderRect)
    Q_PROPERTY(QColor m_backGroundColor READ backGroundColor WRITE setBackGroundColor)
public:
    explicit MLineEdit(QWidget* parent = nullptr);
    void setText(const QString &text);
    QString text() const;
    void setTipText(const QString& text);

protected:
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void initUI();

    void updateLayout();
    void updateData();

    double placeHolderFontSize();
    void setplaceHolderFontSize(double size);

    QRectF placeholderRect();
    void setPlaceholderRect(const QRectF &rect);

    QColor backGroundColor();
    void setBackGroundColor(const QColor &color);

    void startplaceholderAni();
    
private:
    QLineEdit *m_lineEdit = nullptr;

    QString m_placeholderText;

    QFont m_placeholderFont;
    double m_placeholderFontSize = 12.0;
    QRectF m_placeholderRect;

    QFont m_foldPlaceholderFont;
    double m_foldPlaceholderFontSize = 8.0;
    QRectF m_foldPlaceholderRect;

    QColor m_backGroundColor = QColor(255, 255, 255, 120);
    QColor m_isInputBackColor = QColor(0, 129, 255, 150);
    QColor m_isNoInputBackColor = QColor(255, 255, 255, 120);

    QPropertyAnimation *m_placeholderRectAni = nullptr;
    QPropertyAnimation *m_placeholderFontSizeAni = nullptr;
    QPropertyAnimation *m_backgroundColorAni = nullptr;

    int topMargin = 5;      // 控件上边缘到顶部间隔
    int leftPadding = 4;    // 内部输入框左缩进

    bool isInput = false;

    bool lastIsInput = false;
};
#endif
