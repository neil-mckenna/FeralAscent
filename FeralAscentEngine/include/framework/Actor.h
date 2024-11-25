#pragma once

#include "framework/Object.h"
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>

using namespace std;
using namespace sf;

class b2Body;

namespace fa
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const string &texturePath = "");

		string m_ActorName = "";
		bool m_facingLeft = true;

		virtual void BeginPlay();
		void BeginPlayInternal();

		virtual void Update(float dt);
		void LogActorDetails();
		void UpdateInternal(float dt);

		void SetTexture(const string texturePath);

		void Render(RenderWindow &window);

		void SetActorLocation(const Vector2f& newLocation);
		void SetActorRotation(float newRot);

		Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		void AddActorLocationOffset(const Vector2f& offsetAmt);
		void AddActorLocationOffset(float rotOffsetAmt);

		Vector2f GetActorForwardDirection() const;
		Vector2f GetActorRightDirection() const;

		void RescaleActor(float scaleXAmt, float scaleYAmt);
		void FaceLeft();
		void FaceRight();

		Vector2u GetWindowSize() const;

		FloatRect GetActorGlobalBounds() const;

		// new functions
		void SetSpriteRotation(float newRot);
		float GetSpriteRotation() const;

		World* GetWorld() const { return m_owningWorld; }

		bool IsActorOutOfWindowBounds() const;

		virtual void Destroy() override;

		// destructor
		virtual ~Actor();

	protected:

	private:
		World* m_owningWorld;
		bool m_hasBeganPlay;


		float m_ActorRotation = 0.0f;
		Sprite m_Sprite;
		shared<Texture> m_Texture;

		void CenterPivot();

		bool m_dynamic;
		Vector2i m_position;
		b2Body* m_body;


	};




}