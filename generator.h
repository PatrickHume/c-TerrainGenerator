#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

/* Terrain Generation */
class Generator {
public:
    Generator();
    ~Generator();

    /* Generate Seed */
    int generateSeed();
    int printSeed();
    /* Generate Terrain -
    return 0 on success and 1 on failure */
    int generate();

    void increaseScale();
    void decreaseScale();

    Tile* getTile(int x, int y);

    int getWidth();
private:
    /* Holds all tiles in terrain */
    static const int _width = 128;
    int _heightRange;
    int _log;
    int *_seed;
    Tile *_tiles;
    float _bias;
    int _seaLevel; // yet to be used
};