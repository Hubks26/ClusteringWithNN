#ifndef FEATURES_H
#define FEATURES_H

#include <SFML/Graphics.hpp>
#include <vector>

class Features : public sf::Drawable
{
public :
	
	Features(const std::vector<std::vector<float>>&, const std::vector<bool>&);
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	std::vector<std::vector<float>> m_positions;
	std::vector<bool> m_labels;
};

#endif // FEATURES_H
