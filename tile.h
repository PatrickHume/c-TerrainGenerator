#define DEEPWATER     15 , 94 , 156
#define WATER         35 , 137, 218
#define MOSS          107, 142, 35 
#define DARKMOSS      81 , 116, 0  
#define LIGHTSAND     251, 234, 181
#define SAND          222, 205, 154
#define DARKSAND      194, 178, 128
#define DARKSTONE     142, 142, 133
#define STONE         168, 168, 159
#define LIGHTSTONE    196, 196, 186
#define SNOW          255, 255, 255

#define colour(c) colourTest(c);
#define colourTest(a,b,c) _r=a; _g=b; _b=c;

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
    void updateColour();
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