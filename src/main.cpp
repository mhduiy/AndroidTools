#include <DApplication>
#include <DWidgetUtil>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QScreen>
#include <QDebug>
#include "mainWindow.h"

DWIDGET_USE_NAMESPACE //使用DWidget命名空间

int main(int argc, char *argv[]) {
    DApplication *a = DApplication::globalApplication(argc, argv);

    a->setApplicationName("Android Tools");
    a->setApplicationVersion("1.0");
    a->setAttribute(Qt::AA_UseHighDpiPixmaps);
    a->loadTranslator();
    a->setProductIcon(QIcon(":/Icon/AndroidTools.svg"));
    a->setWindowIcon(QIcon(":/Icon/AndroidTools.svg"));

    //开启Debug调试
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    MainWindow w;
    w.show();
    w.setFixedSize(1200,800);
    Dtk::Widget::moveToCenter(&w);

    a->exec();
}
