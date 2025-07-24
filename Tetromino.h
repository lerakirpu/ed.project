#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class TetrominoType { I, O, T, L, J, S, Z };

class Tetromino {
public:
    Tetromino(TetrominoType type, const sf::Vector2f& position);
    
    void move(const sf::Vector2f& offset);
    void rotate();
    void draw(sf::RenderWindow& window) const;
    
    const std::vector<sf::Vector2i>& getBlocks() const;
    sf::Vector2f getPosition() const;
    sf::Color getColor() const;
    
private:
    TetrominoType type;
    sf::Vector2f position;
    int rotation;
    sf::Color color;
    
    std::vector<sf::Vector2i> blocks;
    void updateBlocks();
};
