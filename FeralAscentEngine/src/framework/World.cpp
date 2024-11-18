#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

namespace fa
{
	World::World(Application* owningApp)
		: m_owningApp{ owningApp },
		m_BeginPlay{false},
		m_Actors{},
		m_pendingActors{}
	{
		LOG("World created");

	}

	void World::BeginPlayInternal()
	{

		if (!m_BeginPlay)
		{
			m_BeginPlay = true;
			BeginPlay();
		}

	}

	void World::UpdateInternal(float dt)
	{
		//LOG("Pending Actors size()  %d", m_pendingActors.size());
		for (shared<Actor> actor : m_pendingActors)
		{
			//LOG("Pending Actor added to Actors");
			m_Actors.push_back(actor);

			actor->BeginPlayInternal();
		}

		m_pendingActors.clear();


		for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
		{
			iter->get()->UpdateInternal(dt);
			++iter;

		}

		Update(dt);
	}

	void World::Render(RenderWindow& window)
	{
		for (auto& actor : m_Actors)
		{
			actor->Render(window);
		}


	}


	void World::BeginPlay()
	{
		LOG("Begin Play");
	}

	void World::Update(float dt)
	{
		//LOG("Updating at framerate %f", 1.f / dt);
		//LOG("Actors count %zu" , m_Actors.size());
	}

	Vector2u World::GetWindowSize() const
	{
		return m_owningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = m_Actors.erase(iter);
			}
			else
			{
				++iter;
			}
		}


	}

	World::~World()
	{

	}
}