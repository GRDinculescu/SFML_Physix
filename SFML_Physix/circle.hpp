#include <SFML/Graphics.hpp>
#include "entity.hpp"
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class Circle : public Entity {
public:
	Circle(float radius = 10.f, sf::Color color = sf::Color::Cyan)
		: Entity(), radius(radius), color(color), shape(radius) {
		shape.setFillColor(color);
		shape.setOrigin({ radius, radius });
		shape.setPosition(pos);
		shape.setOutlineColor(sf::Color::Green);
	}

	EntityType getType() const override { return EntityType::CIRCLE; }

	sf::CircleShape& getShape() { return shape; }
	sf::Color getColor() const { return color; }
	float getRadius() const { return radius; }

	void setRadius(float r) { radius = r; shape.setRadius(r); shape.setOrigin({ r,r }); }
	void setColor(sf::Color color) { this->color = color; shape.setFillColor(color); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }
	void setFillColor(sf::Color color) { shape.setFillColor(color); }
	void toggleSelection() { shape.setOutlineThickness(shape.getOutlineThickness() != 0 ? 0.f : 3.f); }
	void setSelection(bool toggle) { shape.setOutlineThickness(toggle ? 3.f : 0.f); }

	void updateShape() { shape.setPosition(pos); }
	void setPosition(sf::Vector2f newPos) override { Entity::setPosition(newPos); updateShape(); }
private:
	float radius;
	sf::Color color;
	sf::CircleShape shape;
};

#endif // !CIRCLE_HPP
