#include <SFML/Graphics.hpp>
#include "object.hpp"
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class Circle : public Object<Circle> {
public:
	Circle(float radius = 10.f, sf::Color color = sf::Color::Cyan) : Object(), radius(radius), color(color) {
		shape.setRadius(radius);
		shape.setPosition(pos);
		shape.setFillColor(color);
		shape.setOrigin({ radius, radius });
	}

	sf::CircleShape& getShape() { return shape; }

	Circle& setRadius(float r) { radius = r; shape.setRadius(r); shape.setOrigin({ r,r }); return *this; }
	Circle& setPosition(sf::Vector2f pos) { this->pos = pos; shape.setPosition(pos); return *this; }
	Circle& setColor(sf::Color color) { this->color = color; shape.setFillColor(color); return *this; }
	Circle& setSpeed(sf::Vector2f speed) { this->speed = speed; return *this; }
	Circle& setMass(float mass) { this->mass = mass; return *this; }
	Circle& setRestitution(float restitution) { this->restitution = restitution; return *this; }
	Circle& draw(sf::RenderWindow& window) override { window.draw(shape); return *this; }


	Circle& move(const sf::Vector2f force) override {
		Object::move(force);
		shape.setPosition(pos);
		return *this;
	}

	Circle& screenColisions(sf::RenderWindow& window, bool bottom = true, bool top = false, bool left = false, bool right = false) override {
		if (bottom) {
			if (pos.y + radius > window.getSize().y) {
				this->setPosition({pos.x, window.getSize().y - radius});
				this->setSpeed({speed.x, -speed.y});
			}
		}
		return *this;
	}

	sf::Vector2f getPosition() { return pos; }
	sf::Vector2f getSpeed() { return speed; }

private:
	float radius;
	sf::Color color;
	sf::CircleShape shape;
};

#endif // !CIRCLE_HPP
