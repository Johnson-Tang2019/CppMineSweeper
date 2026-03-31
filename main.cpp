#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QQmlContext>
#include <QQuickItem>
#include <QObject>
#include <QString>
#include "minesweeper.h"
#include "MyObject.h"
using namespace std;


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SimpleMineSweeper", "Main");

    QObject *root = engine.rootObjects().first();
    QObject *selectText = root->findChild<QObject *>("select");
    MyClickObject myClickObj;
    myClickObj.setRoot(root);
    engine.rootContext()->setContextProperty("myClickObject", &myClickObj);
    return app.exec();
}
