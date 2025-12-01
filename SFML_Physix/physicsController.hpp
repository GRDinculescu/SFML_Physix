#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.hpp"
#include "circleObject.hpp"
#include "math.hpp"
#include "debug.hpp"
#include "collisionInfo.hpp"
#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP


class PhysicsSystem {
public:
	static PhysicsSystem& getInstance() {
		static PhysicsSystem instance;
		return instance;
	}

	void applyForces(Object& o, sf::Vector2f force, float g, float dt) {
		PhysicsComponent& phys = o.getPhysics();
		phys.acceleration = (force / o.getPhysics().mass + sf::Vector2f(0.f, g));
		phys.velocity = phys.velocity + phys.acceleration * dt;
		o.getTransform().position = o.getTransform().position + phys.velocity * dt;
	}

	void detectColision(Object& o1, Object& o2) {
		if (o1.getType() == ObjectType::CIRCLE && o2.getType() == ObjectType::CIRCLE) {
			float distance = Math::distanceBettweenCircles(static_cast<CircleObject&>(o1), static_cast<CircleObject&>(o2));
			//text.setString("Distance " + std::to_string(distance));
			if (distance <= 50)
				circleCircleColision(static_cast<CircleObject&>(o1), static_cast<CircleObject&>(o2), distance);
		}
		else if (o1.getType() == ObjectType::RECTANGLE && o2.getType() == ObjectType::RECTANGLE) {
			//rectangleRectangleColision(static_cast<Rectangle&>(o1), static_cast<Rectangle&>(o2));
		}
		else {
			//circleRectangleColision(...)
		}
	}

	// Indicates which sides to check for colisions
	void screenColisions(Object& o, sf::Vector2u windowSize, bool bottom = true, bool top = false, bool left = false, bool right = false) {
		switch (o.getType())
		{
			case ObjectType::CIRCLE:
				circleWindowColision(static_cast<CircleObject&>(o), windowSize, bottom, top, left, right);
				break;

			case ObjectType::RECTANGLE:
				//rectangleColision(static_cast<Rectangle&>(o), window, bottom, top, left, right);
				break;

			default:
				break;
		}
	}

private:
	void circleCircleColision(CircleObject& o1, CircleObject& o2, float distance) {
		if (CollisionDetector::circleCircle(o1, o2).collided) {
			if (o1.getPhysics().isTrigger || o2.getPhysics().isTrigger)
			{
				text.setString("Colision detected");
				o1.getRender().color = sf::Color::Red;
				o2.getRender().color = sf::Color::Red;
			}
			else
			{

			}
		}
		else
		{
			text.setString("No colision");
			o1.getRender().color = sf::Color::White;
			o2.getRender().color = sf::Color::White;
		}
	}

	// Circle colision with window borders
	void circleWindowColision(CircleObject& o, sf::Vector2u bounds, bool bottom = true, bool top = false, bool left = false, bool right = false) {
		float radius = o.getRadius();
		if (bottom) {
			sf::Vector2f pos = o.getTransform().position;
			sf::Vector2f speed = o.getPhysics().velocity;
			if (pos.y + radius > bounds.y) {
				o.getTransform().position = { pos.x, bounds.y - radius };
				o.getPhysics().velocity = { speed.x, -speed.y * o.getPhysics().restitution };
			}
		}
		if (top) {
			sf::Vector2f pos = o.getTransform().position;
			sf::Vector2f speed = o.getPhysics().velocity;
			if (pos.y - radius < 0.f) {
				o.getTransform().position = { pos.x, radius };
				o.getPhysics().velocity = { speed.x, -speed.y * o.getPhysics().restitution };
			}
		}
		if (left) {
			sf::Vector2f pos = o.getTransform().position;
			sf::Vector2f speed = o.getPhysics().velocity;
			if (pos.x - radius < 0.f) {
				o.getTransform().position = { radius, pos.y };
				o.getPhysics().velocity = { -speed.x * o.getPhysics().restitution, speed.y };
			}
		}
		if (right) {
			sf::Vector2f pos = o.getTransform().position;
			sf::Vector2f speed = o.getPhysics().velocity;
			if (pos.x + radius > bounds.x) {
				o.getTransform().position = { bounds.x - radius, pos.y };
				o.getPhysics().velocity = { -speed.x * o.getPhysics().restitution, speed.y };
			}
		}
	}

	sf::Text& text;
	PhysicsSystem() : text(Debug::getInstance().addText("Physix")) {}
	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(const PhysicsSystem&) = delete;
};

#endif // !PHYSICS_SYSTEM_HPP
