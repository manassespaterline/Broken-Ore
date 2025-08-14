#include <iostream>
#include <SDL.h>
#include <Ore.h>

Ore::Ore(int x, int y, int w, int h){
    rect = {x, y, w, h};
}

void Ore::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 140, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Ore::isColliding(const SDL_Point& p) const{
    return SDL_PointInRect(&p, &rect);
}