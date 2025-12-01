#include <SFML/Graphics.hpp>
#include "object.hpp"
#ifndef CIRCLE_OBJECT_HPP
#define CIRCLE_OBJECT_HPP

class CircleObject : public Object {
public:
	CircleObject(sf::Vector2f scale = {1.f, 1.f}, float radius = 1.f, sf::Color color = sf::Color::White, sf::Vector2f position = {}) :
		Object(), radius(radius) {
		shape.setRadius(radius);
		shape.setOrigin({ 1.f, 1.f }); // Center the origin

		Object::getTransform().scale = scale;
		Object::getTransform().position = position;
		Object::getRender().color = color;
	}

	sf::CircleShape& getShape() { return shape; }

	ObjectType getType() const override { return ObjectType::CIRCLE; }

	float getRadius() const { return radius; }
	void setRadius(float newRadius) { 
		radius = newRadius; 
		shape.setRadius(newRadius);
	}

private:
	sf::CircleShape shape;
	float radius;
};

#endif // !CIRCLE_OBJECT_HPP