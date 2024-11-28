#include "framework/Player.h"
#include "framework/World.h"
#include <framework/Actor.h>
#include <SFML/Window/Keyboard.hpp>
#include <cmath> // For std::sqrt
#include "framework/Utilities.h"

namespace fa {


    /**
     * @brief Constructs a `Player` instance with specified world, position, and texture path.
     *
     * @param owningWorld Pointer to the `World` that owns this player. Used to initialize physics and other game logic dependencies.
     * @param position The initial position of the player in the game world (in SFML coordinates).
     * @param texturePath The path to the player's texture, used for rendering the player's sprite.
     *
     * This constructor initializes the player by:
     * - Setting up the base actor with physics through the `Actor` constructor.
     * - Loading animations for walking (right and left directions).
     * - Setting the initial texture for the player sprite.
     * - Centering the sprite's origin for easier transformations.
     * - Initializing Box2D physics properties specific to the player.
     *
     * @note
     * The texture for walking animations is expected to follow a naming convention with an incremental numbering scheme.
     * For example:
     * - Right walk textures: `assets/PNG/player/walking_sprites/right_walk_0.png` to `right_walk_8.png`
     * - Left walk textures: `assets/PNG/player/walking_sprites/left_walk_0.png` to `left_walk_8.png`
     *
     * Ensure the `owningWorld` is not null and that the texture paths are valid to avoid runtime errors.
     */
    Player::Player(World* owningWorld, const sf::Vector2f& position, const string& texturePath) :
        Actor(owningWorld, position, texturePath),  // Inherit physics from Actor
        m_CurrentFrame(0),
        m_AnimationTimer(0.0f),
        m_FrameDuration(0.1f)


    {
        LOG("Player Constructor: owningWorld=%p, position=(%f, %f), texturePath=%s",
            owningWorld,
            position.x, position.y,
            texturePath.c_str());

        // Ensure owningWorld is valid
        if (!owningWorld) {
            LOG("Error: owningWorld is nullptr in Player constructor!");
        }


        // call the call actor component and set the image texture
        m_TextureComponent.get()->SetTexture("PNG/player/walking_sprites/right_walk_1.png");



        // Load walking textures for right and left animations
        //LoadTextures("PNG/player/walking_sprites/right_walk_", 9, m_RightWalkTextures);
        //LoadTextures("PNG/player/walking_sprites/left_walk_", 9, m_LeftWalkTextures);

        //// Set the initial texture
        //if (!m_RightWalkTextures.empty()) {
        //    m_Sprite.setTexture(m_RightWalkTextures[0]);
        //}

        //if(m_Sprite.getTexture())
        //{
        //    m_Sprite.setOrigin(m_Sprite.getTexture()->getSize().x / 2.f, m_Sprite.getTexture()->getSize().y / 2.f);
        //}

        // Initialize physics
        InitPhysics(owningWorld->GetB2World(), position);
    }

    void Player::LoadTextures(const std::string& prefix, int frameCount, std::vector<sf::Texture>& textures) {
        for (int i = 1; i <= frameCount; ++i) {
            sf::Texture texture;
            if (texture.loadFromFile(prefix + std::to_string(i) + ".png")) {
                textures.push_back(texture);
            }
        }
    }

    void Player::InitPhysics(b2World& world, const sf::Vector2f& position) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(PixelsToMeters(position.x), PixelsToMeters(position.y));
        m_Body = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(PixelsToMeters(32.0f), PixelsToMeters(32.0f)); // Half-width and half-height

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        m_Body->CreateFixture(&fixtureDef);
    }

    void Player::Update(float deltaTime) {
        sf::Vector2f direction(0.0f, 0.0f);

        // Detect movement input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction.x -= 1.0f;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction.x += 1.0f;

        }

        // Normalize direction
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude > 0.0f) direction /= magnitude;

        // Update Box2D velocity
        float speed = 5.0f; // Speed in meters per second
        b2Vec2 velocity(direction.x * speed, direction.y * speed);
        m_Body->SetLinearVelocity(velocity);

        // Handle animation updates
        m_AnimationTimer += deltaTime;
        if (m_AnimationTimer >= m_FrameDuration) {
            m_AnimationTimer -= m_FrameDuration;

            if (!m_RightWalkTextures.empty()) {
                m_CurrentFrame = (m_CurrentFrame + 1) % m_RightWalkTextures.size();
                m_Sprite.setTexture(m_RightWalkTextures[m_CurrentFrame]);
            }
            else if (!m_LeftWalkTextures.empty()) {
                m_CurrentFrame = (m_CurrentFrame + 1) % m_LeftWalkTextures.size();
                m_Sprite.setTexture(m_LeftWalkTextures[m_CurrentFrame]);
            }
        }

        // Update sprite position
        b2Vec2 pos = m_Body->GetPosition();
        m_Sprite.setPosition(MetersToPixels(pos.x), MetersToPixels(pos.y));
    }

    void Player::Render(sf::RenderWindow& window) {
        // Render the sprite
        window.draw(m_Sprite);
    }



    Player::~Player() {

        //if (m_Body) {
        //    b2World* world = m_Body->GetWorld();
        //    if (world) {
        //        world->DestroyBody(m_Body);
        //    }
        //    m_Body = nullptr; // Avoid dangling pointer
        //}


    }

}
