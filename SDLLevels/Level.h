#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include "SpriteSheet.h"
#include "Renderer.h"
#include "Timing.h"
#include "TTFont.h"

class Level
{
public:
    // Constructor and Destructor
    Level(SpriteSheet* sheet, Renderer* renderer, TTFont* font);
    ~Level();

    // Serialize and Deserialize functions
    void Serialize(std::ostream& stream);
    void Deserialize(std::istream& stream);

    // Function to run level1 logic
    void RunLevel1Logic(float deltaTime);

private:
    // Variables to save and load
    float rectX;
    float rectAsh;
    float scale;
    int spriteWidth;
    int spriteHeight;
    int currentFrame;

    // Dependencies (Renderer, Sheet, etc.)
    SpriteSheet* sheet;
    Renderer* renderer;
    TTFont* font;
};

#endif
