#include <SFML/Graphics.hpp>
#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

class RenderComponent {
public:
	RenderComponent(const sf::Color& color = sf::Color::White)
		: color(color) {}
	
	sf::Color color;
};

#endif