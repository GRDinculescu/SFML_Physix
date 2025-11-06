#include <SFML/Graphics.hpp>
#include "entity.hpp"
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle : public Entity {
public:
	Rectangle(sf::Vector2f size = { 10.f, 10.f }, sf::Color color = sf::Color::Cyan) 
		: Entity(), size(size), color(color), shape(size) {
		shape.setFillColor(color);
		shape.setOrigin(size / 2.f);
		shape.setPosition(pos);
	}

	EntityType getType() const override { return EntityType::RECTANGLE; }

	sf::RectangleShape getShape() const { return shape; }
	sf::Color getColor() const { return color; }
	sf::Vector2f getSize() const { return size; }

	void setSize(sf::Vector2f size) { this->size = size; shape.setSize(size); shape.setOrigin(size / 2.f); }
	void setColor(sf::Color color) { this->color = color; shape.setFillColor(color); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }

	void updateShape() { shape.setPosition(pos); }
	void setPosition(sf::Vector2f newPos) override { Entity::setPosition(newPos); updateShape(); }

private:
	sf::Vector2f size;
	sf::Color color;
	sf::RectangleShape shape;
};

#endif // !RECTANGLE_HPP
