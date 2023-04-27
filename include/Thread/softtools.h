#ifndef SOFTTOOLS_H
#define SOFTTOOLS_H

#include <QObject>
#include "deviceConnect.h"
#include "ADBTools.h"

class SoftTools : public QObject
{
    Q_OBJECT
public:
    explicit SoftTools(QObject *parent = nullptr);
    bool installApp(const QString& Path);                                   //安装软件
    bool clearData(const QString& packageName);                             //清除数据
    bool uninstallApp(const QString& packageName);                          //卸载软件
    bool extractApp(const QString& packageName, const QString& targetPath); //提取软件
    static SoftTools* getInstance(QObject *parent = nullptr);
private:
    ADBTools adbTool;
    static SoftTools* instance;
};

#endif // SOFTTOOLS_H
