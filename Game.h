#pragma once

#include "GameState.h"

class Game {
    private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock dtClock;
	double dt;

	std::stack<State*> states;
	
	// Functions
	void initWindow();
	void initStates();

    public:
	Game();
	~Game();
	void updateDt();
	void updateEvents();
	void endApplication();
	void run();
	void update();
	void render();
};
