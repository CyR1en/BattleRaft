#ifndef BATTLERAFT_BATTLERAFT_H
#define BATTLERAFT_BATTLERAFT_H

#include "Board.h"

class BattleRaft {
private:
    Board playerBoard;
    ComputerBoard computerBoard;
    bool isRunning;

    void loop() ;

    static void printInstruction();

public:
    explicit BattleRaft(const char * player_csv_board_path);

    void start();
};

#endif
