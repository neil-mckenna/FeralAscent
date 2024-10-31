#include "framework/Application.h"
#include <iostream>

using namespace sf;
using namespace std;

namespace fa
{


	// Application constructor with default settings
	Application::Application() :
		m_Window{ VideoMode(768, 1024), "FeralAscentGame" },
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
	}

}