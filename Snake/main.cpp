#include "snake.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    SnakeGame game(30, 20); // Board size: 30x20
    game.run();

    return 0;
}
