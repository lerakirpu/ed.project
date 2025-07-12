#include "Renderer.h"
#include <iostream>

// Конструктор принимает ссылку на окно, размер блока и размеры сетки
Renderer::Renderer(sf::RenderWindow& window, float blockSize, int gridWidth, int gridHeight)
    : window(window),        // Инициализация ссылки на окно
      blockSize(blockSize), // Размер одного блока
      gridWidth(gridWidth), // Ширина игровой сетки (в блоках)
      gridHeight(gridHeight) // Высота игровой сетки (в блоках)
{
    initFont(); 
}

// Инициализация шрифта для текста
void Renderer::initFont() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl; 
    }
}

// Отрисовка игровой сетки
void Renderer::drawGrid(const std::vector<std::vector<sf::Color>>& grid) {
    // Создание прямоугольника для отрисовки блоков
    sf::RectangleShape block(sf::Vector2f(blockSize - 1, blockSize - 1)); 
    
    // Двойной цикл по всем клеткам сетки
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y] != sf::Color::Transparent) {
                block.setPosition(x * blockSize, y * blockSize); // Позиция блока
                block.setFillColor(grid[x][y]);                  // Цвет блока
                window.draw(block);                              // Отрисовка блока
            }
        }
    }
}

// Отрисовка текущей тетромино
void Renderer::drawTetromino(const Tetromino& tetromino) {
    tetromino.draw(window);
}

void Renderer::drawTargetLine(int targetHeight) {
    sf::RectangleShape line(sf::Vector2f(gridWidth * blockSize, 2.f)); // Ширина во весь экран
    line.setPosition(0, targetHeight * blockSize); // Позиция по Y в соответствии с целевой высотой
    line.setFillColor(sf::Color::Red);             // Красный цвет для заметности
    window.draw(line);                             // Отрисовка линии
}

// Отрисовка экрана "Game Over"
void Renderer::drawGameOver() {
    sf::Text text;
    text.setFont(font);                     // Установка шрифта
    text.setString("Game Over!");           // Текст
    text.setCharacterSize(50);              // Размер текста
    text.setFillColor(sf::Color::White);    // Белый цвет
    text.setStyle(sf::Text::Bold);          // Жирный стиль
    
    // Центрирование текста
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                 textRect.top + textRect.height/2.0f);
    text.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f);
    
    window.draw(text);      // Отрисовка текста
    window.display();       // Обновление экрана
    sf::sleep(sf::seconds(2)); 
}

// Отрисовка экрана победы
void Renderer::drawWin() {
    sf::Text text;
    text.setFont(font);                     // Установка шрифта
    text.setString("You Win!");             // Текст
    text.setCharacterSize(50);              // Размер текста
    text.setFillColor(sf::Color::Green);    // Зеленый цвет для победы
    text.setStyle(sf::Text::Bold);          // Жирный стиль
    
    // Центрирование текста
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                 textRect.top + textRect.height/2.0f);
    text.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f);
    
    window.draw(text);      // Отрисовка текста
    window.display();       // Обновление экрана
    sf::sleep(sf::seconds(2)); 
}
