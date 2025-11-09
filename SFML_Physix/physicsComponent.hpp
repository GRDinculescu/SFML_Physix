#include <SFML/Graphics.hpp>
#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

class PhysicsComponent {
public:
	PhysicsComponent(const sf::Vector2f& initialVelocity = {}, float mass = 1.f, float restitution = 1.f)
		: velocity(initialVelocity), mass(mass), restitution(restitution) {}
	PhysicsComponent(const PhysicsComponent& other) = default;

	sf::Vector2f getVelocity() const { return velocity; }
	float getMass() const { return mass; }
	float getRestitution() const { return restitution; }

	void setVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }
	void setMass(float newMass) { mass = newMass; }
	void setRestitution(float newRestitution) { restitution = newRestitution; }

private:
	sf::Vector2f velocity;
	float mass;
	float restitution;
};

#endif // !PHYSICS_OBJECT_HPP
