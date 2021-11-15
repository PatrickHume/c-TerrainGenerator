#include "generator.h"
#include <cstdlib>
#include <math.h>
#include <stdlib.h>

/* Generator */
Generator::Generator(){
    srand(time(0));
    _heightRange = 128;
    _seed = (int*)malloc((_width * _width) * sizeof(int));
    _tiles = (Tile*)malloc((_width * _width) * sizeof(Tile));
    _log = log2(_width);
    _bias = 1.6f;

    for(int x = 0; x < _width; x++){
        for(int y = 0; y < _width; y++){
            _tiles[(x*_width) + y] = Tile(x,y,0);
        }
    }
    generateSeed();
    generate();
}
/* Destructor */
Generator::~Generator(){
    free(_tiles);
    free(_seed);
}
/* return pointer to tile at x, y */
Tile* Generator::getTile(int x, int y){
    return &_tiles[(x*_width) + y];
}
/* get width */
int Generator::getWidth(){
    return _width;
}
/* increase and decrease the resolution of the generation */
void Generator::increaseScale(){
    _bias += 0.1f;
    generate();
}
void Generator::decreaseScale(){
    _bias -= 0.1f;
    generate();
}
/* generate array of random values to sample during generation, in _seed */
int Generator::generateSeed(){
    for(int x = 0; x < _width; x++){
        for(int y = 0; y < _width; y++){
            _seed[(x*_width) + y] = rand() % _heightRange;
        }
    }    
    return 0;
}
/* print array of random values to sample during generation */
int Generator::printSeed(){
    for(int x = 0; x < _width; x++){
        for(int y = 0; y < _width; y++){
            printf("%i,",_seed[(x*_width) + y]);
        }
        printf("\n");
    }    
    return 0;
}
/* generate terrain by populating _tiles  */
int Generator::generate() {
    float resolution = 1.0f;
    int nOctaves = _log * resolution;

    for(int x = 0; x < _width; x++){
        for(int y = 0; y < _width; y++){
            float noise = 0.0f;
            float scaleAcc = 0.0f;
            float scale = 1.0f;
            for(int n = 0; n < nOctaves; n++){
                int pitch = _width >> n;

                int sampleX1 = (x/pitch) * pitch;
                int sampleY1 = (y/pitch) * pitch;

                int sampleX2 = (sampleX1 + pitch) % _width;
                int sampleY2 = (sampleY1 + pitch) % _width;

                float blendX = (float)(x - sampleX1)/(float)pitch;
                float blendY = (float)(y - sampleY1)/(float)pitch;

                float sampleT = (1-blendX)*_seed[sampleX1*_width + sampleY1] + blendX*_seed[sampleX2*_width + sampleY1];
                float sampleB = (1-blendX)*_seed[sampleX1*_width + sampleY2] + blendX*_seed[sampleX2*_width + sampleY2];

                scaleAcc += scale;
                noise += (blendY * (sampleB - sampleT) + sampleT) * scale;
                scale = scale / _bias;
            }
            noise *= 0.5;
            noise /= _heightRange * scaleAcc;
            Tile* tile = getTile(x,y);

            tile->setZ(noise*512);
            tile->updateColour();
        }
    }
    return 0;
}
