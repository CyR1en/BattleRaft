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
    /**
   ComputerBoard c_board;
   BoardSetter::setCompBoard(c_board);
   std::cout << c_board << std::endl;

   Board board;
   CSVReader reader(argv[1]);
   reader.parse();
   BoardSetter::setPlayerBoard(board, reader);
   std::cout << board << std::endl;
     **/
    /**
   std::string s = "Carrier";
   Raft r(s, 5, H, "B2");
   r.getParts();
   for(Coord p: r.getParts())
       std::cout << coord_to_string(p) << " ";
       **/
    return 0;
}
