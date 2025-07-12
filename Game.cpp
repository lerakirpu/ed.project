#include "Game.h"
#include <iostream>

// Конструктор класса Game
Game::Game() : window(sf::VideoMode(COLS * BLOCK_SIZE, ROWS * BLOCK_SIZE), "Tricky Tetris") {
    // Инициализация игрового поля (матрица ROWS x COLS, заполненная нулями)
    board = std::vector<std::vector<int>>(ROWS, std::vector<int>(COLS, 0));
    
    // Создание первой фигуры
    spawnTetromino();
    
    // Установка флага работы игры
    isRunning = true;
}

// Главный игровой цикл
void Game::run() {
    while (window.isOpen() && isRunning) {
        processEvents();  // Обработка ввода
        update();         // Обновление состояния игры
        render();         // Отрисовка
    }
}

// Обработка событий
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Закрытие окна
        if (event.type == sf::Event::Closed)
            window.close();

        // Обработка нажатий клавиш
        if (event.type == sf::Event::KeyPressed) {
            // Движение влево (проверка столкновений)
            if (event.key.code == sf::Keyboard::Left && !checkCollision(-1, 0, current.getRotation()))
                current.x--;
            
            // Движение вправо
            else if (event.key.code == sf::Keyboard::Right && !checkCollision(1, 0, current.getRotation()))
                current.x++;
            
            // Ускоренное падение вниз
            else if (event.key.code == sf::Keyboard::Down && !checkCollision(0, 1, current.getRotation()))
                current.y++;
            
            // Поворот фигуры
            else if (event.key.code == sf::Keyboard::Up) {
                current.rotate();
                // Если после поворота есть столкновение - откатываем поворот
                if (checkCollision(0, 0, current.getRotation()))
                    current.rotateBack();
            }
        }
    }
}

// Обновление игрового состояния
void Game::update() {
    // Проверка времени для автоматического падения (каждые 0.5 секунды)
    if (dropClock.getElapsedTime().asSeconds() > 0.5f) {
        if (!checkCollision(0, 1, current.getRotation())) {
            current.y++; 
        } else {
            mergeTetromino();
            clearLines();
            
            // Проверка условия победы
            if (checkWin()) {
                std::cout << "Победа! Достигнута цель по высоте!" << std::endl;
                isRunning = false; 
            }          
            // Создание новой фигуры
            spawnTetromino();
        }
        dropClock.restart(); 
    }
}

// Отрисовка игры
void Game::render() {
    window.clear(); 
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            if (board[y][x]) { 
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
                block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                block.setFillColor(sf::Color::Blue);  
                window.draw(block);
            }
        }
    }

    // Отрисовка текущей фигуры
    auto shape = current.getShape();
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j]) { 
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
                block.setPosition((current.x + j) * BLOCK_SIZE, (current.y + i) * BLOCK_SIZE);
                block.setFillColor(sf::Color::Green);  
                window.draw(block);
            }
        }
    }

    // Отрисовка целевой линии (красная полоса)
    sf::RectangleShape goalLine(sf::Vector2f(COLS * BLOCK_SIZE, 2));
    goalLine.setPosition(0, GOAL_HEIGHT * BLOCK_SIZE);
    goalLine.setFillColor(sf::Color::Red);
    window.draw(goalLine);

    window.display();
}

// Создание новой фигуры
void Game::spawnTetromino() {
    current = Tetromino();  
}

// Проверка столкновений
bool Game::checkCollision(int dx, int dy, int rotation) {
    auto shape = current.getShape(rotation);
    int newX = current.x + dx;
    int newY = current.y + dy;

    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j]) {
                int x = newX + j;
                int y = newY + i;
                // Проверка выхода за границы или пересечения с другими блоками
                if (x < 0 || x >= COLS || y >= ROWS || (y >= 0 && board[y][x]))
                    return true;  // Столкновение есть
            }
        }
    }
    return false; 
}

// Фиксация фигуры на поле
void Game::mergeTetromino() {
    auto shape = current.getShape();
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j]) {
                int x = current.x + j;
                int y = current.y + i;
                // Если координаты в пределах поля
                if (y >= 0 && y < ROWS && x >= 0 && x < COLS)
                    board[y][x] = 1;  // Помечаем клетку как занятую
            }
        }
    }
}

// Удаление заполненных линий
void Game::clearLines() {
    for (int y = ROWS - 1; y >= 0; y--) {
        for (int x = 0; x < COLS; ++x) {
            if (!board[y][x]) {
                full = false;
                break;
            }
        }
        if (full) {
            for (int row = y; row > 0; row--) {
                board[row] = board[row - 1];
            }
            board[0] = std::vector<int>(COLS, 0);
            y++; 
        }
    }
}

// Проверка достижение целевой высоты
bool Game::checkWin() {
    for (int y = 0; y < GOAL_HEIGHT; ++y) {
        for (int x = 0; x < COLS; ++x) {
            if (board[y][x]) return true;  
        }
    }
    return false;
}
