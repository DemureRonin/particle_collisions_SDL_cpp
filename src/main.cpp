#include <iostream>

#include "screen.h"
void add_particle(std::vector<Particle> &vector, vec2 coords, float radius);
void handle_input(SDL_Event e, std::vector<Particle> &vector, float radius);
int main()
{
    Screen screen;
    bool running = true;
    const float defaultRadius = 3;
    std::vector<Particle> particles;

    add_particle(particles, vec2(500, 500), defaultRadius);

    Uint32 previousTime = SDL_GetTicks();
    float deltaTime = 0;

    while (running)
    {
        screen.render(particles);
        for (auto &particle1 : particles)
        {
             particle1.simulate(deltaTime, true, vec2(1, 1));
            // for (auto &particle2 : particles)
            // {
            //     if (particle1 != particle2)
            //     {
            //         //      if(distance)
            //     }
               
            // }
        }

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        handle_input(screen.e, particles, defaultRadius);
        SDL_Delay(16);
    }
    return 0;
}
void add_particle(std::vector<Particle> &vector, vec2 coords, float radius)
{
    std::unique_ptr<Particle> particle =
        std::make_unique<Particle>(coords, radius);
    vector.push_back(*particle);
    std::cout << vector.size() << std::endl;
}
void handle_input(SDL_Event e, std::vector<Particle> &vector, float radius)
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            SDL_Quit();
            exit(0);
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Left mouse button pressed at: (" << e.button.x << ", " << e.button.y << ")" << std::endl;
                add_particle(vector, vec2(e.button.x, e.button.y), radius);
            }
            else if (e.button.button == SDL_BUTTON_RIGHT)
            {
                std::cout << "Right mouse button pressed at: (" << e.button.x << ", " << e.button.y << ")" << std::endl;
            }
        }
    }
}