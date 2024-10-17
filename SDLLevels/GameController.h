#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"


enum GameState
{
	LEVEL1,
	LEVEL2

};
class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController();

	void RunGame();

private:
	SDL_Event m_sdlEvent;
	GameState currentState;

	void UpdateLvl1();


};



#endif //GAME_CONTROLLER_H
