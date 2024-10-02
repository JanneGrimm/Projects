#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // SDL initialisieren
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL konnte nicht initialisiert werden! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Fenster erstellen
    SDL_Window* window = SDL_CreateWindow("SDL Fenster", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          800, 600, 
                                          SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Fenster konnte nicht erstellt werden! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Renderer erstellen
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer konnte nicht erstellt werden! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Fensterfarbe setzen (hier: blau)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Renderer leeren (mit gesetzter Farbe)
    SDL_RenderClear(renderer);

    // Renderer anzeigen
    SDL_RenderPresent(renderer);

    // Warten, damit das Fenster sichtbar bleibt
    SDL_Delay(5000);  // 5 Sekunden warten

    // Ressourcen freigeben
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
