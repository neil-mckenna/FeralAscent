#include "framework/Application.h"
#include <iostream>

using namespace sf;
using namespace std;

const int GAMEWIDTH = 1024;
const int GAMEHEIGHT = 768;


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

	}

	void Application::Render()
	{
		m_Window.clear();

		RectangleShape player{ Vector2f{20,100} };
		player.setFillColor(Color::Green);
		player.setOrigin(10, 50);
		player.setPosition(GAMEWIDTH / 2, GAMEHEIGHT - 75.0f);

		RectangleShape ground{ Vector2f(GAMEWIDTH, 20.0f) };
		ground.setFillColor(Color::Magenta);
		ground.setPosition(0, GAMEHEIGHT - 25.0f);


		m_Window.draw(ground);
		m_Window.draw(player);

		m_Window.display();
	}

}