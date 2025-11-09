#include <SFML/Graphics.hpp>
#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

class TransformComponent
{
public:
	TransformComponent (const sf::Vector2f& pos = {}, const sf::Vector2f& scl = { 1.f , 1.f })
		: position(pos), scale(scl) {}

	void setPosition(const sf::Vector2f& pos) { position = pos; }
	void setScale(const sf::Vector2f& scl) { scale = scl; }

	sf::Vector2f getPosition() const { return position; }
	sf::Vector2f getScale() const { return scale; }

private:
	sf::Vector2f position;
	sf::Vector2f scale;
};

#endif // !TRANSFORM_HPP
