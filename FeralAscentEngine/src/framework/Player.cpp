#include "framework/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath> // For std::sqrt
#include "framework/Utilities.h"

namespace fa {

    Player::Player(b2World& world, const sf::Vector2f& position)
        : m_CurrentFrame(0), m_AnimationTimer(0.0f), m_FrameDuration(0.1f), m_IsMovingRight(false), m_IsMovingLeft(false) {

        // Load walking textures for right and left animations
        LoadTextures("assets/PNG/player/walking_sprites/right_walk_", 9, m_RightWalkTextures);
        LoadTextures("assets/PNG/player/walking_sprites/left_walk_", 9, m_LeftWalkTextures);

        // Set the initial texture
        if (!m_RightWalkTextures.empty()) {
            m_Sprite.setTexture(m_RightWalkTextures[0]);
        }

        if(m_Sprite.getTexture())
        {
            m_Sprite.setOrigin(m_Sprite.getTexture()->getSize().x / 2.f, m_Sprite.getTexture()->getSize().y / 2.f);
        }

        // Initialize physics
        InitPhysics(world, position);
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

        m_IsMovingRight = false;
        m_IsMovingLeft = false;

        // Detect movement input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction.x -= 1.0f;
            m_IsMovingLeft = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction.x += 1.0f;
            m_IsMovingRight = true;
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

            if (m_IsMovingRight && !m_RightWalkTextures.empty()) {
                m_CurrentFrame = (m_CurrentFrame + 1) % m_RightWalkTextures.size();
                m_Sprite.setTexture(m_RightWalkTextures[m_CurrentFrame]);
            }
            else if (m_IsMovingLeft && !m_LeftWalkTextures.empty()) {
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
        // Cleanup Box2D body if necessary
        if (m_Body) {
            m_Body->GetWorld()->DestroyBody(m_Body);
        }
    }
}
