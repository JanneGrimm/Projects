#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <SDL2/SDL.h>
#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Position {
    int x, y;
};

class Snake {
private:
    std::vector<Position> body;
    Direction direction;
public:
    Snake(int startX, int startY);
    void move();
    void changeDirection(Direction newDirection);
    void grow();
    bool isCollidingWithItself();
    const std::vector<Position>& getBody() const;
};

class GameBoard {
private:
    int width, height;
    Position fruit;
public:
    GameBoard(int w, int h);
    void generateFruit();
    const Position& getFruit() const;
    int getWidth() const;
    int getHeight() const;
};

class SnakeGame {
private:
    Snake snake;
    GameBoard board;
    bool gameOver;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void handleInput();
    void update();
    void render();

public:
    SnakeGame(int boardWidth, int boardHeight);
    ~SnakeGame();
    void run();
};

#endif // SNAKEGAME_H
