#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "circle.hpp"
#include "rectangle.hpp"
#include "moveController.hpp"
#include "physicsSystem.hpp"
#include "entity.hpp"

// Constants
sf::Vector2u WIN_SIZE = {800, 600};
const float GRAVITY = 9.81f;
const float MOVE_FORCE = 10.f;

// Singelton class instances
const auto& mc = MoveController::getInstance();
auto& ps = PhysicsSystem::getInstance();

// Generate text
sf::Text getText(sf::Font& font) {
	sf::Text text(font);
	text.setString("");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	return text;
}

void loop(sf::RenderWindow& win, std::vector<std::unique_ptr<Entity>>& entities, std::vector<sf::Text>& texts) {
	// Delta time clock
	sf::Clock clock;
	
	while (win.isOpen()) { // Main loop
		// Calculate delta time
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = win.pollEvent()) // Event polling
		{
			if (event->is<sf::Event::Closed>()) {
				win.close();
			}
		}

		// Clear window
		win.clear();

		// Update and draw entities
		sf::Vector2f dir = mc.getDirections();
		sf::Vector2f force = {
			dir.x * MOVE_FORCE,
			dir.y * MOVE_FORCE
		};

		// Update and draw entities
		for (auto& entity : entities) {
			ps.applyForces(*entity, force, GRAVITY, deltaTime);
			ps.screenColisions(*entity, win, true);
			entity->draw(win);
		}

		// Print texts
		if (texts.size() > 0) {
			for (auto& text : texts) {
				float yHeight = dynamic_cast<Circle*>(entities.at(0).get())->getPosition().y;
				text.setString("Y Position: " + std::to_string(yHeight));
				win.draw(text);
			}
		}

		// Display window
		win.display();
	}
}

Circle c; // Circle object
int main() {
	c.setColor(sf::Color::Red);
	c.setMass(0.01f);
	c.setPosition({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f });
	c.setRestitution(0.5f);

	// Create entities vector
	std::vector<std::unique_ptr<Entity>> entities;
	entities.push_back(std::make_unique<Circle>(c));

	// Load font and create text
	sf::Font font;
	sf::Text text = getText(font);
	if (!font.openFromFile("Fonts/SpaceMono.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	// Create text vector
	std::vector<sf::Text> texts;
	texts.push_back(text);

	// Create window
	sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(WIN_SIZE), "Helo");
	win.setFramerateLimit(60);

	loop(win, entities, texts);

	return 0;
}