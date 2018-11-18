#include <QGuiApplication>
#include <QQuickView>
#include <QLibrary>
#include <QDebug>
#include <QQmlApplicationEngine>
//#include "physicssetter.h"

#include <Qt3DCore/qaspectengine.h>
int main(int argc, char **argv)
{

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath(QCoreApplication::applicationDirPath() + "/../../imports");
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
