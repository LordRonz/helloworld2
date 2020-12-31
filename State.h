#pragma once

#include "BaseDeck.h"
class State {
    protected:
	std::stack<State*>* states{};
	sf::RenderWindow* window{};
	std::map<std::string, sf::Texture> textures;
	bool end{};

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	virtual void initVariables() = 0;

    public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();
	const bool& getEnd() const;
	virtual void endState() = 0;
	virtual void checkEnd();
	virtual void updateMousePos();
	virtual void updateInput(const double& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
	virtual void update(const double& dt) = 0;
};
