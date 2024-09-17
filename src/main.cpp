#include <iostream>

#include "screen.h"
void add_particle(std::vector<Particle> &vector, vec2 coords, float radius, float hue);
void handle_input(SDL_Event e, std::vector<Particle> &vector, float radius, float &clickCount, bool &colorAscending);
int main(int argc, char **argv)
{
    Screen screen;
    bool running = true;
    const float defaultRadius = 5;
    std::vector<Particle> particles;
    Uint32 previousTime = SDL_GetTicks();
    float deltaTime = 0;
    float clickCount = 0;
    bool colorAscending = true;
    while (running)
    {
        handle_input(screen.e, particles, defaultRadius, clickCount, colorAscending);

        for (auto &p1 : particles)
        {
            int screenWidth, screenHeight;
            SDL_GetWindowSize(screen.window, &screenWidth, &screenHeight);
            p1.simulate(deltaTime);
            p1.handleBoundsCollisions(screenWidth, screenHeight);
            p1.handleParticleCollisions(particles);
        }
        screen.render(particles);

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        SDL_Delay(16);
    }
    return 0;
}
void add_particle(std::vector<Particle> &vector, vec2 coords, float radius, float hue)
{
    vector.emplace_back(coords, radius, hue);

    std::cout << vector.size() << std::endl;
}
void handle_input(SDL_Event e, std::vector<Particle> &vector, float radius, float &clickCount, bool &colorAscending)
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
                add_particle(vector, vec2(e.button.x, e.button.y), radius, clickCount);
                float increment = 10;
                if (clickCount > 360)
                {
                    colorAscending = false;
                }
                else if (clickCount < 0)
                {
                    colorAscending = true;
                }
                clickCount = colorAscending ? clickCount + increment : clickCount - increment;
            }
            else if (e.button.button == SDL_BUTTON_RIGHT)
            {
                std::cout << "Right mouse button pressed at: (" << e.button.x << ", " << e.button.y << ")" << std::endl;
            }
        }
    }
}
