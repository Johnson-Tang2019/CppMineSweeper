#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <time.h>
#include <iostream>

#define SIMPLE_MINE_RATE 0.12
#define MIDDLE_MINE_RATE 0.16
#define HARD_MINE_RATE 0.20
#define SIMPLE_SIZE 9
#define MIDDLE_SIZE 16
#define HARD_SIZE 24

class MineData {
private:
typedef std::vector<std::vector<int>> Matrix;
    Matrix mine;

public:
    MineData(int firstX, int firstY, int n = SIMPLE_SIZE, float mine_rate = SIMPLE_MINE_RATE) {
        mine.resize(n, std::vector<int>(n, 0));
        srand(time(NULL));

        for (int i = n * n * mine_rate; i > 0; i--){
            while (true) {
                int x = rand() % n;
                int y = rand() % n;
                if (mine[x][y] == 0 && (x > firstX + 1 || x < firstX - 1) && 
                    (y > firstY + 1 || y < firstY - 1)) {
                    mine[x][y] = 1;
                    break;
                }
            }
        }
    }   

    int getMineData(int x, int y){
        if((x < 0 || x >= mine[0].size()) || (y < 0 || y >= mine[0].size()))
            return 0;
        else
            return mine[x][y];
    }

    int getMineSize(){
        return mine.size();
    }

    void printMineData(){
        for(int i = 0; i < mine.size(); i++){
            for(int j = 0; j < mine[i].size(); j++){
                std::cout << mine[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

class MineSweeper{
private:
    MineData minedata;

public:
    MineSweeper(int x, int y, int n = SIMPLE_SIZE, float mine_rate = SIMPLE_MINE_RATE): minedata(x, y, n, mine_rate) {}

    int getMineCount(){
        int count = 0;
        for(int i = 0; i < minedata.getMineSize(); i++){
            for(int j = 0; j < minedata.getMineSize(); j++){
                count += minedata.getMineData(i, j);
            }
        }
        return count;
    }

    int countAdjacentMines(int x, int y){
        if(minedata.getMineData(x, y) == 1){
            return -1; // 如果是雷，返回 -1
        }

        int count = 0;
        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                count += minedata.getMineData(x + i, y + j);
            }
        }
        return count;
    }
};

#endif