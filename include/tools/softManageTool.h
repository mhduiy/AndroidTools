#ifndef SOFTMANAGETOOL_H
#define SOFTMANAGETOOL_H

#include <QObject>
#include "myTypes.h"
#include "ADBTools.h"
#include "softtools.h"

class SoftTools;

class SoftManageTool : public QObject {
    Q_OBJECT
public:

    static SoftManageTool* getInstance(QObject *parent = nullptr);

    enum SOFTFLAG{
        SOFT_TOTAL,
        SOFT_SYS,
        SOFT_THIRD
    };

    explicit SoftManageTool(QObject *parent = nullptr);
    ~SoftManageTool();
    QStringList getSoftList(SOFTFLAG flag);                     //获取软件包名列表
    MHDUIY::SoftInfo &getSoftInfo(const QString &packageName);   //获取软件详细信息
    bool operateSoft(MHDUIY::OPERATFLAG flag, const QString &packageName);  //通过包名操作软件

signals:
    void installApp(const QString& Path);
    void clearData(const QString& packageName);
    void uninstallApp(const QString& packageName);
    void freezeApp(const QString& packageName);
    void unfreezeApp(const QString& packageName);
    void extractApp(const QString& packageName, const QString& targetPath);
private:
    static SoftManageTool* instance;
    ADBTools tool;
    SoftTools *softTool;
};

#endif
