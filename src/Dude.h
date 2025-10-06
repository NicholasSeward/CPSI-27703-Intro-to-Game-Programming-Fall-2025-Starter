#pragma once
#include "Object.h"
#include <string>

class Dude : public Object {
public:
    // Constructor with position, size, and texture name
    Dude(float x, float y);
    
    // Override Object methods
    virtual void update() override;
    virtual void render() override;

};
