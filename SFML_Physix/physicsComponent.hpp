#include <SFML/Graphics.hpp>
#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

class PhysicsComponent {
public:
	PhysicsComponent(const sf::Vector2f& initialVelocity = {}, const sf::Vector2f& accelerationVelocity = {},
		float mass = 1.f, float restitution = 1.f)
		: velocity(initialVelocity), acceleration(accelerationVelocity), mass(mass), restitution(restitution) { }

	float getVelocityMagnitude() const { return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y); }
	float getAccelerationMagnitude() const { return std::sqrt(acceleration.x * acceleration.x + acceleration.y * acceleration.y); }

	float mass;
	bool isTrigger = false;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float restitution;
};

#endif // !PHYSICS_OBJECT_HPP
