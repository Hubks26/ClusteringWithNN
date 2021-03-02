#ifndef FEATURES_H
#define FEATURES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>

class Features : public sf::Drawable
{
public :
	
	Features(unsigned int);
	Features(const std::vector<std::vector<float>>&, const std::vector<bool>&);
	
	std::vector<std::vector<float>> getInputs() const;
	std::vector<std::vector<float>> getOutputs() const;
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	std::vector<std::vector<float>> m_positions;
	std::vector<bool> m_labels;
};

#endif // FEATURES_H
