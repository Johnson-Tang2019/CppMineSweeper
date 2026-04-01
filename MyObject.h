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
    Q_INVOKABLE int getSize();
    void setRoot(QObject* _root);
    float getRate();
    Q_INVOKABLE void clickBox(int index);
    Q_INVOKABLE void gameOver();

signals:
    void updateBox(int index, int number);
};

#endif