#include <SFML/Graphics.hpp>
#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

class RenderComponent {
public:
	RenderComponent(const sf::Color& color = sf::Color::White)
		: color(color) {}
	RenderComponent(const RenderComponent& other) = default;
	
	sf::Color getColor() const { return color; }

	void setColor(const sf::Color& newColor) { color = newColor; }
	void draw(sf::RenderWindow& window, sf::Shape& shape) const { shape.setFillColor(color); window.draw(shape); }

private:
	sf::Color color;
};

#endif