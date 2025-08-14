#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>
#include "Ore.h"
#include <vector>

int main(){
    printf("Hello, World!");

    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Inicializa o SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_Log("SDL não foi inicializado! Erro SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Cria uma janela.
    window = SDL_CreateWindow("Broken Ore", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window){
        SDL_Log("Não foi possível inicializar a janela! Erro SDL: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Cria o renderizador.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        SDL_Log("Não foi possível inicializar o renderizador! Erro SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Desenha um retângulo.
    // SDL_Rect rect = {100, 100, 50, 50};


    std::vector<Ore> ores;

    int oreWidth = 20;
    int oreHeight = 20;
    int spacing = 5;

    int oresPerRow = 10;
    int oresPerCol = 20;

    int startX = 50;
    int startY = 100;

    for (int row = 0; row < oresPerRow; row++){
        for (int col = 0; col < oresPerCol; col++){
            int x = startX + col * (oreWidth + spacing);
            int y = startY + row * (oreHeight + spacing);
            ores.emplace_back(x, y, oreWidth, oreHeight);
        }
    }

    

    bool running = true;

    SDL_Event event;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }

            

            if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT){
                    SDL_Point mousePoint = { event.button.x, event.button.y};

                    // for (auto& ore : ores){
                    //     if (ore.isColliding(mousePoint)){
                    //         std::cout << "You've broken the ore!" << std::endl;

                    //         ores.erase(ore);
                    //     }
                    // }

                    for (auto it = ores.begin(); it != ores.end(); ){
                        if (it->isColliding(mousePoint)){
                            std::cout << "You've broken the ore! " << ores.size() << std::endl;
                            it = ores.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
            }

        }

        SDL_SetRenderDrawColor(renderer, 28, 28, 28, 255); // Red, Green, Blue, Alpha.
        SDL_RenderClear(renderer);

        // SDL_SetRenderDrawColor(renderer, 0, 0, 140, 255);
        // SDL_RenderFillRect(renderer, &rect);

        for (auto& ore : ores){
            ore.render(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}