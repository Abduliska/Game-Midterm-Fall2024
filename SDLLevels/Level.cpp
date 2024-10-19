#include "Level.h"


Level::Level(SpriteSheet* sheet, Renderer* renderer, TTFont* font)
    : rectX(0.0f), rectAsh(0.0f), scale(1.8f), spriteWidth(69), spriteHeight(44), currentFrame(0),
    sheet(sheet), renderer(renderer), font(font), autoSaved(false), m_autoSaveStatus("AutoSave:No"), autoSaveMsgTimer(0.0f)
{
}


Level::~Level() {}


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
void Level::RunLevel1Logic(float deltaTime,float gameTime)
{
    rectX += 100 * deltaTime;  
    rectAsh += 200 * deltaTime;

    

    renderer->SetDrawColor(Color(128, 128, 128, 255));
    renderer->ClearScreen();

    // setting my warriors
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 10, (rectX + spriteWidth * scale), (10 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectAsh, 110, (rectAsh + spriteWidth * scale), (110 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 210, (rectX + spriteWidth * scale), (210 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 210, (rectX + spriteWidth * scale), (210 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 310, (rectX + spriteWidth * scale), (310 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 410, (rectX + spriteWidth * scale), (410 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 510, (rectX + spriteWidth * scale), (510 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 610, (rectX + spriteWidth * scale), (610 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 710, (rectX + spriteWidth * scale), (710 + spriteHeight * scale)));
    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 810, (rectX + spriteWidth * scale), (810 + spriteHeight * scale)));
   
    

    //GUI fps
    std::string fps = "FPS: " + std::to_string(Timing::Instance().GetFPS());
    font->Write(renderer->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 0, 0 });

    std::string time = "Game Time: " + std::to_string(static_cast<int>(gameTime));
    font->Write(renderer->GetRenderer(), time.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 100, 0 });

    
    font->Write(renderer->GetRenderer(), m_autoSaveStatus.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 300, 0 });

    
    //std::cout << "Delta Time: " << deltaTime << std::endl;

   
}

bool Level::Level2TransitionTriggered()
{
    
    return (rectX >= 1440);
}

void Level::RunLevel2Logic(float deltaTime, float gameTime) 
{
    renderer->SetDrawColor(Color(0, 128, 0, 255));
    renderer->ClearScreen();

    std::string fps = "FPS: " + std::to_string(Timing::Instance().GetFPS());
    font->Write(renderer->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 0, 0 });

    std::string time = "Game Time: " + std::to_string(static_cast<int>(gameTime));
    font->Write(renderer->GetRenderer(), time.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 100, 0 });


    font->Write(renderer->GetRenderer(), m_autoSaveStatus.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 300, 0 });
}
