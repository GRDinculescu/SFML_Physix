#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "circle.hpp"
#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

class PhysicsSystem {
public:
	static PhysicsSystem& getInstance() {
		static PhysicsSystem instance;
		return instance;
	}

	void applyForces(Entity& o, sf::Vector2f force, float g, float dt) {
		sf::Vector2f acceleration = force / o.getMass();
		sf::Vector2f newSpeed = o.getSpeed() + (acceleration + sf::Vector2f(0.f, g)) *dt;
		sf::Vector2f newPosition = o.getPosition() + newSpeed * dt;

		o.setSpeed(newSpeed);
		o.setPosition(newPosition);
	}

	// Indicates which sides to check for colisions
	void screenColisions(Entity& o, sf::RenderWindow& window, bool bottom = true, bool top = false, bool left = false, bool right = false) {
		switch (o.getType())
		{
			case EntityType::CIRCLE:
				circleColision(static_cast<Circle&>(o), window, bottom, top, left, right);
				break;

			case EntityType::RECTANGLE:
				//rectangleColision(static_cast<Rectangle&>(o), window, bottom, top, left, right);
				break;

			default:
				break;
		}
	}

	// Circle colision with window borders
	void circleColision(Circle& o, sf::RenderWindow& window, bool bottom = true, bool top = false, bool left = false, bool right = false) {
		if (bottom) {
			sf::Vector2f pos = o.getPosition();
			sf::Vector2f speed = o.getSpeed();
			float radius = o.getRadius();
			if (pos.y + radius > window.getSize().y) {
				o.setPosition({ pos.x, window.getSize().y - radius });
				o.setSpeed({ speed.x, -speed.y * o.getRestitution() });
			}
		}
		if (top) {
			sf::Vector2f pos = o.getPosition();
			sf::Vector2f speed = o.getSpeed();
			float radius = o.getRadius();
			if (pos.y - radius < 0.f) {
				o.setPosition({ pos.x, radius });
				o.setSpeed({ speed.x, -speed.y * o.getRestitution() });
			}
		}
		if (left) {
			sf::Vector2f pos = o.getPosition();
			sf::Vector2f speed = o.getSpeed();
			float radius = o.getRadius();
			if (pos.x - radius < 0.f) {
				o.setPosition({ radius, pos.y });
				o.setSpeed({ -speed.x * o.getRestitution(), speed.y });
			}
		}
		if (right) {
			sf::Vector2f pos = o.getPosition();
			sf::Vector2f speed = o.getSpeed();
			float radius = o.getRadius();
			if (pos.x + radius > window.getSize().x) {
				o.setPosition({ window.getSize().x - radius, pos.y });
				o.setSpeed({ -speed.x * o.getRestitution(), speed.y });
			}
		}
	}

	


private:
	PhysicsSystem() = default;
	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(const PhysicsSystem&) = delete;
};

#endif // !PHYSICS_SYSTEM_HPP
