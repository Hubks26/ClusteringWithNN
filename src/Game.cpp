#include "Game.h"

const sf::Time Game::m_timePerFrame = sf::seconds(1.f/60.f);

Game::Game(Features feat, NeuralNetwork nn)
: m_window(sf::VideoMode(1000, 1000), "Neural Network", sf::Style::Fullscreen)
, m_nn(nn)
, m_field(Field(nn, feat))
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;
			update();
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			m_window.close();
	}
}

void Game::update()
{
	m_field.update();
}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_field);
	m_window.display();
}
