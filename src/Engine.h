#pragma once
#include <vector>
#include <memory>
#include <SDL.h>
#include "Object.h"

struct View {
    int x{0};
    int y{0};
};

class Engine {
public:
    static Engine* E;
    Engine();
    ~Engine();

    // Core engine methods
    void addObject(Object* obj);
    void setView(int x, int y);
    void update();
    SDL_Renderer* getRenderer(){return renderer;}
    static void drawRect(float x, float y, float width, float height, int r, int g, int b, int a=255);
    static void drawImage(float x, float y, float width, float height, std::string textureName);

    Object* getObject(int index){return objects[index].get();}
    Object* getLastObject(){return getObject(objects.size()-1);}
private:
    std::vector<std::unique_ptr<Object>> objects;
    SDL_Window* window;
    SDL_Renderer* renderer;
    View view;
    // Internal methods
    void processInput();
    void updateObjects();
    void render();
};
