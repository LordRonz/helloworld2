#pragma once

#include "EndGame.h"
class State {
    protected:
	std::stack<State*>* states{};
	sf::RenderWindow* window{};
	std::map<std::string, sf::Texture> textures;
	bool end{};
	bool paused{};

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	sf::Clock keyTimer;
	float keyTimeMax;

	void initKeyTimer();
	bool getKeyTime();
	void pauseState();
	void unpauseState();

    public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();
	const bool& getEnd() const;
	void endState();
	virtual void updateMousePos();
	virtual void updateInput(const double& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void update(const double& dt) = 0;
};
