#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void spawnTetromino();
    void mergeTetromino();
    bool checkCollision(int dx, int dy, int rotation);
    void clearLines();
    bool checkWin();

    sf::RenderWindow window;
    sf::Clock dropClock;

    const int ROWS = 20;
    const int COLS = 10;
    const int BLOCK_SIZE = 30;
    const int GOAL_HEIGHT = 2;

    std::vector<std::vector<int>> board;
    Tetromino current;
    bool isRunning;
};
