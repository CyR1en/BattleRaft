#ifndef BATTLERAFT_BOARD_H
#define BATTLERAFT_BOARD_H

#include "BitGrid.h"
#include "CSVReader.h"
#include "Raft.h"

class Board : public BitGrid {
private:
    std::vector<Coord> hits;
    std::vector<Coord> missed;
    std::vector<Raft> rafts;
    std::vector<Raft> destroyed;

protected:
    vector<std::vector<std::string>> renderDestroyed(std::vector<std::vector<std::string>> &p_rendered) const;

public:
    Board();

    void attack(const Coord &coord);

    void placeRaft(const Raft &raft, bool print_err);

    bool isRaftOutBound(const Raft &raft);

    const std::vector<Coord> &getHits() const;

    const std::vector<Coord> &getMissed() const;

    const std::vector<Raft> &getRafts() const;

    const std::vector<Raft> &getDestroyed() const;

    std::vector<Coord> getUsedCoords();

    virtual std::vector<std::vector<std::string>> renderBoard() const;

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

class ComputerBoard : public Board {
public:
    std::vector<std::vector<std::string>> renderBoard() const override;

    friend std::ostream &operator<<(std::ostream &out, const ComputerBoard &b);
};

struct BoardSetter {
private:
    static Coord findValidCoord(Board &c_board, std::string &type, Orientation &o);

public:
    static void setPlayerBoard(Board &board, CSVReader &reader);

    static void setCompBoard(Board &c_board);
};

#endif
