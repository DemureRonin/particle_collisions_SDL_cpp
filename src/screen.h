#include <SDL2/SDL.h>

#include <memory>
#include <numeric>
#include <vector>

#include "particle.h"
#include "renderer.h"

class Screen
{
public:
    SDL_Event e;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(800, 640, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    void render(std::vector<Particle> particles)
    {
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (auto &particle : particles)
        {
            SDL_RenderFillCircle(renderer, particle.position.x, particle.position.y,
                                 particle.radius);
        }

        SDL_RenderPresent(renderer);
    }

   
    void clear() {}
};