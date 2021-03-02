#ifndef GAME_H
#define GAME_H

#include "Field.h"

class Game
{
public :
	
	Game(Features, NeuralNetwork);
	void run();
	
private :
	
	void processEvents();
	void update();
	void render();
	
private :
	
	sf::RenderWindow m_window;
	static const sf::Time m_timePerFrame;
	
	NeuralNetwork m_nn;
	Field m_field;
};

#endif //GAME_H
