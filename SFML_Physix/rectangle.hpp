#include <SFML/Graphics.hpp>
#include "object.hpp"
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle : public Object<Rectangle> {
public:
	Rectangle(sf::Vector2f size = { 10.f, 10.f }, sf::Color color = sf::Color::Cyan) : Object(), size(size), color(color) {
		shape.setSize(size);
		shape.setPosition(pos);
		shape.setFillColor(color);
		shape.setOrigin(size / 2.f);
	}

	Rectangle& setSize(sf::Vector2f size) { this->size = size; shape.setSize(size); shape.setOrigin(size / 2.f); return *this; }
	Rectangle& setPosition(sf::Vector2f pos) { this->pos = pos; shape.setPosition(pos); return *this; }
	Rectangle& setColor(sf::Color color) { this->color = color; shape.setFillColor(color); return *this; }
	Rectangle& setSpeed(sf::Vector2f speed) { this->speed = speed; return *this; }
	Rectangle& setMass(float mass) { this->mass = mass; return *this; }
	Rectangle& setRestitution(float restitution) { this->restitution = restitution; return *this; }
	Rectangle& draw(sf::RenderWindow& window) override { window.draw(shape); return *this; }

	Rectangle& move(const sf::Vector2f force) override {
		Object::move(force);
		shape.setPosition(pos);
		return *this;
	}

	sf::RectangleShape& getShape() {
		return shape;
	}
private:
	sf::Vector2f size;
	sf::Color color;
	sf::RectangleShape shape;
};

#endif // !RECTANGLE_HPP
