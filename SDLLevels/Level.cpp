#include "Level.h"
#include <random>
#include <stdbool.h>


Level::Level(Renderer* renderer, TTFont* font)
    : rectX(0.0f), rectAsh(0.0f), scale(1.8f), 
    spriteWidth(69), spriteHeight(44), currentFrame(0),
    renderer(renderer), font(font), autoSaved(false), m_autoSaveStatus("AutoSave:No"), autoSaveMsgTimer(0.0f),
    m_warriorXPositions(10, 0.0f), m_rockYPositions(10, 0.0f), 
    m_warriorIsAlive(10, true), m_rockIsAlive(10, true), m_warriorDeathState(10, false),
    scaleRock(1.0f), spriteWidthRock(20), spriteHeightRock(20),
    viewportEdge(1920)
{
    if(!isGenerated) GenerateRandomSpeeds();
    GenerateWarriorSheets();
    GenerateRockSheets();
}

Level::~Level(){}

void Level::Serialize(std::ostream& _stream)
{
    _stream.write(reinterpret_cast<char*>(&rectX), sizeof(rectX));
    _stream.write(reinterpret_cast<char*>(&rectAsh), sizeof(rectAsh));
    _stream.write(reinterpret_cast<char*>(&currentFrame), sizeof(currentFrame));
    _stream.write(reinterpret_cast<char*>(&scale), sizeof(scale));
    _stream.write(reinterpret_cast<char*>(&spriteWidth), sizeof(spriteWidth));
    _stream.write(reinterpret_cast<char*>(&spriteHeight), sizeof(spriteHeight));
    std::cout << "Level Saved Successfully" << endl;
    Resource::Serialize(_stream);
}


void Level::Deserialize(std::istream& _stream)
{
    _stream.read(reinterpret_cast<char*>(&rectX), sizeof(rectX));
    _stream.read(reinterpret_cast<char*>(&rectAsh), sizeof(rectAsh));
    _stream.read(reinterpret_cast<char*>(&currentFrame), sizeof(currentFrame));
    _stream.read(reinterpret_cast<char*>(&scale), sizeof(scale));
    _stream.read(reinterpret_cast<char*>(&spriteWidth), sizeof(spriteWidth));
    _stream.read(reinterpret_cast<char*>(&spriteHeight), sizeof(spriteHeight));
    Resource::Deserialize(_stream);
    std::cout << "Level Loaded Successfully" << endl;

}

void Level::SetAutoSaveStatus(const std::string& _status)
{
    m_autoSaveStatus = _status;
}

void Level::InitializeWarriorPositions(vector<float> _warriorXPositions)
{
    _warriorXPositions.assign(10, 0.0f);
}

void Level::GenerateRandomSpeeds() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(80, 100);  // random speed between 80 and 100

    m_randSpeeds.resize(10);  // resize to hold 10 speeds
    for (int& speed : m_randSpeeds) {
        speed = dist(rd);  // store the random speed
        std::cout << "Generated Speed: " << speed << std::endl;
    }

    isGenerated = true;
}

void Level::GenerateWarriorSheets() 
{
    for (int i = 0; i < 10; i++) 
    {
        SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
        sheet->Load("../Assets/Textures/Warrior.tga");
        sheet->SetSize(17, 6, 69, 44);
        sheet->AddAnimation(EN_AN_RUN, 6, 7, (float)m_randSpeeds[i]/100.0f * 6.0f);
        sheet->AddAnimation(EN_AN_DEATH, 27, 10, (float)m_randSpeeds[i]/100.0f * 6.0f);

        m_warriorSheets.push_back(sheet);
    }
}

void Level::GenerateRockSheets()
{
    for (int i = 0; i < 10; i++)
    {
        SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
        sheet->Load("../Assets/Textures/Rock.tga");
        sheet->SetSize(1, 4, 20, 20);
        sheet->AddAnimation(ROCK_FALL, 0, 4, (float)m_randSpeeds[i] / 100.0f * 6.0f);

        m_rockSheets.push_back(sheet);
    }
}

bool CheckCollision(float x1A, float y1A, float x2A, float y2A,
    float x1B, float y1B, float x2B, float y2B) {
    // Check if the rectangles overlap
    return !(x1A > x2B || x2A < x1B || y1A > y2B || y2A < y1B);
}

void Level::RunLevel1Logic(float deltaTime,float gameTime)
{   
    int offsets[] = { 10, 110, 210, 310, 410, 510, 610, 710, 810, 910 };  // y-offsets


    renderer->SetDrawColor(Color(128, 128, 128, 255));
    renderer->ClearScreen();

    // setting my warriors
    for (int i = 0; i < 10;i++)
    {
        m_warriorXPositions[i] += m_randSpeeds[i] * deltaTime;
        renderer->RenderTexture(m_warriorSheets[i], m_warriorSheets[i]->Update(EN_AN_RUN, deltaTime),
            Rect(m_warriorXPositions[i], offsets[i], (m_warriorXPositions[i] + spriteWidth * scale), (offsets[i] + spriteHeight * scale)));
    }

    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 10, (rectX + spriteWidth * scale), (10 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 110, (rectX + spriteWidth * scale), (110 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 210, (rectX + spriteWidth * scale), (210 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 210, (rectX + spriteWidth * scale), (210 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 310, (rectX + spriteWidth * scale), (310 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 410, (rectX + spriteWidth * scale), (410 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 510, (rectX + spriteWidth * scale), (510 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 610, (rectX + spriteWidth * scale), (610 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 710, (rectX + spriteWidth * scale), (710 + spriteHeight * scale)));
    //renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
    //    Rect(rectX, 810, (rectX + spriteWidth * scale), (810 + spriteHeight * scale)));
   
    

    //GUI fps
    std::string fps = "FPS: " + std::to_string(Timing::Instance().GetFPS());
    font->Write(renderer->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 100, 0 });

    std::string time = "Game Time: " + std::to_string(static_cast<int>(gameTime));
    font->Write(renderer->GetRenderer(), time.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });
    
    font->Write(renderer->GetRenderer(), m_autoSaveStatus.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 500, 0 });

    
    //std::cout << "Delta Time: " << deltaTime << std::endl;
}

bool Level::Level2TransitionTriggered()
{
    for (int i = 0; i < 10; i++)
    {
        if (m_warriorXPositions[i] >= viewportEdge - spriteWidth)
        {
            std::cout << "Warrior " << i << " was first!" << std::endl;
            m_warriorXPositions = std::vector <float>(10, 0.0f);
            return true;
        }
    }

    return false;  // No warrior has crossed yet
   
    
}

void Level::RunLevel2Logic(float deltaTime, float gameTime) 
{
    int offsets[] = { 10, 110, 210, 310, 410, 510, 610, 710, 810, 910 };  // y-offsets  
    int offsetsRock[] = { 10, 110, 210, 310, 410, 510, 610, 710, 810, 910 };  // x-offsets  

    renderer->SetDrawColor(Color(0, 128, 0, 255));
    renderer->ClearScreen();

    // Warriors
    for (int i = 0; i < 10;i++)
    {
        if (m_warriorIsAlive[i])
        {
            if(!m_warriorDeathState[i])
            { 
                m_warriorXPositions[i] += m_randSpeeds[i] * deltaTime;
                renderer->RenderTexture(m_warriorSheets[i], m_warriorSheets[i]->Update(EN_AN_RUN, deltaTime),
                    Rect(m_warriorXPositions[i], offsets[i], (m_warriorXPositions[i] + spriteWidth * scale), (offsets[i] + spriteHeight * scale)));
            }
            else
            {
                if(m_warriorSheets[i]->GetCurrentClip(EN_AN_DEATH) == 36)
                { 
                    m_warriorIsAlive[i] = false;
                }
                else
                {
                    renderer->RenderTexture(m_warriorSheets[i], m_warriorSheets[i]->Update(EN_AN_DEATH, deltaTime),
                        Rect(m_warriorXPositions[i], offsets[i], (m_warriorXPositions[i] + spriteWidth * scale), (offsets[i] + spriteHeight * scale)));
                }
            }
        }
    }

    //Rocks
    for (int i = 0; i < 10; i++)
    {
        if(m_rockIsAlive[i])
        { 
            m_rockYPositions[i] += m_randSpeeds[i] * deltaTime;
            renderer->RenderTexture(m_rockSheets[i], m_rockSheets[i]->Update(ROCK_FALL, deltaTime),
                Rect(offsetsRock[i], m_rockYPositions[i], (offsetsRock[i] + spriteHeightRock), (m_rockYPositions[i] + spriteWidthRock * scaleRock)));
        }
    }

    //GUI fps
    std::string fps = "FPS: " + std::to_string(Timing::Instance().GetFPS());
    font->Write(renderer->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 100, 0 });

    std::string time = "Game Time: " + std::to_string(static_cast<int>(gameTime));
    font->Write(renderer->GetRenderer(), time.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });
    
    font->Write(renderer->GetRenderer(), m_autoSaveStatus.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 500, 0 });


    // Collision
    for (int i = 0; i < 10; i++)
    {
        if (m_warriorIsAlive[i])
        {
            for (int j = 0; j < 10; j++)
            {
                if (m_rockIsAlive[j])
                {
                    if (CheckCollision(m_warriorXPositions[i], offsets[i], m_warriorXPositions[i] + spriteWidth, offsets[i] + spriteHeight,
                        offsetsRock[j], m_rockYPositions[j], offsetsRock[j] + spriteWidthRock, m_rockYPositions[j] + spriteHeightRock))
                    {
                        // delete rock
                        m_rockIsAlive[j] = false;

                        // swap warrior animation to death
                        m_warriorDeathState[i] = true;

                    }
                }
            }
        }
    }

}

bool Level::Level2EndTriggered()
{
    for (int i = 0; i < 10; i++)
    {
        if (m_warriorXPositions[i] >= viewportEdge-spriteWidth || std::find(m_warriorIsAlive.begin(), m_warriorIsAlive.end(), true) == m_warriorIsAlive.end())
        {
            return true;
        }
    }
    return false;  // No warrior has crossed yet
}
