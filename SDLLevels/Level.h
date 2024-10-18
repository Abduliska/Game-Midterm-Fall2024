#ifndef LEVEL_H
#define LEVEL_H

#include "StandardIncludes.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include "Timing.h"
#include "TTFont.h"

class Level
{
public:
    
    Level(SpriteSheet* sheet, Renderer* renderer, TTFont* font);
    ~Level();

    //save and load
    void Serialize(std::ostream& stream);
    void Deserialize(std::istream& stream);

    // Function to run level1 logic
    void RunLevel1Logic(float deltaTime, float gameTime);

    
    bool autoSaved;

private:
    // Variables I will be sending to save and load
    float rectX;
    float rectAsh;
    float scale;
    int spriteWidth;
    int spriteHeight;
    int currentFrame;

    float autoSaveMsgTimer;



    // Dependencies 
    SpriteSheet* sheet;
    Renderer* renderer;
    TTFont* font;
};

#endif
