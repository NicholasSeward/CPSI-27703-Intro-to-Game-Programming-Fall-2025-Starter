#include "Engine.h"
#include "Object.h"
#include "ImageDevice.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "InputDevice.h"

Engine* Engine::E = nullptr;

Engine::Engine() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    E = this;
}
Engine::~Engine() {
    //ImageDevice::cleanup();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}

void Engine::addObject(Object* obj) {
    if (obj != nullptr) {
        objects.push_back(std::unique_ptr<Object>(obj));
        std::cout << "Added object to engine" << std::endl;
    }
}


void Engine::update() {
    view.x+=1;
    view.y+=1;
    processInput();
    updateObjects();
    render();
}

void Engine::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
        InputDevice::process(event);
    }
}

void Engine::updateObjects() {
    // Update all objects
    for (auto& obj : objects) 
        obj->update();
        
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (auto& obj : objects) 
        obj->render();
    SDL_RenderPresent(renderer);

}

// void Engine::drawRect(float x, float y, float width, float height, int r, int g, int b, int a) {
//     SDL_SetRenderDrawColor(Engine::E->renderer, r, g, b, a);
//     SDL_Rect rect = {(int)x, (int)y, (int)width, (int)height};
//     SDL_RenderFillRect(Engine::E->renderer, &rect);
// }


void Engine::drawRect(float x, float y, float width, float height, int r, int g, int b, int a) {
    
    View& view = Engine::E->view;
    SDL_SetRenderDrawColor(Engine::E->renderer, r, g, b, a);
    SDL_Rect rect = {(int)(x-view.x), (int)(y-view.y), (int)width, (int)height};
    SDL_RenderFillRect(Engine::E->renderer, &rect);
}

void Engine::drawImage(float x, float y, float width, float height, std::string textureName) {
    
    View& view = Engine::E->view;
    SDL_Texture* blockTexture;

    blockTexture = ImageDevice::get(textureName);
    SDL_Rect rect = {(int)(x-view.x), (int)(y-view.y), (int)width, (int)height};
    SDL_RenderCopy(Engine::E->renderer, blockTexture, nullptr, &rect);
}

void Engine::setView(int x, int y) {
    view.x = x;
    view.y = y;
}
