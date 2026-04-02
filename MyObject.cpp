#include "MyObject.h"
#include <QGuiApplication>
#include "minesweeper.h"


using namespace std;

double rate[3] = {SIMPLE_MINE_RATE, MIDDLE_MINE_RATE, HARD_MINE_RATE};
int sizeNumber[3] = {SIMPLE_SIZE, MIDDLE_SIZE, HARD_SIZE};
string rateText[3] = {"simple", "middle", "hard"};
int rateIndex = 0;
bool startFlag = false;
std::vector<bool> visited;
int unopenedBox = 0;

MineSweeper* mineSweeper;

void MyClickObject::changeRate() {

    QObject *selectRateText = root->findChild<QObject*>("select_difficulty");
    
    if (selectRateText) {
        rateIndex = (rateIndex + 1) % 3;
        selectRateText->setProperty("text", QString::fromStdString(rateText[rateIndex]));
        qDebug() << "Rate changed to:" << selectRateText->property("text").toString();
    }
}

int MyClickObject::getSize() {
    return sizeNumber[rateIndex];
}

void MyClickObject::setRoot(QObject* _root) {
    root = _root;
}

double getRate() { return rate[rateIndex]; }

void MyClickObject::gameOver() {
    resetGame();
    emit updateBox(-1, -1);  // 发送特殊信号通知 QML 游戏结束
}

void MyClickObject::resetGame() {
    unopenedBox = 0;
    startFlag = false;
    visited.clear();
    delete mineSweeper;
    mineSweeper = nullptr;
    
}

int MyClickObject::getBoxCount() {
    return unopenedBox - mineSweeper->getMineCount();
}   

int MyClickObject::getMineCount() {
    return mineSweeper->getMineCount();
}

void MyClickObject::clickBox(int index) {
    if(index < 0 || index >= sizeNumber[rateIndex] * sizeNumber[rateIndex])
        return;
    if(!startFlag){
        unopenedBox = sizeNumber[rateIndex] * sizeNumber[rateIndex];
        int x = index / sizeNumber[rateIndex];
        int y = index % sizeNumber[rateIndex];
        mineSweeper = new MineSweeper(x, y, sizeNumber[rateIndex], rate[rateIndex]);
        startFlag = true;
        visited.resize(sizeNumber[rateIndex] * sizeNumber[rateIndex], false);
    }
    int count = mineSweeper->
        countAdjacentMines(index / sizeNumber[rateIndex], index % sizeNumber[rateIndex]);
    if(count == -1){
        gameOver();
        return;
    } else {
        if (count > 0) {
            unopenedBox--;
            emit updateBox(index, count);
            if(index >= 0 && index < visited.size()) {
                visited[index] = true;
            }
        }else {
            unopenedBox--;
            emit updateBox(index, 0);
            if(index >= 0 && index < visited.size()) {
                visited[index] = true;
            }
            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++){
                    if(i == 0 && j == 0)
                        continue;
                    if((index / sizeNumber[rateIndex] + i) < 0 || (index / sizeNumber[rateIndex] + i) 
                        >= sizeNumber[rateIndex] || (index % sizeNumber[rateIndex] + j) < 0 
                        || (index % sizeNumber[rateIndex] + j) >= sizeNumber[rateIndex])
                          continue;
                    if(!visited[(index / sizeNumber[rateIndex] + i) * 
                        sizeNumber[rateIndex] + (index % sizeNumber[rateIndex] + j)])
                        clickBox((index / sizeNumber[rateIndex] + i) * 
                            sizeNumber[rateIndex] + (index % sizeNumber[rateIndex] + j));
                }
            }
        }
        if(unopenedBox == mineSweeper->getMineCount()){
            winGame();
        }
    }
    
}