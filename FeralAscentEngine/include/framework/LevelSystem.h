#ifndef LEVEL_SYSTEM_HPP
#define LEVEL_SYSTEM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * Namespace for the level system functionality.
 * Handles loading, managing, and rendering levels in the game.
 */
namespace fa {

    // Enum for different tile types
    enum TILE {
        WALL,   // Green
        START,  // Blue
        END,    // Red
        ENEMY,  // Yellow
        EMPTY   // Transparent
    };

    /**
     * Loads a level from a specified file.
     * @param path Path to the level file.
     * @param tileSize Size of each tile in pixels (default specified in implementation).
     */
    void loadLevelFile(const std::string& path, float tileSize);

    /**
     * Gets the width of the level in tiles.
     * @return The number of tiles in the horizontal dimension.
     */
    size_t getWidth();

    /**
     * Gets the height of the level in tiles.
     * @return The number of tiles in the vertical dimension.
     */
    size_t getHeight();

    /**
     * Retrieves the tile type at a specific position in the grid.
     * @param pos Tile coordinates (x, y).
     * @return The type of the tile at the specified position.
     * @throws std::out_of_range if the position is out of bounds.
     */
    TILE getTile(const sf::Vector2i& pos);

    /**
     * Converts a tile's grid position to its world position.
     * @param pos Tile coordinates (x, y).
     * @return The world position as an SFML vector.
     */
    sf::Vector2f getTilePosition(const sf::Vector2i& pos);

    /**
     * Renders the level to the specified SFML render window.
     * @param window The SFML render window to draw the level on.
     */
    void render(sf::RenderWindow& window);

} // namespace fa

#endif // LEVEL_SYSTEM_HPP
