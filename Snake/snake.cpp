#include <SDL2/SDL.h>
#include <iostream>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define FIELD_WIDTH 900
#define FIELD_HEIGHT 900
#define FIELD_X 50
#define FIELD_Y 50

//Fielddesign
#define GRID_SIZE 13

void drawGrid(SDL_Renderer* renderer, int gridSize){
    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);  // Hellgrau

    // Vertikale Linien zeichnen
    for (int x = 0; x <= WINDOW_WIDTH; x += gridSize) {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }

    // Horizontale Linien zeichnen
    for (int y = 0; y <= WINDOW_HEIGHT; y += gridSize) {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }
}



int main(int argc, char* argv[]) {
    // SDL initialisieren
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL konnte nicht initialisiert werden! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Fenster erstellen
    SDL_Window* window = SDL_CreateWindow("SDL Fenster", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 
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


    // Game Loop Variablen
    bool isRunning = true;  // Flag, um zu bestimmen, ob die Spielschleife läuft
    SDL_Event event;        // SDL Event Struktur, um Eingaben zu verarbeiten

    // Game Loop
    while (isRunning) {
        // 1. Ereignisverarbeitung (Input)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;  // Fenster geschlossen
            }

            // Weitere Eingabeverarbeitung (Tasten, Maus etc.) hier
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:  // Wenn die ESC-Taste gedrückt wird
                        isRunning = false;
                        break;
                    
                    // Weitere Tastenverarbeitung hier
                }
            }
        }
        // Hintergrundfarbe
        SDL_SetRenderDrawColor(renderer, 195, 176, 145, 255);
        SDL_RenderClear(renderer);
        // 2. Spielzustand aktualisieren (Update)
        // Hier wird die Logik aktualisiert, z.B. Spielobjekte bewegen oder Status updaten.
        SDL_Rect fieldRect = { FIELD_X, FIELD_Y, FIELD_WIDTH, FIELD_HEIGHT };
        SDL_SetRenderDrawColor(renderer, 195, 176, 145, 255);  // Grün für das Spielfeld
        SDL_RenderFillRect(renderer, &fieldRect);          // Spielfeld füllen
        drawGrid(renderer,  GRID_SIZE);
        
        // Spielfeldrand zeichnen (dunklerer Rand um das Spielfeld)
        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);  // Dunkleres Grün für den Rand
        SDL_RenderDrawRect(renderer, &fieldRect);          // Rand des Spielfelds

        SDL_RenderPresent(renderer);  // Gezeichneten Inhalt anzeigen

        // Optional: Frame Rate Control (damit das Spiel nicht zu schnell läuft)
        SDL_Delay(16);  // 16 ms Delay (ca. 60 FPS)
    }

    // Ressourcen freigeben
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
