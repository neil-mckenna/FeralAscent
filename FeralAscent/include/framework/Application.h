#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace fa
{
	class Application
	{
	public:
		Application();
		void Run();

	private:
		RenderWindow m_Window;
		float m_TargetFrameRate;
		Clock m_TickClock;

		void Update(float dt);
		void Render();

	};


}
