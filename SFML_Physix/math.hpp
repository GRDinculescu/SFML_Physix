#include <SFML/Graphics.hpp>
#include "circleObject.hpp"
#ifndef MATH_HPP
#define MATH_HPP

class Math {
public:
	static sf::Vector2f divideVectors(const sf::Vector2f& v, const sf::Vector2f& v2) {
		return sf::Vector2f({ v.x / v2.x, v.y / v2.y });
	}

	static float distanceBettweenPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
		float x = p2.x - p1.x;
		float y = p2.y - p1.y;
		return std::sqrt(x*x + y*y);
	}

	static float distanceBettweenCircles(CircleObject& o1, CircleObject& o2) {
		return distanceBettweenPoints(o1.getTransform().position, o2.getTransform().position)
			- (o1.getRadius() + o2.getRadius());
	}

	static sf::Vector2f getObjectsVector(Object& o1, Object& o2) {
		return sf::Vector2f({
			o2.getTransform().position.x - o1.getTransform().position.x,
			o2.getTransform().position.y - o1.getTransform().position.y
			});
	}

	static sf::Vector2f getPerpendicularVector(const sf::Vector2f& v) {
		return sf::Vector2f({ -v.y, v.x });
	}
};

#endif // !PHYSICS_OBJECT_HPP
