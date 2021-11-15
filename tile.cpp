#include "tile.h"

static const int waterLevel = 100;

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
void Tile::updateColour(){
    if(_z <= waterLevel-1){
        colour(DEEPWATER);
        _z = waterLevel;
    }else if(_z <= waterLevel){
        colour(WATER);
        _z = waterLevel;
    }else if(_z <= waterLevel+10){
        colour(DARKSAND);
    }else if(_z <= waterLevel+20){
        colour(SAND);
    }else if(_z <= waterLevel+22){
        colour(LIGHTSAND);
    }else if(_z <= waterLevel+24){
        colour(MOSS);
    }else if(_z <= waterLevel+50){
        colour(DARKMOSS);
    }else if(_z <= waterLevel+60){
        colour(DARKSTONE);
    }else if(_z <= waterLevel+70){
        colour(STONE);
    }else if(_z <= waterLevel+80){
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
