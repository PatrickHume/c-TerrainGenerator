#include "generator.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <SDL2/SDL.h>

/* Renderer */
class Renderer {
public:
    Renderer();
    ~Renderer();

    int createWindow();
    int beginTerrainRender();
    int renderFrame();
    int renderTerrain();

    void increaseAngle();
    void decreaseAngle();

    void increaseRotationAngle();
    void decreaseRotationAngle();
private:
    static const int _viewWidth = 128;
    static const int _pixelSize = 4;
    static const int _boardSize = _viewWidth*_pixelSize;
    static const int _screenSize = _boardSize*1.5;

    float _viewingAngle;
    float _rotationAngle;
    float _rotationSin;
    float _rotationCos;

    int _viewX;
    int _viewY;

    int done;
    Generator *generator;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
};
