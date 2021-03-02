#include "Field.h"

Field::Field(NeuralNetwork nn, Features features)
: m_nn(nn)
, m_features(features)
, m_inputs(features.getInputs())
, m_outputs(features.getOutputs())
, m_res(65)
{
}

void Field::update()
{
	m_nn.train(m_inputs, m_outputs, 1);
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f((target.getSize().x+1.f)/m_res, (target.getSize().y+1.f)/m_res));

	float value;
	
	for (std::size_t i = 0; i < m_res; ++i)
	{
		for (std::size_t j = 0; j < m_res; ++j)
		{
			rectangle.setPosition((i*target.getSize().x+1.f)/m_res, (j*target.getSize().y+1.f)/m_res);
			value = m_nn.predict(float(i)/float(m_res), float(j)/float(m_res));
			rectangle.setFillColor(sf::Color(value*120, 0, (1-value)*120));
			target.draw(rectangle, states);
		}
	}
	target.draw(m_features, states);
}
