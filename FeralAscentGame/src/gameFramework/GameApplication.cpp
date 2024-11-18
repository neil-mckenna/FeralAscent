#include "gameFramework/GameApplication.h"
#include "player/Player.h"
#include <enemy/Enemy.h>
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/PhysicsSystem.h"

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

		if (auto world = newWorld.lock())
		{
			// spawn a player into the world with a specific sprite
			weak<Player> player_1 = newWorld.lock()->SpawnActor<Player>(
				//"PNG/player/playerShip1_blue.png"
				"PNG/Player/walking_sprites/right_walk_1.png"
			);

			player_1.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
			player_1.lock()->SetEnablePhysics(true);


			// spawn a enemy into the world with a specific sprite
			weak<Enemy> enemy_1 = newWorld.lock()->SpawnActor<Enemy>(
				"PNG/Player/walking_sprites/left_walk_1.png"
			);
			enemy_1.lock()->SetEnablePhysics(true);
			enemy_1.lock()->SetActorLocation(sf::Vector2f(780.f, 490.f));

		}
		else
		{
			LOG("Failed to load world.");
		}


		counter = 0.f;

	}

	void GameApplication::Update(float dt)
	{
		counter += dt;

		PhysicsSystem::Get().Step(dt);

		//LOG("GAME APPlication updating counter: %f", counter);


		if (counter > 10.f)
		{

		}
	}


}