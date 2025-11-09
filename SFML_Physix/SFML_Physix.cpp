#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "moveController.hpp"
#include "physicsController.hpp"
#include "object.hpp"
#include "circleObject.hpp"

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

void debugInfo(sf::RenderWindow& win, Object& o) {
	float yHeight = o.getTransform().getPosition().y;
	float heightFromGrownd = (WIN_SIZE.y - yHeight) / WORLD_DIMENSIONS;
	sf::Text heightText = getText(font);
	heightText.setString("Height from ground: " + std::to_string(heightFromGrownd) + "m");

	sf::Text posText = getText(font);
	posText.setPosition({ 0.f, 25.f });
	sf::Vector2f position = o.getTransform().getPosition();
	posText.setString("X: " + std::to_string(position.x) + " | Y: " + std::to_string(position.y));

	sf::Text posSpeed = getText(font);
	posSpeed.setPosition({ 0.f, 50.f });
	sf::Vector2f speed = o.getPhysics().getVelocity();
	float speedMagnitude = std::sqrt(speed.x * speed.x + speed.y * speed.y);
	posSpeed.setString("X: " + std::to_string(speed.x) + " | Y: " + std::to_string(speed.y) + " | Speed mag: " + std::to_string(speedMagnitude));

	std::vector<sf::Text> texts = { heightText , posText , posSpeed };

	printTexts(win, texts);
}

//void entityManager(Object& e, sf::RenderWindow& win) {
//	sf::Vector2f mousePos = mc.getMousePositionInWindow(win);
//	sf::Vector2f entityPos = e.getTransform().getPosition();
//
//	if (e.getType() == ObjectType::CIRCLE) {
//		CircleObject& c = static_cast<CircleObject&>(e);
//		
//		float distanceToCenter = std::sqrt(std::powf(mousePos.x - entityPos.x, 2) + std::powf(mousePos.y - entityPos.y, 2));
//		if (distanceToCenter <= c.getRadius()) {
//			c.setSelected(true);
//			c.setSelection(true);
//		}
//		else {
//			c.setSelected(false);
//			c.setSelection(false);
//		}
//	}
//}

void loop(sf::RenderWindow& win, std::vector<std::unique_ptr<Object>>& objects) {
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

		// Update and draw objects
		sf::Vector2f dir = mc.getDirections();
		sf::Vector2f force = {
			dir.x * MOVE_FORCE * WORLD_DIMENSIONS,
			dir.y * MOVE_FORCE * WORLD_DIMENSIONS
		};

		// Update and draw objects
		for (auto& object : objects) {
			if (mc.isResetPressed()) {
				// Reset entity position and speed
				object->getTransform().setPosition({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f });
				object->getPhysics().setVelocity({ 0.f, 0.f });
			}

			/*if (mc.mouseClick()) {
				entityManager(*object, win);
			}*/

			ps.applyForces(*object, force, GRAVITY * WORLD_DIMENSIONS, deltaTime);
			ps.screenColisions(*object, win, true, true, true, true);
			
			/*if (object->isSelected())
				debugInfo(win, *object);*/

			if (object->getType() == ObjectType::CIRCLE) {
				CircleObject* c = dynamic_cast<CircleObject*>(object.get());
				object->update(win, c->getShape());
			}
		}

		//CircleObject* c = dynamic_cast<CircleObject*>(objects.at(0).get());
		

		//c->setSelected(true);
		//c->drawSelection();

		// Display window
		win.display();
	}
}

int main() {
	// Create objects vector
	auto circle = std::make_unique<CircleObject>();
	circle->getTransform().setScale(sf::Vector2f({0.12f , 0.12f}) * WORLD_DIMENSIONS);
	circle->getTransform().setPosition(sf::Vector2f({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f }));
	circle->getPhysics().setMass(1.f * WORLD_DIMENSIONS);
	circle->getPhysics().setRestitution(0.8f);

	std::vector<std::unique_ptr<Object>> objects;
	objects.push_back(std::move(circle));

	// Load font and create text
	if (!font.openFromFile("Fonts/SpaceMono.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	// Create window
	sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(WIN_SIZE), "Helo", sf::Style::Close);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	
	loop(win, objects);

	return 0;
}