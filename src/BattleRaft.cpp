#include "BattleRaft.h"
#include "input.h"

BattleRaft::BattleRaft(const char *path) : playerBoard(), computerBoard(), isRunning(false) {
    CSVReader reader(path);
    reader.parse();
    BoardSetter::setPlayerBoard(playerBoard, reader);
    BoardSetter::setCompBoard(computerBoard);
}

void BattleRaft::start() {
    printInstruction();
    std::cout << "Press enter to continue . . ." << "\n";
    std::cin.get();
    clear_screen();
    isRunning = true;
    loop();
}

void BattleRaft::loop() {
    bool isPlayerTurn = true;
    while (isRunning) {
        std::cout << "Computer's Board:" << std::endl << computerBoard << std::endl;
        std::cout << "Your Board:" << std::endl <<playerBoard << std::endl;

        std::cout << "It's " << (isPlayerTurn ? "your turn!" : "the computer's turn") << std::endl;
        std::string in = isPlayerTurn ? io::ask_coord_input() :
                         coord_to_string(Coord(rand(0, 9), rand(0, 9)));
        clear_screen();
        if (in == "exit") {
            std::cout << "Thanks for playing the game";
            std::exit(0);
        }

        Coord coord = string_to_coord(in.c_str());

        if (isPlayerTurn) {
            std::cout << "You chose to attack at " << in << std::endl;
            computerBoard.attack(coord);
            if (computerBoard.getRafts().size() == computerBoard.getDestroyed().size()) {
                std::cout << "You won the game!" << std::endl;
                std::cout << "Thanks for playing!" << std::endl;
                isRunning = false;
                break;
            }
        } else {
            std::cout << "The computer chose to attack at " << in << std::endl;
            playerBoard.attack(coord);
            if (playerBoard.getRafts().size() == playerBoard.getDestroyed().size()) {
                std::cout << "The computer won the game, better luck next time!" << std::endl;
                std::cout << "Thanks for playing!" << std::endl;
                isRunning = false;
                break;
            }
        }
        isPlayerTurn = !isPlayerTurn;
    }
}

void BattleRaft::printInstruction() {
    std::cout << "=================== Welcome to BattleRafts ====================" << std::endl;
    std::cout << "| Your goal is to hit all of the computer's raft on its board.|" << std::endl;
    std::cout << "| You and the computer will take turns and whoever wipes all  |" << std::endl;
    std::cout << "| of the raft on the opponent's board wins.                   |" << std::endl;
    std::cout << "|                                                             |" << std::endl;
    std::cout << "| The board is a 10 x 10 grid, and is coordinated with the    |" << std::endl;
    std::cout << "| letters [A-J] on the x-axis (left-to-right) and [1-10] on   |" << std::endl;
    std::cout << "| the y-axis (top-to-bottom).                                 |" << std::endl;
    std::cout << "|                                                             |" << std::endl;
    std::cout << "| The computer's board will be display above your board       |" << std::endl;
    std::cout << "| without showing the actual the position of each rafts.      |" << std::endl;
    std::cout << "|                                                             |" << std::endl;
    std::cout << "| On your board, (~) indicates water, and (1) is a segment of |" << std::endl;
    std::cout << "| your rafts.                                                 |" << std::endl;
    std::cout << "|                                                             |" << std::endl;
    std::cout << "| Send an attack by entering a valid coordinate (i.e A1, B10).|" << std::endl;
    std::cout << "|                                                             |" << std::endl;
    std::cout << "| On the computer's board preview, missed targets will be     |" << std::endl;
    std::cout << "| marked with (0) and hit targets with (x).                   |" << std::endl;
    std::cout << "|                                                             |" << std::endl;
    std::cout << "| When a segment of the raft gets hit, the whole rafts gets   |" << std::endl;
    std::cout << "| destroyed immediately.                                      |" << std::endl;
    std::cout << "===============================================================" << std::endl;
}

