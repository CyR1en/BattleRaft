# CSCI 2312 Final Project: BattleRaft

#### Ethan Bacurio (109977009)

Project Status: Compiles and runs as intended.

### Structure
The project structure is illustrated below:
```
root
  |
  |__build //generated after make
  |    |
  |    |__apps //dir for binaries
  |    |
  |    |__objects //dir for compiled obj.
  |
  |__include //dir for all the header files.
  |    |
  |    |_io //dir for all io headers.
  |    |
  |    |_model //dir for enitity headers.
  |    |
  |    |_util //dir for all util headers
  |
  |__src //dir for all source files.
  |    |
  |    |_io //dir for all io source files.
  |    |
  |    |_model //dir for enitity source files.
  |    |
  |    |_util //dir for util source files.
  |
  |_resource //contains all csv files for raft placements
```

_this project is managed using Makefile (for csegrid) and Cmake (for clion)_

### Compilation
To compile the project
```
make clean all
```
Compiled objs can be found in ```/build/objects``` and the executable binary can be found in `/build/apps`.

To run after compilation
```
./build/apps/BattleRafts [path to csv file]

example:
./build/apps/BattleRafts resource/ship_placement1_good.csv
./build/apps/BattleRafts resource/ship_placement2_good.csv
```
