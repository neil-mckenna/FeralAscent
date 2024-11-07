#include "framework/Application.h"
#include "framework/player.h"
#include <iostream>

using namespace sf;
using namespace std;

const int GAMEWIDTH = 1024;
const int GAMEHEIGHT = 768;

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

	void Application::Update(float dt)
	{
		player->Update(dt);
	}

	void Application::Render()
	{
		m_Window.clear();
		player->Render(m_Window);

		m_Window.display();
	}

}