#pragma once

#include "StatePlaying.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game {
    private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock dtClock;
	double dt;

	std::stack<State*> states;

	void initWindow();
	void initStates();

    public:
	Game();
	~Game();
	void updateDt();
	void updateEvents();
	void run();
	void update();
	void render();
};
