#include <SDL2/SDL.h>
#include <math.h>

#include "structs.h"

class Particle
{
public:
    Particle(vec2 coord, float radius) : position(coord), radius(radius) {}

    float radius;
    float mass = 1;
    const vec2 gravity = vec2(0, 9.81);
    vec2 position = vec2(0, 0);
    vec2 velocity = vec2(0, 0);
    bool freeFalling;
    float groundY = 700;
    float restitution = 0.7f;
    float simulationSpeed = 1;

    void simulate(float deltaTime, bool collided, vec2 bounceVector)
    {
        vec2 totalForce = gravity * mass;
        vec2 acceleration = totalForce * (1.0f / mass);
        velocity += acceleration * deltaTime * simulationSpeed;
        position += velocity;
        handleBounce();
        if (collided)
        {
            //   velocity = bounceVector * restitution;
        }
        
    }
    void handleBounce()
    {
        if (position.y > groundY)
        {
            // Reverse the velocity in the Y direction and apply restitution (energy loss)
            velocity.y = -velocity.y * restitution;
            position.y = groundY; // Keep at the surface level
        }
    }
    bool operator==(const Particle &other) const
    {
        return (position.x == other.position.x) && (position.y == other.position.y);
    }

    // Define the != operator using the == operator
    bool operator!=(const Particle &other) const
    {
        return !(*this == other);
    }
};