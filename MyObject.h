#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QQmlApplicationEngine>

class MyClickObject : public QObject{
    QObject *root;
    Q_OBJECT
public:
    explicit MyClickObject(QObject* parent = nullptr) : QObject(parent) {}
    Q_INVOKABLE void changeRate();
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void backToMain();
    void setRoot(QObject* _root);
    float getRate();
};

#endif