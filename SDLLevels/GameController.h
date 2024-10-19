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

	bool autoSaved;

private:
	SDL_Event m_sdlEvent;
	GameState currentState;
	float gameTime;

	


};



#endif //GAME_CONTROLLER_H
