#include <SFML/Graphics.hpp>
#ifndef COLIDER_COMPONENT_HPP
#define COLIDER_COMPONENT_HPP

class ColiderComponent {
public:
	ColiderComponent(const sf::Vector2f& scale = {}, bool isTrigger = false)
		: scale(scale), isTrigger(isTrigger) {}
	ColiderComponent(const ColiderComponent& other) = default;
	
	sf::Vector2f scale;
	bool isTrigger;
};

#endif // !COLIDER_COMPONENT_HPP
