#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "TTFont.h"
#include "Timing.h"
#include "Level.h"


GameController::GameController()
    : currentState(GameState::LEVEL1),gameTime(0.0f),autoSaved(false)
{
    m_sdlEvent = {};
}

GameController::~GameController()
{}


Timing* t = &Timing::Instance();
// I made this maybe relocate it later..
int RandomNumber(int min, int max)
{
    int random = (min + rand() % (max - min + 1));

    return random;
}
void GameController::RunGame()
{
    // bytes of memory for your assets to use.
    AssetController::Instance().Initialize(10000000);
    // create a renderer.
    Renderer* r = &Renderer::Instance();
    // renderer makes window.
    r->Initialize(1920, 1080);//DONT FORGET TO CHANGE THIS TO 1080x1920
    TTFont* font = new TTFont();
    font->Initialize(20);
    Point ws = r->GetWindowSize();


    SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
    SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
    SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
    SpriteSheet* sheetRock = SpriteSheet::Pool->GetResource();

    sheet->Load("../Assets/Textures/Warrior.tga");
    
    // this maps to our warrior tga file.
    sheet->SetSize(17, 6, 69, 44);

    // sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
    sheet->AddAnimation(EN_AN_RUN, 6, 7, 1.0f);
    Level* level1 = new Level(sheet, r, font);
    
    sheetRock->Load("../Assets/Textures/Rock.tga");
    sheetRock->SetSize(1, 4, 20, 19);
    sheetRock->AddAnimation(ROCK_FALL, 1, 3, 1.0f);
    Level* level2 = new Level(sheet, sheetRock, r, font);

    while (m_sdlEvent.type != SDL_QUIT)
    {
        t->Tick();
        gameTime += t->GetDeltaTime();
        SDL_PollEvent(&m_sdlEvent);


        switch (currentState)
        {
        case GameState::LEVEL1:
        {
            //So I pass GetDeltaTime() for frame consistency, gameTime is for the total time passed
            level1->RunLevel1Logic(t->GetDeltaTime(), gameTime);
            if (!autoSaved && gameTime >= 5.0f)
            {
                ofstream writeStream("level1.bin", ios::out | ios::binary);
                level1->Serialize(writeStream);
                autoSaved = true;
                level1->SetAutoSaveStatus("AutoSave:Yes");
                writeStream.close();



                Level* loadedLevel = new Level(sheet, r, font);
                ifstream readStream("level1.bin", ios::in | ios::binary);
                loadedLevel->Deserialize(readStream);
                readStream.close();
            }
            if (level1->Level2TransitionTriggered())
            {
                currentState = GameState::LEVEL2; // Change game state to Level 2
                level1->SetAutoSaveStatus("AutoSave:No");
                autoSaved = false;
                gameTime = 0.0f;
                std::cout << "transitioning to level2" << endl;
            }

            break;
        }
        case GameState::LEVEL2:

            level2->RunLevel2Logic(t->GetDeltaTime(), gameTime);
            if (!autoSaved && gameTime >= 5.0f)
            {
                ofstream writeStream("level2.bin", ios::out | ios::binary);
                level2->Serialize(writeStream);
                autoSaved = true;
                level2->SetAutoSaveStatus("AutoSave:Yes");
                writeStream.close();



                Level* loadedLevel = new Level(sheet, sheetRock, r, font);
                ifstream readStream("level2.bin", ios::in | ios::binary);
                loadedLevel->Deserialize(readStream);
                readStream.close();
            }

            if (level2->Level2EndTriggered())
            {
                SDL_Quit();
            }
            break;
        }

        SDL_RenderPresent(r->GetRenderer());
    }
    delete SpriteAnim::Pool;
    delete SpriteSheet::Pool;



    r->Shutdown();
}


