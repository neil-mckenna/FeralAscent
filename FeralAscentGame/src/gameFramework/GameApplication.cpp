#include "gameFramework/GameApplication.h"
#include "player/Player.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"

#include "config.h"

fa::Application* GetApplication()
{
	return new fa::GameApplication{};
}

namespace fa
{


	GameApplication::GameApplication()
		: Application{ 1024, 768, "Feral Ascent", Style::Titlebar | Style::Close }
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());

		LOG("GAME Application called");
		weak<World> newWorld = LoadWorld<World>();


		// make the world spawn it
		weak<Player> player = newWorld.lock()->SpawnActor<Player>(
			"PNG/player/playerShip1_blue.png"
		);

		player.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));


		counter = 0.f;

	}

	void GameApplication::Update(float dt)
	{
		counter += dt;

		//LOG("GAME APPlication updating counter: %f", counter);


		if (counter > 10.f)
		{

		}
	}


}