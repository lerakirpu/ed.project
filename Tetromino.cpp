#include "Tetromino.h"
#include <array>

Tetromino::Tetromino(TetrominoType type, const sf::Vector2f& position) 
    : type(type), position(position), rotation(0) {
    switch (type) {
        case TetrominoType::I: color = sf::Color::Cyan; break;
        case TetrominoType::O: color = sf::Color::Yellow; break;
        case TetrominoType::T: color = sf::Color::Magenta; break;
        case TetrominoType::L: color = sf::Color(255, 165, 0); break; // Orange
        case TetrominoType::J: color = sf::Color::Blue; break;
        case TetrominoType::S: color = sf::Color::Green; break;
        case TetrominoType::Z: color = sf::Color::Red; break;
    }
    updateBlocks();
}

void Tetromino::move(const sf::Vector2f& offset) {
    position += offset;
}

void Tetromino::rotate() {
    rotation = (rotation + 1) % 4;
    updateBlocks();
}

void Tetromino::draw(sf::RenderWindow& window) const {
    const float blockSize = 30.f;
    sf::RectangleShape block(sf::Vector2f(blockSize - 1, blockSize - 1));
    block.setFillColor(color);
    
    for (const auto& b : blocks) {
        block.setPosition(position.x + b.x * blockSize, position.y + b.y * blockSize);
        window.draw(block);
    }
}

const std::vector<sf::Vector2i>& Tetromino::getBlocks() const {
    return blocks;
}

sf::Vector2f Tetromino::getPosition() const {
    return position;
}

sf::Color Tetromino::getColor() const {
    return color;
}

void Tetromino::updateBlocks() {
    blocks.clear();
    
    // I, O, T, L, J, S, Z blocks definitions
    const std::array<std::vector<sf::Vector2i>, 7> shapes = {{
        { {0, -1}, {0, 0}, {0, 1}, {0, 2} },  // I
        { {0, 0}, {1, 0}, {0, 1}, {1, 1} },   // O
        { {-1, 0}, {0, 0}, {1, 0}, {0, 1} },  // T
        { {0, -1}, {0, 0}, {0, 1}, {1, 1} },  // L
        { {0, -1}, {0, 0}, {0, 1}, {-1, 1} }, // J
        { {0, 0}, {1, 0}, {-1, 1}, {0, 1} },  // S
        { {-1, 0}, {0, 0}, {0, 1}, {1, 1} }   // Z
    }};
    
    auto baseBlocks = shapes[static_cast<int>(type)];
    
    for (auto& block : baseBlocks) {
        // Apply rotation
        for (int i = 0; i < rotation; ++i) {
            int newX = -block.y;
            int newY = block.x;
            block.x = newX;
            block.y = newY;
        }
        blocks.push_back(block);
    }
}
