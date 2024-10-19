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
    

private:
    // Variables I will be sending to save and load
    float rectX;
    float rectAsh;
    float scale;
    int spriteWidth;
    int spriteHeight;
    int currentFrame;
    std::vector<int> m_randSpeeds;
    std::vector<float> m_warriorXPositions;
    int viewportEdge;
    bool isGenerated = false;

    // Methods
    void GenerateRandomSpeeds();
    void InitializeWarriorPositions(vector<float> _warriorXPositions);

    float autoSaveMsgTimer;
    string m_autoSaveStatus;


    // Dependencies 
    SpriteSheet* sheet;
    Renderer* renderer;
    TTFont* font;
};

#endif
