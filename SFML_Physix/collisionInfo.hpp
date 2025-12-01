#include <SFML/Graphics.hpp>
#include "circleObject.hpp"
#ifndef COLLISION_INFO_HPP
#define COLLISION_INFO_HPP

struct CollisionInfo {
    bool collided;
    float penetration;
    sf::Vector2f normal;
};

class CollisionDetector {
public:
    static CollisionInfo circleCircle(const CircleObject& a, const CircleObject& b)
    {
        sf::Vector2f diff = b.getTransform().position - a.getTransform().position;
        float dist = diff.length();
        float sum = a.getRadius() + b.getRadius();

        if (dist >= sum) {
            return { false, 0.f, {0.f, 0.f} };
        }

        float penetration = sum - dist;
        sf::Vector2f normal = diff / (dist >= 0.0001f ? dist : 0.0001f);

        return { true, penetration, normal };
    }
};

#endif // !COLLISION_INFO_HPP