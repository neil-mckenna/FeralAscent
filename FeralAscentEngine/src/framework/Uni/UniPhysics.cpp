#include "framework/Uni/UniPhysics.h"
#include "framework/Core.h"

namespace fa
{
	// Constructor
	UniPhysics::UniPhysics(b2World& world, float physicsScale)
		: m_world(&world), gameHeight{ 768 }, physics_scale_inv{ 1.f / physicsScale }
	{
		// Log to confirm initialization
		if (m_world == nullptr) {
			LOG("Error: m_world is null in UniPhysics constructor!");
		}
		else {
			LOG("UniPhysics initialized with valid world.");
		}
	}


	// Create a physics box using position and size (Vector2f)
	b2Body* UniPhysics::CreatePhysicsBox(b2World& world, const bool dynamic, const Vector2f& position, const Vector2f& size)
	{
		LOG("Creating physics box at position (%f, %f) with size (%f, %f).", position.x, position.y, size.x, size.y);

		b2BodyDef bodyDef;
		if (dynamic)
		{
			bodyDef.type = b2_dynamicBody;
			LOG("Box set to dynamic.");
		}
		else
		{
			bodyDef.type = b2_staticBody;
			LOG("Box set to static.");
		}
		bodyDef.position.Set(position.x / physicsScale, position.y / physicsScale);  // Convert to Box2D units

		b2Body* body = world.CreateBody(&bodyDef);

		if (body == nullptr) {
			LOG("Failed to create physics body!");
			return nullptr;
		}

		LOG("Physics body created.");

		// Create the box shape for physics
		b2PolygonShape boxShape;
		boxShape.SetAsBox(size.x / 2.0f / physicsScale, size.y / 2.0f / physicsScale);  // Box2D uses half-width and half-height

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		LOG("Fixture created with density 1.0 and friction 0.3.");

		return body;
	}

	//
	b2Body* UniPhysics::CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs)
	{
		LOG("Creating physics box for RectangleShape at position (%f, %f) with size (%f, %f).",
			rs.getPosition().x, rs.getPosition().y, rs.getSize().x, rs.getSize().y);

		b2BodyDef bodyDef;
		if (dynamic) {
			bodyDef.type = b2_dynamicBody;
			LOG("Box set to dynamic.");
		}
		else {
			bodyDef.type = b2_staticBody;
			LOG("Box set to static.");
		}
		bodyDef.position.Set(rs.getPosition().x / physicsScale, rs.getPosition().y / physicsScale);

		b2Body* body = world.CreateBody(&bodyDef);

		if (body == nullptr) {
			LOG("Failed to create physics body!");
			return nullptr;  // Return null if body creation failed
		}

		LOG("Created physics body at position (%f, %f)", rs.getPosition().x, rs.getPosition().y);

		// Create the box shape for physics
		b2PolygonShape boxShape;
		boxShape.SetAsBox(rs.getSize().x / 2.f / physicsScale, rs.getSize().y / 2.f / physicsScale);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		LOG("Fixture created with density 1.0 and friction 0.3.");

		// Check if the body is awake right after creation
		if (body->IsAwake()) {
			LOG("Body is awake after creation.");
		}
		else {
			LOG("Body is asleep after creation.");
		}

		return body;
	}

	Vector2f UniPhysics::BV2_TO_SV2(const b2Vec2& in)
	{
		LOG("Converting b2Vec2 (%f, %f) to Vector2f.", in.x, in.y);
		return Vector2f(in.x * physicsScale, (in.y * physicsScale));
	}

	b2Vec2 UniPhysics::SV2_TO_BV2(const Vector2f& in)
	{
		LOG("Converting Vector2f (%f, %f) to b2Vec2.", in.x, in.y);
		return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
	}

	Vector2f UniPhysics::Invert_Height(const Vector2f& in)
	{
		LOG("Inverting height for Vector2f (%f, %f).", in.x, in.y);
		return Vector2f(in.x, gameHeight - in.y);
	}


	// In UniPhysics::Step() method
	void UniPhysics::Step(float dt)
	{
		LOG("PHYSICS STEPPING!");

		if (m_world == nullptr) {
			LOG("Error: m_world is null!");
			return;
		}

		// Ensure that the world is not locked before stepping
		if (m_world->IsLocked()) {
			LOG("Error: Box2D world is locked during step!");
			return;
		}

		// Proceed with stepping the world
		m_world->Step(dt, 6, 2);  // Typically, 6 and 2 are velocity and position iterations
		LOG("Physics step completed for dt = %f.", dt);
	}



	// Destructor
	UniPhysics::~UniPhysics() {
		LOG("UniPhysics object destroyed.");
	}
}
