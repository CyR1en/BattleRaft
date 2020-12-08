#include "CSVReader.h"
#include "Raft.h"
#include "BattleRaft.h"
#include "util.h"

/**
 * Main function
 *
 * Because of the fact that I chose to require the csv path to construct the game. I've also decided to
 * use the main function with argument vector to pass in the path when executing the game.
 */
int main(int argc, const char *argv[]) {
    if(argc != 2) { //argv[0] == name of program. So args starts at [1]
        std::cerr << "Invalid arguments";
        std::exit(0);
    }
    std::cout << "CSV Path : " << argv[1] << std::endl;
    BattleRaft battleRaft(argv[1]);
    battleRaft.start();
    return 0;
}
