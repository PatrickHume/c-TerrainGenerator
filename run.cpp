#include "renderer.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Renderer renderer = Renderer();
    renderer.createWindow();
    renderer.beginTerrainRender();
}
