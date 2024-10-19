#ifndef LEVEL_H
#define LEVEL_H

#include "StandardIncludes.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include "Timing.h"
#include "TTFont.h"

class Level : public Resource
{
public:
    
    Level(SpriteSheet* sheet, Renderer* renderer, TTFont* font);
    ~Level();

    //save and load
    void Serialize(std::ostream& _stream);
    void Deserialize(std::istream& _stream);

    
    void RunLevel1Logic(float deltaTime, float gameTime);
    void RunLevel2Logic(float deltaTime, float gameTime);
    void SetAutoSaveStatus(const std::string& _status);
    bool Level2TransitionTriggered();
    bool Level2EndTriggered();
    
    
    bool autoSaved;
    bool initializePosition;
    

private:
    // Variables I will be sending to save and load
    float rectX;
    float rectAsh;
    float scale;
    int spriteWidth;
    int spriteHeight;
    int currentFrame;
    int viewportEdge;

    float autoSaveMsgTimer;
    string m_autoSaveStatus;

    void InitializeWarriorSpeeds(float deltaTime);
    

    // Dependencies 
    SpriteSheet* sheet;
    Renderer* renderer;
    TTFont* font;
};

#endif
