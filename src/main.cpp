#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>

using namespace sf;
using namespace std;

#pragma region Globals_&_Constants

const int gameHeight = 468;
const int gameWidth = 768;

std::vector<b2Body*> bodies;
std::vector<RectangleShape*> sprites;

b2World* world;

#pragma endregion

#pragma region Physics_Functions

// 1 sfml unit = 30 physics units
const float physics_scale = 30.0f;
// inverse of physics_scale, useful for calculations
const float physics_scale_inv = 1.0f / physics_scale;
// Magic numbers for accuracy of physics simulation
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

//Convert from b2Vec2 to a Vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in) {
    return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}

//Convert from Vector2f to a b2Vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
    return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}

//Convert from screenspace.y to physics.y (as they are the other way around)
inline const Vector2f invert_height(const Vector2f& in) {
    return Vector2f(in.x, gameHeight - in.y);
}

//Create a Box2D body with a box fixture
b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const Vector2f& position, const Vector2f& size) {
    b2BodyDef BodyDef;
    //Is Dynamic(moving), or static(Stationary)
    BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
    BodyDef.position = sv2_to_bv2(position);
    //Create the body
    b2Body* body = World.CreateBody(&BodyDef);

    //Create the fixture shape
    b2PolygonShape Shape;
    Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    b2FixtureDef FixtureDef;
    //Fixture properties
    FixtureDef.density = dynamic ? 10.f : 0.f;
    FixtureDef.friction = dynamic ? 0.8f : 1.f;
    FixtureDef.restitution = 1.0;
    FixtureDef.shape = &Shape;
    //Add to body
    body->CreateFixture(&FixtureDef);
    return body;
}

// Create a Box2d body with a box fixture, from a sfml::RectangleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs) {
    return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}
#pragma endregion

#pragma region Init

void Init()
{
    const b2Vec2 gravity(0.0f, -10.0f);

    world = new b2World(gravity);

    // Create Boxes
    for (int i = 1; i < 11; ++i) {
        // Create SFML shapes for each box
        auto s = new RectangleShape();
        s->setPosition(Vector2f(i * (gameWidth / 12.f), gameHeight * .7f));
        s->setSize(Vector2f(50.0f, 50.0f));
        s->setOrigin(Vector2f(25.0f, 25.0f));
        s->setFillColor(Color::White);
        sprites.push_back(s);

        // Create a dynamic physics body for the box
        auto b = CreatePhysicsBox(*world, true, *s);
        // Give the box a spin
        b->ApplyAngularImpulse(5.0f, true);
        bodies.push_back(b);
    }


    // Wall Dimensions
    Vector2f walls[] = {
        // Top
        Vector2f(gameWidth * .5f, 5.f), Vector2f(gameWidth, 10.f),
        // Bottom
        Vector2f(gameWidth * .5f, gameHeight - 5.f), Vector2f(gameWidth, 10.f),
        // left
        Vector2f(5.f, gameHeight * .5f), Vector2f(10.f, gameHeight),
        // right
        Vector2f(gameWidth - 5.f, gameHeight * .5f), Vector2f(10.f, gameHeight)
    };

    // Build Walls
    for (int i = 0; i < 7; i += 2) {
        // Create SFML shapes for each wall
        auto s = new RectangleShape();
        s->setPosition(walls[i]);

        // set origin to center
        //s->setOrigin(Vector2f(25.0f, 25.0f));

        // set size and thickness of walls ?
        //s->setSize(Vector2f(walls[i].x, walls[i].y));
        s->setSize(Vector2f(walls[i].x * 1.0f, walls[i].y * 1.0f));

        // add back to sprites array for drawing
        sprites.push_back(s);

        // Create a static physics body for the wall
        CreatePhysicsBox(*world, false, *s);

    }

    // Create Boxes // world / static? / pos / size
    //auto b = CreatePhysicsBox(*world, false, Vector2f(walls[0].x, walls[0].y), Vector2f(10.0f, 10.0f));

    //bodies.push_back(b);
}
#pragma endregion

#pragma region Update

void Update() {
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();

    // Step Physics world by dt (non-fixed timestep) - THIS DOES ALL THE ACTUAL SIMULATION, DON'T FORGET THIS!
    world->Step(dt, velocityIterations, positionIterations);

    for (int i = 0; i < bodies.size(); ++i) {
        // Sync Sprites to physics position
        sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
        // Sync Sprites to physics Rotation
        sprites[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
    }
}
#pragma endregion

#pragma region Green_Circle
// Was test to show basic libraries working with a green screen
void ShowGreenCircle(sf::RenderWindow & window)
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // loop until closed
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
#pragma endregion

#pragma region Main

int main()
{
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Feral Ascent");

    //ShowGreenCircle(window);

    Init();

    // loop until closed
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // clear previous frame
        window.clear();

        // render then update

        // Draw the wall sprites
        for (const auto& sprite : sprites) {
            window.draw(*sprite);
        }

        // update frames
        Update();

        // Display the content of the window
        window.display();
    }

    return 0;
}

#pragma endregion


