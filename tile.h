/* The different types of tiles */
typedef enum {
    TILE_NONE,
    TILE_TREE,
} tile_type;

/* Tile */
class Tile {
public:
    Tile(int x, int y, int z);
    ~Tile();

    tile_type getTileType();

    int getX();
    int getY();
    int getZ();

    int getR();
    int getG();
    int getB();

    void setR(int r);
    void setG(int g);
    void setB(int b);

    void setZ(int z);
    void colour();
private:
    int _x;
    int _y;
    int _z;

    int _r;
    int _g;
    int _b;
};

/* Tile */
class Tree : public Tile {
public:
    Tree(int x, int y, int z);
    ~Tree();

    tile_type getTileType();
private:
};