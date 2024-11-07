#include "framework/Application.h"
#include "framework/player.h"
#include "framework/LevelSystem.h"
#include <iostream>

using namespace sf;
using namespace std;

const int GAMEWIDTH = 1920;
const int GAMEHEIGHT = 1080;

Player* player;


namespace fa
{

	// Application constructor with default settings
	Application::Application() :
		m_Window{ VideoMode(GAMEWIDTH, GAMEHEIGHT), "FeralAscent" },
		m_TargetFrameRate{ 60.0f },
		m_TickClock{}
	{

	}

	void Application::Run()
	{
		m_TickClock.restart();
		float accumlatedTime = 0.f;
		float targetDeltaTime = 1.f / m_TargetFrameRate;

		// create a player object
		player = new Player();
		player->setPosition(Vector2f(GAMEWIDTH / 2, GAMEHEIGHT / 2));

		// load level with a specific size
		LoadLevel(GAMEWIDTH / 30);

		while (m_Window.isOpen())
		{
			Event windowEvent;
			while (m_Window.pollEvent(windowEvent))
			{
				// close the window
				if (windowEvent.type == Event::EventType::Closed)
				{
					m_Window.close();
				}
			}
			float frameDeltaTime = m_TickClock.restart().asSeconds();
			accumlatedTime += frameDeltaTime;
			while (accumlatedTime > targetDeltaTime)
			{
				accumlatedTime -= targetDeltaTime;
				Update(targetDeltaTime);
				Render();

			}
			//cout << "Updating at framerate: " << 1.f / frameDeltaTime << endl;

		}

	}

	void Application::LoadLevel(float tileSize = 100.f)
	{

		LevelSystem::loadLevelFile(
			"C:/Users/jakes/source/repos/FeralAscent/FeralAscent/assets/level_2.txt",
			tileSize
		);

		// Print the level to the console
		for (size_t y = 0; y < ls::getHeight(); ++y) {
			for (size_t x = 0; x < ls::getWidth(); ++x) {
				cout << ls::getTile({ x, y });
			}
			cout << endl;
		}
	}

	void Application::Update(float dt)
	{
		player->Update(dt);
	}

	void Application::Render()
	{
		m_Window.clear();
		player->Render(m_Window);

		ls::render(m_Window);

		m_Window.display();
	}



}