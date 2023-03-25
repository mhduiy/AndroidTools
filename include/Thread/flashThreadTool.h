#ifndef FLASHTHREADTOOL_H
#define FLASHTHREADTOOL_H

#include <QObject>
#include "myTypes.h"
#include "ADBTools.h"

class FlashThreadTool : public QObject{
    Q_OBJECT
public:
    explicit FlashThreadTool(QObject *parent = nullptr);
    ~FlashThreadTool();
    void FlashPGInfo();
    static FlashThreadTool *getInstance(QObject *parent = nullptr);
signals:
    void newDeviceConnect(MHDUIY::deviceBaceInfo *info);
    void readDeviceInfoFinish(MHDUIY::deviceRealTimeInfo *info);
private:
    ADBTools tool;
    static FlashThreadTool *instance;
    MHDUIY::deviceRealTimeInfo *info = nullptr;
};


#endif
