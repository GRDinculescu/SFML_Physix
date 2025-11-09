#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "circleObject.hpp"
#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

class PhysicsSystem {
public:
	static PhysicsSystem& getInstance() {
		static PhysicsSystem instance;
		return instance;
	}

	void applyForces(Object& o, sf::Vector2f force, float g, float dt) {
		sf::Vector2f acceleration = force / o.getPhysics().getMass();
		sf::Vector2f newSpeed = o.getPhysics().getVelocity() + (acceleration + sf::Vector2f(0.f, g)) * dt;
		sf::Vector2f newPosition = o.getTransform().getPosition() + newSpeed * dt;

		o.getPhysics().setVelocity(newSpeed);
		o.getTransform().setPosition(newPosition);
	}

	// Indicates which sides to check for colisions
	void screenColisions(Object& o, sf::RenderWindow& window, bool bottom = true, bool top = false, bool left = false, bool right = false) {
		switch (o.getType())
		{
			case ObjectType::CIRCLE:
				circleColision(static_cast<CircleObject&>(o), window, bottom, top, left, right);
				break;

			case ObjectType::RECTANGLE:
				//rectangleColision(static_cast<Rectangle&>(o), window, bottom, top, left, right);
				break;

			default:
				break;
		}
	}

	// Circle colision with window borders
	void circleColision(CircleObject& o, sf::RenderWindow& window, bool bottom = true, bool top = false, bool left = false, bool right = false) {
		sf::Vector2f scale = o.getTransform().getScale();
		if (bottom) {
			sf::Vector2f pos = o.getTransform().getPosition();
			sf::Vector2f speed = o.getPhysics().getVelocity();
			if (pos.y + scale.y > window.getSize().y) {
				o.getTransform().setPosition({ pos.x, window.getSize().y - scale.y });
				o.getPhysics().setVelocity({ speed.x, -speed.y * o.getPhysics().getRestitution() });
			}
		}
		if (top) {
			sf::Vector2f pos = o.getTransform().getPosition();
			sf::Vector2f speed = o.getPhysics().getVelocity();
			if (pos.y - scale.y < 0.f) {
				o.getTransform().setPosition({ pos.x, scale.y });
				o.getPhysics().setVelocity({ speed.x, -speed.y * o.getPhysics().getRestitution() });
			}
		}
		if (left) {
			sf::Vector2f pos = o.getTransform().getPosition();
			sf::Vector2f speed = o.getPhysics().getVelocity();
			if (pos.x - scale.x < 0.f) {
				o.getTransform().setPosition({ scale.x, pos.y });
				o.getPhysics().setVelocity({ -speed.x * o.getPhysics().getRestitution(), speed.y });
			}
		}
		if (right) {
			sf::Vector2f pos = o.getTransform().getPosition();
			sf::Vector2f speed = o.getPhysics().getVelocity();
			if (pos.x + scale.x > window.getSize().x) {
				o.getTransform().setPosition({ window.getSize().x - scale.x, pos.y });
				o.getPhysics().setVelocity({ -speed.x * o.getPhysics().getRestitution(), speed.y });
			}
		}
	}

private:
	PhysicsSystem() = default;
	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(const PhysicsSystem&) = delete;
};

#endif // !PHYSICS_SYSTEM_HPP
