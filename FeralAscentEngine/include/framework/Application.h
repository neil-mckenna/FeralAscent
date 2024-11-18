#pragma once
#include <SFML/Graphics.hpp>
#include <Box2d/box2d.h>
#include "framework/Core.h"

using namespace sf;
using namespace std;

namespace fa
{

	class World;
	class Application
	{
	public:
		Application(
			unsigned int windowWidth,
			unsigned int windowHeight,
			const std::string& title,
			sf::Uint32 style);

		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		Vector2u GetWindowSize() const
		{
			return m_Window.getSize();
		}

	protected:
		virtual void Update(float dt);


	private:
		RenderWindow m_Window;
		float m_TargetFrameRate;
		Clock m_TickClock;
		shared<World> m_currentWorld;

		Clock m_CleanCycleClock;
		float m_CleanCycleInterval;

		void UpdateInternal(float dt);

		void RenderInternal();
		virtual void Render();



	};

	template<typename WorldType>
	std::weak_ptr<WorldType> Application::LoadWorld()
	{
		LOG("Attempting to load world of type WorldType");

		shared<WorldType> newWorld{ new WorldType{this} };
		LOG("WorldType instance created");

		m_currentWorld = newWorld;
		LOG("m_currentWorld set");

		// call play after creation
		m_currentWorld->BeginPlayInternal();

		return newWorld;
	}



}