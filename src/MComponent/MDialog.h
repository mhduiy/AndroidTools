//
// Created by mhduiy on 2023/7/15.
//

#ifndef SIMPLYTOOLS_MDIALOG_H
#define SIMPLYTOOLS_MDIALOG_H

#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QDialog>
#include <QEventLoop>
#include "MLineEdit.h"
#include "MButton.h"

class MDialog : public QWidget{
    Q_OBJECT
public:
    explicit MDialog(QWidget* parent = nullptr);
    ~MDialog()override;
    void initUI();
    /**
     *
     * @param label  标签
     * @param defaultStr  输入框默认值
     * @return 输入框id
     */
    int addItem(const QString &label, const QString &defaultStr = "");
    /**
     *
     * @param id
     * @return 获取指定id的输入框的数据
     */
    QString getItemInfo(int id);
    /**
     *
     * @param label
     * @return 获取指定label文字的输入框数据
     */
    QString getItemInfo(const QString& label);
    /**
     * 添加一个控件到dialog中
     * @param widget 添加的小控件
    */
    void addWidget(QWidget *widget = nullptr);

    void setLabelById(const QString& label, int id = 0);
    void setDefaultStrById(const QString& defaultStr, int id = 0);

    void on_confirmBtn_clicked();
    void on_cancelBtn_clicked();
    int exec();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    QVector<MLineEdit*> lineEditVector;

    QWidget* findMainWindow(QObject *obj);

    QWidget *mainWindow = nullptr;
    QVBoxLayout *mainLayout = nullptr;

    QVBoxLayout *m_vLayout = nullptr;

    QEventLoop eventLoop;

    int m_exitStatCode = 0;

    MButton *cancelBtn = nullptr;
    MButton *confirmBtn = nullptr;
};


#endif //SIMPLYTOOLS_MDIALOG_H
