#include <DApplication>
#include <DWidgetUtil>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QScreen>
#include "mainWindow.h"

DWIDGET_USE_NAMESPACE //使用DWidget命名空间

int main(int argc, char *argv[]) {
    DApplication a(argc, argv);

    a.setApplicationName("Android Tools");
    a.setApplicationVersion("1.0");
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.loadTranslator(QList<QLocale>() << QLocale::system());
    a.setProductIcon(QIcon(":/Icon/appIcon.png"));
    a.setWindowIcon(QIcon(":/Icon/appIcon.png"));

    //开启Debug调试
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    MainWindow w;
    w.show();
    w.resize(a.primaryScreen()->size() / 1.5);
    Dtk::Widget::moveToCenter(&w);

    a.exec();
}
