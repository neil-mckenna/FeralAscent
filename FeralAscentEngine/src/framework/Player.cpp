#include "framework/Player.h"
#include "framework/AssetManager.h"
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
        m_FrameDuration(0.1f),
        m_PlayerTexturePath(texturePath),
        m_Body{}

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

        // start animations
        m_TextureComponent.get()->LoadPlayerWalkingTextures();


    }

    void Player::LoadTextures(const std::string& prefix, int frameCount, std::vector<sf::Texture>& textures) {
        for (int i = 1; i <= frameCount; ++i) {
            sf::Texture texture;
            if (texture.loadFromFile(prefix + std::to_string(i) + ".png")) {
                textures.push_back(texture);
            }
        }
    }

    void Player::Update(float deltaTime) {
        //LOG("PLAYER UPDATING!");

        sf::Vector2f direction(0.0f, 0.0f);

        // Handle input for movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.0f;

        //LOG("Current Direction: %f %f", direction.x, direction.y);

        // Normalize direction (to ensure consistent speed)
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude > 0.0f) direction /= magnitude;

        // Apply the velocity to the PhysicsComponent
        if (m_PhysicsComponent) {
            m_PhysicsComponent->HandleMovement(direction, deltaTime);  // Pass direction to PhysicsComponent
        }

        // Get the current position from the PhysicsComponent
        sf::Vector2f physicsPosition = m_PhysicsComponent->GetPosition();

        // Sync the sprite's position with the physics body (convert meters to pixels if necessary)
        //LOG("POS X: %f, POSY: %f", physicsPosition.x, physicsPosition.y);
        m_TextureComponent.get()->GetSprite().setPosition(physicsPosition.x, physicsPosition.y);


        // Call the parent update
        Actor::Update(deltaTime);
    }

    void Player::Render(sf::RenderWindow& window) {

        Actor::Render(window);

    }



    Player::~Player() {

        if (m_Body) {
            b2World* world = m_Body->GetWorld();
            if (world) {
                world->DestroyBody(m_Body);
            }
            m_Body = nullptr; // Avoid dangling pointer
        }


    }

}
