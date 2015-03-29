#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_ 1

#include <vector>
#include "Screen.h"
#include "../Game.h"
#include "../entities/Player.h" //TODO testing
#include "../entities/SolidBlock.h" //TODO testing

class GameScreen : public Screen
{
public:
	GameScreen(Game &game);
	
	void update(float dt);
	void render(sf::RenderWindow &window);
private:
    std::unique_ptr<Player> m_player_test; //TODO testing
    std::vector<std::unique_ptr<SolidBlock>> m_test_blocks; //TODO testing
	void handle_input();
};

#endif
