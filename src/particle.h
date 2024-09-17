#include <SDL2/SDL.h>
#include <math.h>

#include "structs.h"

class Particle
{
public:
    Particle(vec2 coord, float radius, float hue) : position(coord), radius(radius), hue(hue) {}
    const vec2 gravity = vec2(0, 9.81);
    vec2 position = vec2(0, 0);
    vec2 velocity = vec2(10, 10);
    float radius;
    float mass = 1;
    float restitution = .6f;
    float simulationSpeed = 30;

    float hue;
    struct color color = color.from_HSL(hue, 100, 100);

    void simulate(float deltaTime)
    {
        vec2 acceleration = gravity * mass;
        velocity = velocity + acceleration * deltaTime;
        position = position + velocity * deltaTime * simulationSpeed;
    }
    void handleParticleCollisions(std::vector<Particle> &particles)
    {
        for (auto &p2 : particles)
        {
            float minDistance = p2.radius + this->radius;
            float distance = this->position.distanceTo(p2.position);
            if (&p2 != this && distance < minDistance)
            {
                vec2 normal = (p2.position - this->position).normalize();
                vec2 relativeVelocity = p2.velocity - this->velocity;
                vec2 impulse = normal * (2 * relativeVelocity.dot(normal) / 2);
                this->velocity += impulse * restitution;
                p2.velocity -= impulse * p2.restitution;

                vec2 repulsion = normal * (minDistance - distance);
                this->position -= repulsion;
                p2.position += repulsion;
            }
        }
    }
    void handleBoundsCollisions(int screenWidth, int screenHeight)
    {
        if (position.y + radius >= screenHeight)
        {
            position.y = screenHeight - radius;
            velocity.y = -velocity.y * restitution;
        }
        if (position.y - radius <= 0)
        {
            position.y = 0 + radius;
            velocity.y = -velocity.y * restitution;
        }
        if (position.x - radius <= 0)
        {
            velocity.x = -velocity.x * restitution;
            position.x = 0 + radius;
        }
        if (position.x + radius >= screenWidth)
        {
            velocity.x = -velocity.x * restitution;
            position.x = screenWidth - radius;
        }
    }
    bool operator==(const Particle &other) const
    {
        return (position.x == other.position.x) && (position.y == other.position.y);
    }

    bool operator!=(const Particle &other) const
    {
        return !(*this == other);
    }
};