#include "tile.h"

static const int waterLevel = 14;

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
    /* shift world waterlevel to be at height 0 */
    _z -= waterLevel;
    if(_z < 0){
        _z = 0;
    }
    _z *= 2;
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
void Tile::updateColour(){
    if(_z == 0){
        colour(DEEPWATER);
    }else if(_z <= 2){
        colour(WATER);
    }else if(_z <= 5){
        colour(DARKSAND);
    }else if(_z <= 10){
        colour(SAND);
    }else if(_z <= 12){
        colour(LIGHTSAND);
    }else if(_z <= 24){
        colour(MOSS);
    }else if(_z <= 30){
        colour(DARKMOSS);
    }else if(_z <= 38){
        colour(DARKSTONE);
    }else if(_z <= 45){
        colour(STONE);
    }else if(_z <= 50){
        colour(LIGHTSTONE);
    }else{
        colour(SNOW);
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
