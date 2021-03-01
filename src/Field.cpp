#include "Field.h"

Field::Field(NeuralNetwork nn)
: m_nn(nn)
, m_res(100)
{
}

void Field::update()
{
	std::vector<std::vector<float>> inputs{
			std::vector<float>{0.2, 0.4},
			std::vector<float>{0.1, 0.7},
			std::vector<float>{0.4, 0.1},
			std::vector<float>{0.9, 0.3},
			std::vector<float>{0.8, 0.6},
			std::vector<float>{1., 0.f},
			std::vector<float>{0.f, 1.f},
			std::vector<float>{0.6, 0.1},
			std::vector<float>{0.6, 0.2},
			std::vector<float>{0.2, 0.2},
			std::vector<float>{0.7, 0.5},
			std::vector<float>{0.3, 0.6},
			std::vector<float>{0.4, 0.4},
			std::vector<float>{0.5, 0.4},
			std::vector<float>{0.6, 0.9},
			std::vector<float>{0.5, 0.8},
			std::vector<float>{0.3, 0.9}
		};
	
	std::vector<std::vector<float>> outputs{
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{1.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f},
			std::vector<float>{0.f}
		};
		
	m_nn.train(inputs, outputs, 1);
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle;
	circle.setRadius(4.f);
	sf::FloatRect rect = circle.getLocalBounds();
	circle.setOrigin({rect.width/2.f, rect.height/2.f});
	float value;
	
	for (std::size_t i = 0; i < m_res; ++i)
	{
		for (std::size_t j = 0; j < m_res; ++j)
		{
			circle.setPosition(i*target.getSize().x/m_res, j*target.getSize().y/m_res);
			value = m_nn.predict(float(i)/float(m_res), float(j)/float(m_res));
			circle.setFillColor(sf::Color(value*200, value*200, value*200));
			target.draw(circle, states);
		}
	}
}
