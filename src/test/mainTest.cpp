#include <QApplication>
#include <QLoggingCategory>
#include <QScreen>
#include <QDebug>
#include "test/mainTestWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //开启Debug调试
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    MainTestWindow w;
    w.show();
    w.setFixedSize(640,480);

    a.exec();
}
