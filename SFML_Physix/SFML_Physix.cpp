#include <iostream>
#include <SFML/Graphics.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "moveController.hpp"

sf::Vector2u WIN_SIZE = {800, 600};
const float GRAVITY = 9.81f;
const float MOVE_FORCE = 10.f;

const auto& mc = MoveController::getInstance();
Circle c;

int main() {
	float radius = 20.f;
	c.setPosition({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f })
		.setMass(100.f)
		.setRadius(radius);


	sf::Font font;
	if (!font.openFromFile("Fonts/SpaceMono.ttf")) {
		return -1;
	}
	sf::Text text(font);
	text.setString("");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(WIN_SIZE), "Helo");
	win.setFramerateLimit(60);

	while (win.isOpen()) {
		while (const std::optional event = win.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				win.close();
			}
		}

		win.clear();

		sf::Vector2f dir = mc.getDirections();
		sf::Vector2f force = {
			dir.x * MOVE_FORCE,
			dir.y * MOVE_FORCE + GRAVITY
		};
		c.move(force).screenColisions(win).draw(win);

		sf::Vector2f pos = c.getPosition();

		text.setString("Y: " + std::to_string(pos.y));

		win.draw(text);

		win.display();
	}

	return 0;
}