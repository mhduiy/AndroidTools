#ifndef UPDATETHREADTOOL_H
#define UPDATETHREADTOOL_H

#include <QObject>
#include "myTypes.h"
#include "ADBTools.h"

class UpdateThread : public QObject{
    Q_OBJECT
public:
    explicit UpdateThread(QObject *parent = nullptr);
    ~UpdateThread();
    void FlashPGInfo();
    static UpdateThread *getInstance(QObject *parent = nullptr);
signals:
    void newDeviceConnect(MHDUIY::deviceBaceInfo *info);
    void readDeviceInfoFinish(MHDUIY::deviceRealTimeInfo *info);
private:
    ADBTools tool;
    static UpdateThread *instance;
    MHDUIY::deviceRealTimeInfo *info = nullptr;
};


#endif
