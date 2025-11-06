#include <SFML/Graphics.hpp>
#ifndef ENTITY_HPP
#define ENTITY_HPP

enum EntityType {
	CIRCLE,
	RECTANGLE
};

class Entity {
public:
	Entity(sf::Vector2f pos = {}, sf::Vector2f speed = {}, float mass = 1, float restitution = 1.f)
		: pos(pos), speed(speed), mass(mass), restitution(restitution) {
	}

	virtual EntityType getType() const = 0;

	virtual ~Entity() = default;

	sf::Vector2f getPosition() const { return pos; }
	sf::Vector2f getSpeed() const { return speed; }
	float getMass() const { return mass; }
	float getRestitution() const { return restitution; }

	virtual void setPosition(sf::Vector2f newPos) { pos = newPos; }
	void setSpeed(sf::Vector2f newSpeed) { speed = newSpeed; }
	void setMass(float newMass) { mass = newMass; }
	void setRestitution(float newRestitution) { restitution = newRestitution; }

	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	sf::Vector2f pos;
	sf::Vector2f speed;
	float mass;
	float restitution;
};

#endif // !OBJECT_HPP
