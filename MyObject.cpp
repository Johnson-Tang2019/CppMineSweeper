#include "MyObject.h"
#include <QGuiApplication>
#include "minesweeper.h"

using namespace std;

double rate[3] = {SIMPLE_MINE_RATE, MIDDLE_MINE_RATE, HARD_MINE_RATE};
string rateText[3] = {"simple", "middle", "hard"};
int rateIndex = 0;

void MyClickObject::changeRate() {

    QObject *selectRateText = root->findChild<QObject*>("select_difficulty");
    
    if (selectRateText) {
        rateIndex = (rateIndex + 1) % 3;
        selectRateText->setProperty("text", QString::fromStdString(rateText[rateIndex]));
        qDebug() << "Rate changed to:" << selectRateText->property("text").toString();
    }
}

void MyClickObject::startGame() {
    
    
}

void MyClickObject::backToMain() {
    
    
}

void MyClickObject::setRoot(QObject* _root) {
    root = _root;
}

double getRate() { return rate[rateIndex]; }