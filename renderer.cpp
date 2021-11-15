#include "renderer.h"
#include <math.h>

/* Renderer */
/* Constructor */
Renderer::Renderer(){
    _viewingAngle = 0.5;
    _rotationAngle = 0.5;
    _viewX = 0;
    _viewY = 0;

    _rotationSin = sin(_rotationAngle);
    _rotationCos = cos(_rotationAngle);

    generator = new Generator();

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
}
/* Destructor */
Renderer::~Renderer(){
}
/* Create Window */
int Renderer::createWindow(){

    /* Initialize SDL */
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return 1;
    }

    /* Create window and renderer for given surface */
    window = SDL_CreateWindow("Terrain", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenSize, _screenSize, SDL_WINDOW_RESIZABLE);
    if(!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
        return 1;
    }
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);
    if(!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
        return 1;
    }

    /* Clear the rendering surface with the specified color */
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    return 0;
}
void Renderer::increaseAngle(){
    if(_viewingAngle < 1){
        _viewingAngle += 0.05;
    }
}
void Renderer::decreaseAngle(){
    if(_viewingAngle > 0){
        _viewingAngle -= 0.05;
    }
}
void Renderer::increaseRotationAngle(){
    _rotationAngle += 0.1;
    if(_rotationAngle > 6.2){
        _rotationAngle = 0;
    }
    _rotationSin = sin(_rotationAngle);
    _rotationCos = cos(_rotationAngle);
}
void Renderer::decreaseRotationAngle(){
    _rotationAngle -= 0.1;
    if(_rotationAngle < 0){
        _rotationAngle = 6.2;
    }
    _rotationSin = sin(_rotationAngle);
    _rotationCos = cos(_rotationAngle);
}
/* Render Frame */
int Renderer::renderFrame(){
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
       
       /* Re-create when window has been resized */
       if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

          SDL_DestroyRenderer(renderer);

          surface = SDL_GetWindowSurface(window);
          renderer = SDL_CreateSoftwareRenderer(surface);
          /* Clear the rendering surface with the specified color */
          SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
          SDL_RenderClear(renderer);
       }

        switch(e.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch(e.key.keysym.sym){
                    case SDLK_q:
                        generator->increaseScale();
                        break;
                    case SDLK_e:
                        generator->decreaseScale();
                        break;

                    case SDLK_s:
                        decreaseAngle();
                        break;
                    case SDLK_w:
                        increaseAngle();
                        break;

                    case SDLK_a:
                        decreaseRotationAngle();
                        break;
                    case SDLK_d:
                        increaseRotationAngle();
                        break;
                    case SDLK_1: 
                        generator->generateSeed();
                        generator->generate();
                        break;
                    case SDLK_UP: 
                        _viewY -= 8;
                        break;
                    case SDLK_DOWN: 
                        _viewY += 8;
                        break;
                    case SDLK_LEFT: 
                        _viewX -= 8;
                        break;
                    case SDLK_RIGHT: 
                        _viewX += 8;
                        break;
                    default:
                        break;
            }
        }


       if (e.type == SDL_QUIT) {
            done = 1;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return 1;
        }

        if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
            done = 1;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return 1;
        }
    }

    renderTerrain();

    /* Got everything on rendering surface,
       now Update the drawing image on window screen */
    SDL_UpdateWindowSurface(window);

    return 0;
}
int Renderer::renderTerrain(){

    int row = 0,column = 0,x = 0;
    SDL_Rect rect, darea;

    /* Get the Size of drawing surface */
    SDL_RenderGetViewport(renderer, &darea);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);

    rect.w = _pixelSize;

    int flip_x;
    int flip_y;

    if(_rotationAngle < 1.57){
        flip_x = 0;
        flip_y = 0;
    }else if(_rotationAngle < 3.14){
        flip_x = 0;
        flip_y = _viewWidth - 1;
    }else if(_rotationAngle < 4.71){
        flip_x = _viewWidth - 1;
        flip_y = _viewWidth - 1;
    }else{
        flip_x = _viewWidth - 1;
        flip_y = 0;
    }


    for(int x_1 = 0; x_1 < _viewWidth; x_1++){
        for(int y_1 = 0; y_1 < _viewWidth; y_1++){
            int x = abs(x_1 - flip_x);
            int y = abs(y_1 - flip_y);

            Tile* tile = generator->getTile(abs((x+_viewX)%generator->getWidth()),abs((y+_viewY)%generator->getWidth()));

            rect.x = (x * _pixelSize) - _boardSize*0.5;
            rect.y = (y * _pixelSize) - _boardSize*0.5; 

            int xRotated = rect.x * _rotationCos - rect.y * _rotationSin;
            int yRotated = rect.x * _rotationSin + rect.y * _rotationCos;
            rect.x = xRotated;
            rect.y = yRotated;  

            rect.y *= _viewingAngle;
        
            rect.y += _boardSize*0.5*(1-_viewingAngle);

            rect.x += _screenSize*0.5;
            rect.y += _screenSize*0.5;  

            rect.x -= _pixelSize*0.5;
            rect.y -= _pixelSize*0.5;

            rect.h = tile->getZ()*(1-_viewingAngle)*_pixelSize + _pixelSize + 5;
            rect.y -= tile->getZ()*(1-_viewingAngle)*_pixelSize;

            /* draw side of board if drawing edge tile */
            if(x_1 == 0 || y_1 == 0 || x_1 == _viewWidth-1 || y_1 == _viewWidth-1){
                rect.y += _pixelSize;
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0xFF);
            }else{
                SDL_SetRenderDrawColor(renderer, tile->getR(), tile->getG(), tile->getB(), 0xFF);
            }
            /* draw tile */
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    return 0;
}

int Renderer::beginTerrainRender(){

    /* Draw the image to the rendering surface */
    done = 0;
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(loop, 0, 1);
    #else
    while (!done) {
        renderFrame();
    }
    #endif

    SDL_Quit();
    return 0;
}