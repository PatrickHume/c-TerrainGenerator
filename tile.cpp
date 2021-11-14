#include "tile.h"

#define colourDEEPWATER _r=15; _g=94; _b=156;
#define colourWATER _r=35; _g=137; _b=218;
#define colourMOSS _r=74; _g=93; _b=35;
#define colourSAND _r=194, _g=178, _b=128;
#define colourSTONE _r=145; _g=142; _b=133;

static const int waterLevel = 13;

/* Tile */
/* Constructor */
Tile::Tile(int x,int y,int z){
    _x = x;
    _y = y;
    _z = z;

    _r = 0;
    _g = 0;
    _b = 0;
}
/* Destructor */
Tile::~Tile(){
}
/* getters */
tile_type Tile::getTileType(){
    return TILE_NONE;
}
int Tile::getX(){
    return _x;
}
int Tile::getY(){
    return _y;
}
int Tile::getZ(){
    return _z;
}

int Tile::getR(){
    return _r;
}
int Tile::getG(){
    return _g;
}
int Tile::getB(){
    return _b;
}
/* setters */
void Tile::setZ(int z){
    _z = z;
}
void Tile::setR(int r){
    _r = r;
}
void Tile::setG(int g){
    _g = g;
}
void Tile::setB(int b){
    _b = b;
}
void Tile::colour(){
    if(_z <= waterLevel-1){
        colourDEEPWATER;
        _z = waterLevel;
    }else if(_z <= waterLevel){
        colourWATER;
        _z = waterLevel;
    }else if(_z <= waterLevel+2){
        colourSAND;
    }else if(_z <= waterLevel+10){
        colourMOSS;
    }else{
        colourSTONE;
    }
}

/* Tree - tile type not yet used */
/* Constructor */
Tree::Tree(int x,int y,int z):Tile(x, y, z){
}
/* Destructor */
Tree::~Tree(){

}
/* getters */
tile_type Tree::getTileType(){
    return TILE_TREE;
}
