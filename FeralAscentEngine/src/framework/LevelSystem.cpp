#include "framework/LevelSystem.h"
#include <fstream>
#include <stdexcept>

namespace fa {
    // Internal variables scoped within an anonymous namespace
    namespace {
        size_t _width = 0, _height = 0; // Level dimensions
        std::vector<TILE> _tiles;      // Tiles data
        constexpr float DEFAULT_TILE_SIZE = 32.0f; // Default tile size
    }

    void loadLevelFile(const std::string& path, float tileSize) {
        _tiles.clear();

        // Open the file
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open level file.");
        }

        std::string line;
        size_t y = 0;
        while (std::getline(file, line)) {
            for (size_t x = 0; x < line.size(); ++x) {
                TILE tile = EMPTY; // Default to empty tile
                switch (line[x]) {
                case 'w': tile = WALL; break;
                case 's': tile = START; break;
                case 'e': tile = END; break;
                case 'n': tile = ENEMY; break;
                default: break;
                }
                _tiles.push_back(tile);
            }
            y++;
        }

        if (y == 0 || _tiles.empty()) {
            throw std::runtime_error("Error: Level file is empty or invalid.");
        }

        _width = _tiles.size() / y; // Calculate width from the tile data
        _height = y;

        file.close();
    }

    size_t getWidth() {
        return _width;
    }

    size_t getHeight() {
        return _height;
    }

    TILE getTile(const sf::Vector2i& pos) {
        if (pos.x < 0 || pos.x >= static_cast<int>(_width) || pos.y < 0 || pos.y >= static_cast<int>(_height)) {
            throw std::out_of_range("Tile position out of bounds");
        }
        return _tiles[pos.y * _width + pos.x];
    }

    sf::Vector2f getTilePosition(const sf::Vector2i& pos) {
        return sf::Vector2f(pos.x * DEFAULT_TILE_SIZE, pos.y * DEFAULT_TILE_SIZE);
    }

    void render(sf::RenderWindow& window) {
        for (size_t y = 0; y < _height; ++y) {
            for (size_t x = 0; x < _width; ++x) {
                TILE tile = _tiles[y * _width + x];
                sf::RectangleShape shape(sf::Vector2f(DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE));
                shape.setPosition(getTilePosition(sf::Vector2i(x, y)));

                // Set color based on tile type
                switch (tile) {
                case WALL: shape.setFillColor(sf::Color::Green); break;
                case START: shape.setFillColor(sf::Color::Blue); break;
                case END: shape.setFillColor(sf::Color::Red); break;
                case ENEMY: shape.setFillColor(sf::Color::Yellow); break;
                default: shape.setFillColor(sf::Color::Transparent); break;
                }

                window.draw(shape);
            }
        }
    }
} // namespace fa
