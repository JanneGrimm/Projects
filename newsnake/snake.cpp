#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // SDL initialisieren
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL konnte nicht initialisiert werden! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Erstellen eines Fensters
    SDL_Window* window = SDL_CreateWindow("SDL Fenster", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          800, 600, 
                                          SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Fenster konnte nicht erstellt werden! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Erstellen eines Renderers
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer konnte nicht erstellt werden! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Haupt-Ereignisschleife
    bool running = true;
    SDL_Event event;

    // Farbwerte
    SDL_Color militaryGreen = {107, 142, 35, 255};  // Militärgrün
    SDL_Color darkLineColor = {85, 110, 28, 255};   // Dunklere Farbe für die Linien
    SDL_Color darkBlue = {0, 0, 139, 255};          // Dunkelblau für das Quadrat
    int tileSize = 20;  // Größe der Karo-Flächen

    // Startposition des Quadrats (mittig auf dem Karomuster)
    int squareX = (800 / 2) / tileSize * tileSize;  // Berechnet die nächste "Karoposition" (auf das Karomuster angepasst)
    int squareY = (600 / 2) / tileSize * tileSize;  // Berechnet die nächste "Karoposition"
    SDL_Rect square = {squareX, squareY, tileSize, tileSize};  // Quadrat

    while (running) {
        while (SDL_PollEvent(&event)) {
            // Überprüfen, ob das Fenster geschlossen oder die Escape-Taste gedrückt wurde
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                // Bewegung mit W, A, S, D
                switch (event.key.keysym.sym) {
                    case SDLK_w: // Nach oben
                        if (squareY > 0)  // Überprüfen, ob das Quadrat sich innerhalb des Fensters bewegt
                            squareY -= tileSize;
                        break;
                    case SDLK_s: // Nach unten
                        if (squareY < 600 - tileSize)
                            squareY += tileSize;
                        break;
                    case SDLK_a: // Nach links
                        if (squareX > 0)
                            squareX -= tileSize;
                        break;
                    case SDLK_d: // Nach rechts
                        if (squareX < 800 - tileSize)
                            squareX += tileSize;
                        break;
                    case SDLK_ESCAPE: // Escape schließt das Programm
                        running = false;
                        break;
                }

                // Quadratposition aktualisieren
                square.x = squareX;
                square.y = squareY;
            }
        }

        // Hintergrund mit Militärgrün füllen
        SDL_SetRenderDrawColor(renderer, militaryGreen.r, militaryGreen.g, militaryGreen.b, militaryGreen.a);
        SDL_RenderClear(renderer);

        // Kariertes Muster durch Linien zeichnen (leicht dunkler als Militärgrün)
        SDL_SetRenderDrawColor(renderer, darkLineColor.r, darkLineColor.g, darkLineColor.b, darkLineColor.a);

        // Vertikale und horizontale Linien des Karomusters zeichnen
        for (int x = 0; x <= 800; x += tileSize) {
            SDL_RenderDrawLine(renderer, x, 0, x, 600);  // Vertikale Linie
        }
        for (int y = 0; y <= 600; y += tileSize) {
            SDL_RenderDrawLine(renderer, 0, y, 800, y);  // Horizontale Linie
        }

        // Dunkelblaues Quadrat zeichnen
        SDL_SetRenderDrawColor(renderer, darkBlue.r, darkBlue.g, darkBlue.b, darkBlue.a);
        SDL_RenderFillRect(renderer, &square);

        // Fenster rendern
        SDL_RenderPresent(renderer);
    }

    // Aufräumen
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
