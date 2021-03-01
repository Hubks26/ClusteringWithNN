#include "Features.h"

Features::Features(const std::vector<std::vector<float>>& positions, const std::vector<bool>& labels)
: m_positions(positions)
, m_labels(labels)
{
}

void Features::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle;
	circle.setRadius(3.f);
	sf::FloatRect rect = circle.getLocalBounds();
	circle.setOrigin({rect.width/2.f, rect.height/2.f});
	
	for (std::size_t i = 0; i < m_labels.size(); ++i)
	{
		circle.setPosition(m_positions[i][0]*target.getSize().x, m_positions[i][1]*target.getSize().y);
		
		if(m_labels[i])
			circle.setFillColor(sf::Color(255, 0, 0));
		else
			circle.setFillColor(sf::Color(0, 0, 255));
		
		target.draw(circle, states);
	}
}
