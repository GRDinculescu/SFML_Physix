#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "circleObject.hpp"
#ifndef DRAW_CONTROLLER_HPP
#define DRAW_CONTROLLER_HPP

class DrawController {
public:
	static DrawController& getInstance() {
		static DrawController instance;
		return instance;
	}

	void update(sf::RenderWindow& window, Object& o) {
		sf::Shape* shape = nullptr;
		if (o.getType() == ObjectType::CIRCLE) {
			shape = &updateCircle(window, static_cast<CircleObject&>(o));
		}
		if (shape == nullptr) return;
		shape->setPosition(o.getTransform().position);
		shape->setFillColor(o.getRender().color);
		window.draw(*shape);
	}

private:
	sf::Shape& updateCircle(sf::RenderWindow& window, CircleObject& c) {
		float radius = c.getRadius();
		sf::CircleShape& shape = c.getShape();
		shape.setRadius(radius);
		shape.setOrigin({ radius, radius }); // Center the origin
		return shape;
	}


	DrawController() = default;
	DrawController(const DrawController&) = delete;
	DrawController& operator=(const DrawController&) = delete;
};

#endif