#include "CSVReader.h"
#include "Raft.h"
#include "Board.h"
#include "BattleRaft.h"
#include "input.h"
#include "util.h"

int main(int argc, const char *argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid arguments";
        std::exit(0);
    }
    std::cout << "CSV Path : " << argv[1] << std::endl;
    BattleRaft battleRaft(argv[1]);
    battleRaft.start();
    return 0;
}
