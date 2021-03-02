#ifndef FIELD_H
#define FIELD_H

#include "NeuralNetwork.h"
#include "Features.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Field : public sf::Drawable
{
public :
	
	Field(NeuralNetwork, Features);
	
	void update();
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	NeuralNetwork m_nn;
	Features m_features;
	std::vector<std::vector<float>> m_inputs;
	std::vector<std::vector<float>> m_outputs;
	unsigned int m_res;
};

#endif // FIELD_H
