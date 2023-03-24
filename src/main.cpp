#include <DApplication>
#include <DWidgetUtil>
#include <QGuiApplication>
#include <QLoggingCategory>
#include "mainWindow.h"

DWIDGET_USE_NAMESPACE //使用DWidget命名空间

int main(int argc, char *argv[]) {
    DApplication a(argc, argv);

    a.setApplicationName("Android Tools");
    a.setApplicationVersion("1.0");

    //开启Debug调试
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    MainWindow w;
    w.show();
    w.resize(1920*0.6,1080*0.6);
    Dtk::Widget::moveToCenter(&w);

    a.exec();
}
