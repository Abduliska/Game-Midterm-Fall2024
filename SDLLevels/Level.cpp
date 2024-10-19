#include "Level.h"


float rectX1;
float rectX2;
float rectX3;
float rectX4;
float rectX5;
float rectX6;
float rectX7;
float rectX8;
float rectX9;

Level::Level(SpriteSheet* sheet, Renderer* renderer, TTFont* font)
    : rectX(0.0f), rectAsh(0.0f), scale(1.8f), spriteWidth(69), spriteHeight(44), currentFrame(0),
    sheet(sheet), renderer(renderer), font(font), autoSaved(false), m_autoSaveStatus("AutoSave:No"), autoSaveMsgTimer(0.0f), initializePosition(false), viewportEdge(1920)
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

void Level::InitializeWarriorSpeeds(float deltaTime)
{
    // Get the specific SpriteAnim instance for the EN_AN_RUN animation
    SpriteAnim* runAnimation = sheet->GetAnimation(EN_AN_RUN);
    SpriteAnim* runAnimation1 = sheet->GetAnimation(EN_AN_RUN1);
    SpriteAnim* runAnimation2 = sheet->GetAnimation(EN_AN_RUN2);
    SpriteAnim* runAnimation3 = sheet->GetAnimation(EN_AN_RUN3);
    SpriteAnim* runAnimation4 = sheet->GetAnimation(EN_AN_RUN4);
    SpriteAnim* runAnimation5 = sheet->GetAnimation(EN_AN_RUN5);
    SpriteAnim* runAnimation6 = sheet->GetAnimation(EN_AN_RUN6);
    SpriteAnim* runAnimation7 = sheet->GetAnimation(EN_AN_RUN7);
    SpriteAnim* runAnimation8 = sheet->GetAnimation(EN_AN_RUN8);
    SpriteAnim* runAnimation9 = sheet->GetAnimation(EN_AN_RUN9);

    float run = runAnimation->GetClipSpeed();
    //std::cout << "run:" << run;

    float run1 = runAnimation1->GetClipSpeed();
    //std::cout << "run1:" << run1;
    float run2 = runAnimation2->GetClipSpeed();
   // std::cout << "run2:" << run2;
    float run3 = runAnimation3->GetClipSpeed();
   // std::cout << "run3:" << run3;
    float run4 = runAnimation4->GetClipSpeed();
   // std::cout << "run4:" << run4;
    float run5 = runAnimation5->GetClipSpeed();
   //std::cout << "run5:" << run5;
    float run6 = runAnimation6->GetClipSpeed();
   // std::cout << "run6" << run6;
    float run7 = runAnimation7->GetClipSpeed();
   // std::cout << "run6" << run7;
    float run8 = runAnimation8->GetClipSpeed();
   // std::cout << "run6" << run8;
    float run9 = runAnimation9->GetClipSpeed();
   // std::cout << "run6" << run9;

    rectX += run / 10 + 100 * deltaTime;  //example movement logic
    rectX1 += run1 / 10 + 100 * deltaTime;
    rectX2 += run2 / 10 + 100 * deltaTime;
    rectX3 += run3 / 10 + 100 * deltaTime;
    rectX4 += run4 / 10 + 100 * deltaTime;
    rectX5 += run5 / 10 + 100 * deltaTime;
    rectX6 += run6 / 10 + 100 * deltaTime;
    rectX7 += run7 / 10 + 100 * deltaTime;
    rectX8 += run8 / 10 + 100 * deltaTime;
    rectX9 += run9 / 10 + 100 * deltaTime;
}
void Level::RunLevel1Logic(float deltaTime,float gameTime)
{
   // rectX += 100 * deltaTime;  //this variable is what makes the first warrior go REALLY fast, fix this before you submit
    //rectAsh += 200 * deltaTime;

    

    renderer->SetDrawColor(Color(128, 128, 128, 255));
    renderer->ClearScreen();

    InitializeWarriorSpeeds(deltaTime);
  

    // setting my warriors

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 10, (rectX + spriteWidth * scale), (10 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN1, deltaTime),
        Rect(rectX1, 110, (rectX1 + spriteWidth * scale), (110 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN2, deltaTime),
        Rect(rectX2, 210, (rectX2 + spriteWidth * scale), (210 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN3, deltaTime),
        Rect(rectX3, 310, (rectX3 + spriteWidth * scale), (310 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN4, deltaTime),
        Rect(rectX4, 410, (rectX4 + spriteWidth * scale), (410 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN5, deltaTime),
        Rect(rectX5, 510, (rectX5 + spriteWidth * scale), (510 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN6, deltaTime),
        Rect(rectX6, 610, (rectX6 + spriteWidth * scale), (610 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN7, deltaTime),
        Rect(rectX7, 710, (rectX7 + spriteWidth * scale), (710 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN8, deltaTime),
        Rect(rectX8, 810, (rectX8 + spriteWidth * scale), (810 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN9, deltaTime),
        Rect(rectX9, 910, (rectX9 + spriteWidth * scale), (910 + spriteHeight * scale)));
  /*  renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
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
        Rect(rectX, 810, (rectX + spriteWidth * scale), (810 + spriteHeight * scale)));*/
   
    

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
    
    return (rectX >= viewportEdge || rectX1 >= viewportEdge || rectX2 >= viewportEdge || rectX3 >= viewportEdge ||
        rectX4 >= viewportEdge || rectX5 >= viewportEdge || rectX6 >= viewportEdge || rectX7 >= viewportEdge ||
        rectX8 >= viewportEdge || rectX9 >= viewportEdge);
}

void Level::RunLevel2Logic(float deltaTime, float gameTime) 
{
    if (!initializePosition) {
        rectX = 0.0f;
        rectX1 = 0.0f;
        rectX2 = 0.0f;
        rectX3 = 0.0f;
        rectX4 = 0.0f;
        rectX5 = 0.0f;
        rectX6 = 0.0f;
        rectX7 = 0.0f;
        rectX8 = 0.0f;
        rectX9 = 0.0f;

        initializePosition = true;
    }

    renderer->SetDrawColor(Color(0, 128, 0, 255));
    renderer->ClearScreen();

    InitializeWarriorSpeeds(deltaTime);

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN, deltaTime),
        Rect(rectX, 10, (rectX + spriteWidth * scale), (10 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN1, deltaTime),
        Rect(rectX1, 110, (rectX1 + spriteWidth * scale), (110 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN2, deltaTime),
        Rect(rectX2, 210, (rectX2 + spriteWidth * scale), (210 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN3, deltaTime),
        Rect(rectX3, 310, (rectX3 + spriteWidth * scale), (310 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN4, deltaTime),
        Rect(rectX4, 410, (rectX4 + spriteWidth * scale), (410 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN5, deltaTime),
        Rect(rectX5, 510, (rectX5 + spriteWidth * scale), (510 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN6, deltaTime),
        Rect(rectX6, 610, (rectX6 + spriteWidth * scale), (610 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN7, deltaTime),
        Rect(rectX7, 710, (rectX7 + spriteWidth * scale), (710 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN8, deltaTime),
        Rect(rectX8, 810, (rectX8 + spriteWidth * scale), (810 + spriteHeight * scale)));

    renderer->RenderTexture(sheet, sheet->Update(EN_AN_RUN9, deltaTime),
        Rect(rectX9, 910, (rectX9 + spriteWidth * scale), (910 + spriteHeight * scale)));



    std::string fps = "FPS: " + std::to_string(Timing::Instance().GetFPS());
    font->Write(renderer->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 0, 0 });

    std::string time = "Game Time: " + std::to_string(static_cast<int>(gameTime));
    font->Write(renderer->GetRenderer(), time.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 100, 0 });


    font->Write(renderer->GetRenderer(), m_autoSaveStatus.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 300, 0 });
}

bool Level::Level2EndTriggered()
{
    return (rectX >= viewportEdge || rectX1 >= viewportEdge || rectX2 >= viewportEdge || rectX3 >= viewportEdge ||
        rectX4 >= viewportEdge || rectX5 >= viewportEdge || rectX6 >= viewportEdge || rectX7 >= viewportEdge ||
        rectX8 >= viewportEdge || rectX9 >= viewportEdge);
}