#ifndef FLASHTOOL_H
#define FLASHTOOL_H

#include <QObject>

class FlashTool : public QObject
{
    Q_OBJECT
public:
    FlashTool(QObject *parent = nullptr);
    void flashPartition(const QString &artition, const QString &imgPath);  //刷写分区
    void startPartition(const QString &imgPath);  //临时启动
    void eraserPartition(const QString &artition);  //清除分区
    static FlashTool* getInstance(QObject *parent = nullptr);
private:
    static FlashTool* instance;
};

#endif // FLASHTOOL_H
