#include "Features.h"

Features::Features(unsigned int n)
{
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<float> dist(0.0,1.0);
	float x;
	float y;
	float u0_1;
	bool b;
	
	std::vector<std::vector<float>> positions;
	std::vector<bool> labels;
	
	for(std::size_t i = 0; i < n; ++i)
	{
		x = dist(generator);
		y = dist(generator);
		
		positions.push_back(std::vector<float>{x, y});
		
		u0_1 = dist(generator);
		if(u0_1 < 0.5)
			b = true;
		else
			b = false;
		
		labels.push_back(b);
	}
	
	m_positions = positions;
	m_labels = labels;
}

Features::Features(const std::vector<std::vector<float>>& positions, const std::vector<bool>& labels)
: m_positions(positions)
, m_labels(labels)
{
}

std::vector<std::vector<float>> Features::getInputs() const
{
	return(m_positions);
}

std::vector<std::vector<float>> Features::getOutputs() const
{
	std::vector<std::vector<float>> outputs;
	
	for(std::size_t i = 0; i < m_labels.size(); ++i)
	{
		if(m_labels[i])
			outputs.push_back(std::vector<float>{1.f});
		else
			outputs.push_back(std::vector<float>{0.f});
	}
	return(outputs);
}

void Features::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle;
	circle.setRadius(target.getSize().y/200.f);
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
