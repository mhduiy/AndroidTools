#ifndef SOFTMANAGETOOL_H
#define SOFTMANAGETOOL_H

#include <QObject>
#include "myTypes.h"
#include "ADBTools.h"
#include "softtools.h"

class SoftManageTool : public QObject {
    Q_OBJECT
public:

    static SoftManageTool* getInstance(QObject *parent = nullptr);

    enum SOFTFLAG{
        SOFT_TOTAL,
        SOFT_SYS,
        SOFT_THIRD
    };
    enum OPERATFLAG {
        OP_INSTALL = 0, //安装
        OP_UNINSTALL,   //卸载
        OP_CLEARDATA,   //清除数据
        OP_EXTRACT,      //提取
        OP_FREEZE,      //冻结
        OP_UNFREEZE     //解冻
    };

    explicit SoftManageTool(QObject *parent = nullptr);
    ~SoftManageTool();
    QStringList getSoftList(SOFTFLAG flag);                     //获取软件包名列表
    MHDUIY::SoftInfo &getSoftInfo(const QString &packageName);   //获取软件详细信息
    bool operateSoft(OPERATFLAG flag, const QString &packageName);  //通过包名操作软件

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
