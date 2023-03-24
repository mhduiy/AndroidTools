#ifndef ADBTOOLS_H
#define ADBTOOLS_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <QStringList>

//DCORE_USE_NAMESPACE

class ADBTools : public QObject{
    Q_OBJECT
public:
    explicit ADBTools(QObject *parent = nullptr);
    ~ADBTools();

    QString testCmd(const QString &cmd);

signals:

private:

};

#endif
