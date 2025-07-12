#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tetromino.h"

class Renderer {
public:
    Renderer(sf::RenderWindow& window, float blockSize, int gridWidth, int gridHeight);
    
    void drawGrid(const std::vector<std::vector<sf::Color>>& grid);
    void drawTetromino(const Tetromino& tetromino);
    void drawTargetLine(int targetHeight);
    void drawGameOver();
    void drawWin();
    
private:
    sf::RenderWindow& window;
    float blockSize;
    int gridWidth;
    int gridHeight;
    
    sf::Font font;
    
    void initFont();
};
