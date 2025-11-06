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
const float MOVE_FORCE = 1000.f;
float WORLD_DIMENSIONS = 100.f;

// Singelton class instances
const auto& mc = MoveController::getInstance();
auto& ps = PhysicsSystem::getInstance();

// Generate text
sf::Font font;
sf::Text getText(sf::Font& font) {
	sf::Text text(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	return text;
}

sf::Vector2f normalize(const sf::Vector2f& v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y);
	if (length != 0)
		return sf::Vector2f(v / length);
	
	return sf::Vector2f({});
}

void printTexts(sf::RenderWindow& win, std::vector<sf::Text>& texts) {
	if (texts.size() > 0) {
		for (auto& text : texts) {
			win.draw(text);
		}
	}
}

void debugInfo(sf::RenderWindow& win, Entity& c) {
	float yHeight = c.getPosition().y;
	float heightFromGrownd = (WIN_SIZE.y - yHeight) / WORLD_DIMENSIONS;
	sf::Text heightText = getText(font);
	heightText.setString("Height from ground: " + std::to_string(heightFromGrownd) + "m");

	sf::Text posText = getText(font);
	posText.setPosition({ 0.f, 25.f });
	sf::Vector2f position = c.getPosition();
	posText.setString("X: " + std::to_string(position.x) + " | Y: " + std::to_string(position.y));

	sf::Text posSpeed = getText(font);
	posSpeed.setPosition({ 0.f, 50.f });
	sf::Vector2f speed = c.getSpeed();
	float speedMagnitude = std::sqrt(speed.x * speed.x + speed.y * speed.y);
	posSpeed.setString("X: " + std::to_string(speed.x) + " | Y: " + std::to_string(speed.y) + " | Speed mag: " + std::to_string(speedMagnitude));

	std::vector<sf::Text> texts = { heightText , posText , posSpeed };

	printTexts(win, texts);
}

void entityManager(Entity& e, sf::RenderWindow& win) {
	sf::Vector2f mousePos = mc.getMousePositionInWindow(win);
	sf::Vector2f entityPos = e.getPosition();

	if (e.getType() == EntityType::CIRCLE) {
		Circle& c = static_cast<Circle&>(e);
		
		float distanceToCenter = std::sqrt(std::powf(mousePos.x - entityPos.x, 2) + std::powf(mousePos.y - entityPos.y, 2));
		if (distanceToCenter <= c.getRadius()) {
			c.setSelected(true);
			c.setSelection(true);
		}
		else {
			c.setSelected(false);
			c.setSelection(false);
		}
	}
	else if (e.getType() == EntityType::RECTANGLE) {
		Rectangle& r = static_cast<Rectangle&>(e);
		// Do something with rectangle r
	}
}

void loop(sf::RenderWindow& win, std::vector<std::unique_ptr<Entity>>& entities) {
	// Delta time clock
	sf::Clock clock;
	float lastFps = 0;
	
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
			dir.x * MOVE_FORCE * WORLD_DIMENSIONS,
			dir.y * MOVE_FORCE * WORLD_DIMENSIONS
		};

		// Update and draw entities
		for (auto& entity : entities) {
			if (mc.isResetPressed()) {
				// Reset entity position and speed
				entity->setPosition({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f });
				entity->setSpeed({ 0.f, 0.f });
			}

			if (mc.mouseClick()) {
				entityManager(*entity, win);
			}

			ps.applyForces(*entity, force, GRAVITY * WORLD_DIMENSIONS, deltaTime);
			ps.screenColisions(*entity, win, true, true, true, true);
			
			if (entity->isSelected())
				debugInfo(win, *entity);

			entity->draw(win);
		}

		//Circle* c = dynamic_cast<Circle*>(entities.at(0).get());
		

		//c->setSelected(true);
		//c->drawSelection();

		// Display window
		win.display();
	}
}

Circle c; // Circle object
int main() {
	c.setColor(sf::Color::Red);
	c.setMass(0.62f * WORLD_DIMENSIONS);
	c.setPosition({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f });
	c.setRestitution(0.8f);
	c.setRadius(0.12f * WORLD_DIMENSIONS * 2.f);

	// Create entities vector
	std::vector<std::unique_ptr<Entity>> entities;
	entities.push_back(std::make_unique<Circle>(c));

	// Load font and create text
	if (!font.openFromFile("Fonts/SpaceMono.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	// Create window
	sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(WIN_SIZE), "Helo", sf::Style::Close);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	
	loop(win, entities);

	return 0;
}