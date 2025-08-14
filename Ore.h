#pragma once
#include <SDL.h>

class Ore {
    private:
        SDL_Rect rect;

    public:
        Ore(int x, int y, int w, int h);
        ~Ore() = default;

        void render(SDL_Renderer* renderer);
        bool isColliding(const SDL_Point& p) const;
};