#include "Game.h"

Game::Game(GameWindow* window): Controller(window)
{
	ResourceAllocator::allocateTexture(m_textures, "player", "res/textures/player.png");
	ResourceAllocator::allocateTexture(m_textures, "level", "res/textures/level.png");
	
	ResourceAllocator::allocateTileset(m_tilesets, "level", new Tileset(m_textures["level"], 3, 6, 16, 16, m_window->getTileSize(), m_window->getTileSize()));

	ResourceAllocator::allocateTileSystem(m_tilesystems, "level",  m_tilesets["level"]);
	m_tilesystems["level"]->registerTile(1, {1, 2, 3}, {1, 1, 1});
	m_tilesystems["level"]->registerTile(2, {1, 2, 3, 4, 5, 6}, {2, 2, 2, 2, 2, 2});
	m_tilesystems["level"]->registerTile(3, {1, 2, 3}, {3, 3, 3});
	
	m_view.reset(sf::FloatRect(0, 0, m_window->getSize().x - 2*m_window->getTileSize(), m_window->getSize().y - 2*m_window->getTileSize()));
	m_view.setViewport(sf::FloatRect(
							1/(float)m_window->getWidth(), 
							1/(float)m_window->getHeight(), 
							(m_window->getWidth()-2)/(float)m_window->getWidth(), 
							(m_window->getHeight()-2)/(float)m_window->getHeight()));
}

Game::~Game()
{
	cout << "** Deleting the Game Controller " << this << endl;
}

void Game::manageEvents()
{
	sf::Event event;
	while(m_window->pollEvent(event))
	{
		switch(event.type)
		{	
			default:
				break;
		}
		m_window->manageEvents(event);
	}
}

void Game::start()
{
	srand(time(NULL));

	//TMP CODE TESTING PURPOSES
	Tilemap testMap(m_tilesystems["level"], m_window->getWidth()-2, m_window->getHeight()-2);
	testMap.setMap({
					{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, },
					{3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 2, 2, 3, 3, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, },
					{3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, },
					{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, },
					});
	//END OF TMP CODE

	while(m_window->isOpen())
	{
		manageEvents();
	
		m_window->clear(sf::Color(100, 100, 100));
		
		m_window->setView(m_view);

		//TMP CODE TESTING PURPOSES
		testMap.draw(m_window);

		//END
	
		m_window->setView(m_window->getDefaultView());

		m_window->display();
	}
}
