#ifndef SOFTTOOLS_H
#define SOFTTOOLS_H

#include <QObject>
#include "deviceConnect.h"
#include "ADBTools.h"
#include "myTypes.h"

class SoftTools : public QObject
{
    Q_OBJECT
public:
    explicit SoftTools(QObject *parent = nullptr);
    bool installApp(const QString& Path);                                   //安装软件
    bool clearData(const QString& packageName);                             //清除数据
    bool unfreezeApp(const QString& packageName);                           //解冻软件
    bool freezeApp(const QString& packageName);                             //冻结软件
    bool uninstallApp(const QString& packageName);                          //卸载软件
    bool extractApp(const QString& packageName, const QString& targetPath); //提取软件
    static SoftTools* getInstance(QObject *parent = nullptr);

signals:
    void finishOP(MHDUIY::OPERATFLAG, bool isSuc);
private:
    ADBTools adbTool;
    static SoftTools* instance;
};

#endif // SOFTTOOLS_H
