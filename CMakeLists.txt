cmake_minimum_required(VERSION 3.17)
project(BattleRaft)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)
include_directories(include/util)
include_directories(include/model)
include_directories(include/io)

add_executable(BattleRaft2 src/main.cpp src/util/BitGrid.cpp include/util/BitGrid.h src/util/Bitset.cpp include/util/Bitset.h src/util/util.cpp include/util/util.h src/model/Board.cpp include/model/Board.h src/model/Raft.cpp include/model/Raft.h src/io/input.cpp include/io/input.h src/BattleRaft.cpp include/BattleRaft.h src/io/CSVReader.cpp include/io/CSVReader.h)