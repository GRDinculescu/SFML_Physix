#include <SFML/Graphics.hpp>
#include "object.hpp"
#ifndef CIRCLE_OBJECT_HPP
#define CIRCLE_OBJECT_HPP

class CircleObject : public Object {
public:
	CircleObject(sf::Vector2f scale = {}, sf::Color color = sf::Color::White, sf::Vector2f position = {}) : Object() {
		shape.setRadius(1.f);
		shape.setOrigin({ 1.f, 1.f }); // Center the origin

		Object::getTransform().setScale(scale);
		Object::getTransform().setPosition(position);
		Object::getRender().setColor(color);
	}

	sf::CircleShape& getShape() { return shape; }

	ObjectType getType() const override { return ObjectType::CIRCLE; }

private:
	sf::CircleShape shape;
};

#endif // !CIRCLE_OBJECT_HPP