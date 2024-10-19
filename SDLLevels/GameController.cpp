#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "TTFont.h"
#include "Timing.h"
#include "Level.h"
#include "StandardIncludes.h"


GameController::GameController()
    : currentState(GameState::LEVEL1),gameTime(0.0f),autoSaved(false)
{

    m_sdlEvent = {};

    

    
}

GameController::~GameController()
{}


Timing* t = &Timing::Instance();
// I made this maybe relocate it later..
float RandomNumber(float min, float max)
{
    
    if (min > max) {
        std::swap(min, max);
    }

    // Generate a random float in the range [min, max)
    float random = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));

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

    sheet->Load("../Assets/Textures/Warrior.tga");
    // this maps to our warrior tga file.
    sheet->SetSize(17, 6, 69, 44);


    // makes ever random number random again
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator


    // sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
    sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
    sheet->AddAnimation(EN_AN_RUN, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN1, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN2, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN3, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN4, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN5, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN6, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN7, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN8, 6, 7, RandomNumber(4.8f, 6.0f));
    sheet->AddAnimation(EN_AN_RUN9, 6, 7, RandomNumber(4.8f, 6.0f));


    Level* level = new Level(sheet, r, font);
    
    // makes ever random number random again
    srand(static_cast<unsigned int>(time(0))); // Seeding the random number generator

    

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
           level->RunLevel1Logic(t->GetDeltaTime(),gameTime);   
           if (!autoSaved && gameTime >= 5.0f)
           {
               ofstream writeStream("level1.bin", ios::out | ios::binary);
               level->Serialize(writeStream);
               autoSaved = true;
               level->SetAutoSaveStatus("AutoSave:Yes");
               writeStream.close();               
               
               

               Level* loadedLevel = new Level(sheet, r, font);
               ifstream readStream("level1.bin", ios::in | ios::binary);
               loadedLevel->Deserialize(readStream);
               readStream.close();
           }
           if (level->Level2TransitionTriggered())
           {
               currentState = GameState::LEVEL2; // Change game state to Level 2
               level->SetAutoSaveStatus("AutoSave:No");
               autoSaved = false;
               gameTime = 0.0f;
               std::cout << "transitioning to level2" << endl;
           }
           
            break;
        }
        case GameState::LEVEL2:
            
            level->RunLevel2Logic(t->GetDeltaTime(), gameTime);
            if (!autoSaved && gameTime >= 5.0f)
            {
                ofstream writeStream("level2.bin", ios::out | ios::binary);
                level->Serialize(writeStream);
                autoSaved = true;
                level->SetAutoSaveStatus("AutoSave:Yes");
                writeStream.close();



                Level* loadedLevel = new Level(sheet, r, font);
                ifstream readStream("level2.bin", ios::in | ios::binary);
                loadedLevel->Deserialize(readStream);
                readStream.close();                
            }

            if (level->Level2EndTriggered())
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


