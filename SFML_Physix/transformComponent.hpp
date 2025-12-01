#include <SFML/Graphics.hpp>
#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

class TransformComponent
{
public:
	TransformComponent (const sf::Vector2f& pos = {}, const sf::Vector2f scale = {1.f, 1.f})
		: position(pos), scale(scale) {}

	sf::Vector2f position;
	sf::Vector2f scale;
};

#endif // !TRANSFORM_HPP
