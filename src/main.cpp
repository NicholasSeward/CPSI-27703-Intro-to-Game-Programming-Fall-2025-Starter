#include "Engine.h"
#include "Object.h"
#include <iostream>
#include "ImageDevice.h"
#include "Dude.h"

//Todo: add images device
//image device will allow for the loading and retrieval of textures
// images are slow to draw...textures are faster
//Todo: add a view

//Todo: add a input device




int main(int argc, char* argv[]) 
{
   
    Engine e;
    ImageDevice::load("stone block", "assets/blocks.png", SDL_Rect{16*12, 16*5, 16, 16});
    ImageDevice::load("wood block", "assets/blocks.png", SDL_Rect{16*12, 16*1, 16, 16});
    ImageDevice::load("dude", "assets/dude.png");
    // Add 10 objects at random positions on an 800x600 screen
    for(int i = 0; i < 10; i++)
    {
        float x = static_cast<float>(rand() % (800 - 100)); // 100 is object width
        float y = static_cast<float>(rand() % (600 - 100)); // 100 is object height
        e.addObject(new Object(x, y, 100, 100));
    }
    e.addObject(new Dude(100, 100));
    Object* lastObject = e.getLastObject();
    int lastTime = SDL_GetTicks();
    double fps = 0.0;
    while(true)   
    {
        int frameStart = SDL_GetTicks();

        e.update();
        e.setView(lastObject->getX()-400+50, lastObject->getY()-300+50);

        int currentTime = SDL_GetTicks();
     
        fps = 1000.0f / (currentTime - lastTime);
        lastTime = currentTime;
        std::cout << "FPS: " << fps << std::endl;
        // std::cout << "Frame Time: " << (currentTime-frameStart) << std::endl;
        SDL_Delay((1000/200) - (currentTime-frameStart)/1000);

    }
    return 0;
}
