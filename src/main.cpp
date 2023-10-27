#include <QApplication>
#include <QLoggingCategory>
#include <QScreen>
#include <QDebug>
#include "MainWindow/mainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //开启Debug调试
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    MainWindow w;
    w.show();
    w.setFixedSize(1200,800);

    a.exec();
}
