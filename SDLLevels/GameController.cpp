#include "GameController.h"
#include "Renderer.h"

GameController::GameController()
    : currentState(GameState::LEVEL1) 
{
    m_sdlEvent = {}; 
}

GameController::~GameController()
{}

void GameController::RunGame()
{
    Renderer* renderer = &Renderer::Instance(); 
    renderer->Initialize(800, 600);//DONT FORGET TO CHANGE THIS TO 1080x1920

    while (m_sdlEvent.type != SDL_QUIT)
    {
        SDL_PollEvent(&m_sdlEvent); 

        
        switch (currentState)
        {
        case GameState::LEVEL1:
            UpdateLvl1(); 
            break;

        case GameState::LEVEL2:
            
            break;
        }

        SDL_RenderPresent(renderer->GetRenderer()); 
    }

    renderer->Shutdown(); 
}

void GameController::UpdateLvl1()
{
    Renderer* renderer = &Renderer::Instance(); 

    
    renderer->SetDrawColor(Color(128, 128, 128, 255));
    renderer->ClearScreen();  

    
}
