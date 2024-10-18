#include "snake.hpp"
#include <cstdlib>
#include <ctime>

// --- Snake Methoden ---
Snake::Snake(int startX, int startY) {
    body.push_back({startX, startY});
    direction = RIGHT;
}

void Snake::move() {
    Position newHead = body.front();
    switch (direction) {
        case UP:    newHead.y--; break;
        case DOWN:  newHead.y++; break;
        case LEFT:  newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }
    body.insert(body.begin(), newHead);
    body.pop_back();
}

void Snake::changeDirection(Direction newDirection) {
    direction = newDirection;
}

void Snake::grow() {
    body.push_back(body.back());
}

bool Snake::isCollidingWithItself() {
    const Position& head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i].x == head.x && body[i].y == head.y)
            return true;
    }
    return false;
}

const std::vector<Position>& Snake::getBody() const {
    return body;
}

// --- GameBoard Methoden ---
GameBoard::GameBoard(int w, int h) : width(w), height(h) {
    generateFruit();
}

void GameBoard::generateFruit() {
    fruit.x = rand() % width;
    fruit.y = rand() % height;
}

const Position& GameBoard::getFruit() const {
    return fruit;
}

int GameBoard::getWidth() const {
    return width;
}

int GameBoard::getHeight() const {
    return height;
}

// --- SnakeGame Methoden ---
SnakeGame::SnakeGame(int boardWidth, int boardHeight)
    : snake(boardWidth / 2, boardHeight / 2), board(boardWidth, boardHeight), gameOver(false) {

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, boardWidth * 20, boardHeight * 20, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SnakeGame::~SnakeGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SnakeGame::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameOver = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_w: snake.changeDirection(UP); break;
                case SDLK_s: snake.changeDirection(DOWN); break;
                case SDLK_a: snake.changeDirection(LEFT); break;
                case SDLK_d: snake.changeDirection(RIGHT); break;
            }
        }
    }
}

void SnakeGame::update() {
    snake.move();

    if (snake.getBody().front().x == board.getFruit().x &&
        snake.getBody().front().y == board.getFruit().y) {
        snake.grow();
        board.generateFruit();
    }

    if (snake.isCollidingWithItself()) {
        gameOver = true;
    }
}

void SnakeGame::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (const auto& segment : snake.getBody()) {
        SDL_Rect rect = { segment.x * 20, segment.y * 20, 20, 20 };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect fruitRect = { board.getFruit().x * 20, board.getFruit().y * 20, 20, 20 };
    SDL_RenderFillRect(renderer, &fruitRect);

    SDL_RenderPresent(renderer);
}

void SnakeGame::run() {
    while (!gameOver) {
        handleInput();
        update();
        render();
        SDL_Delay(100);
    }
}
