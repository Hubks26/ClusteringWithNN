#ifndef FIELD_H
#define FIELD_H

#include "NeuralNetwork.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Field : public sf::Drawable
{
public :
	
	Field(NeuralNetwork);
	
	void update();
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	NeuralNetwork m_nn;
	unsigned int m_res;
};

#endif // FIELD_H
