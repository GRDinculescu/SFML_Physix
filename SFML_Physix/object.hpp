#include <SFML/Graphics.hpp>
#ifndef OBJECT_HPP
#define OBJECT_HPP

template <typename Derived>
class Object {
public:
	Object(sf::Vector2f pos = {}, sf::Vector2f speed = {}, float mass = 1, float restitution = 1.f)
		: pos(pos), speed(speed), mass(mass), restitution(restitution) {
	}

	virtual ~Object() = default;

	virtual Derived& move(const sf::Vector2f force) {
		speed += force / mass;

		pos += speed;

		return static_cast<Derived&>(*this);
	}

	virtual Derived& draw(sf::RenderWindow& window) = 0;

	virtual Derived& screenColisions(sf::RenderWindow& window,
		bool bottom = true, bool top = false, bool left = false, bool right = false) = 0;

protected:
	sf::Vector2f pos;
	sf::Vector2f speed;
	float mass;
	float restitution;
};

#endif // !OBJECT_HPP
