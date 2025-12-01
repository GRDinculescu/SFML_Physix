#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <Windows.h>

#include "moveController.hpp"
#include "physicsController.hpp"
#include "object.hpp"
#include "circleObject.hpp"
#include "drawController.hpp"
#include "debug.hpp"

// Constants
sf::Vector2u WIN_SIZE = {1280, 720};
const float GRAVITY = 9.81f;
const float MOVE_FORCE = 1000.f;
float WORLD_DIMENSIONS = 100.f;

// Singelton class instances
const auto& mc = MoveController::getInstance();
auto& ps = PhysicsSystem::getInstance();
auto& dc = DrawController::getInstance();
auto& db = Debug::getInstance();

void loop(sf::RenderWindow& win, std::vector<std::unique_ptr<Object>>& objects) {
	// Delta time clock
	sf::Clock clock;
	float lastFps = 0;
	
	sf::Text& circleDebug = db.addText();

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

		for (int i = 0; i < objects.size(); i++) {
			for (int j = i + 1; j < objects.size(); j++) {
				ps.detectColision(*objects.at(i), *objects.at(j));
			}
		}

		for (auto& object : objects) {
			ps.applyForces(*object, force, GRAVITY * WORLD_DIMENSIONS, deltaTime);
			ps.screenColisions(*object, win.getSize(), true, true, true, true);

			dc.update(win, *object);
		}

		if (mc.isResetPressed()) {
			for (auto& object : objects) {
				// Reset entity position and speed
				object->getTransform().position = { WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f };
				object->getPhysics().velocity = {};
			}
		}

		// Display window
		db.printTexts(win);

		win.display();
	}
}

int main() {
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	// Create objects vector
	auto circle = std::make_unique<CircleObject>();
	circle->setRadius(0.12f * WORLD_DIMENSIONS);
	circle->getTransform().position = (sf::Vector2f({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f }));
	circle->getPhysics().mass = (1.f * WORLD_DIMENSIONS);
	circle->getPhysics().restitution = 0.8f;
	circle->getPhysics().isTrigger = true;

	auto circle2 = std::make_unique<CircleObject>();
	circle2->setRadius(0.12f * WORLD_DIMENSIONS);
	circle2->getTransform().position = (sf::Vector2f({ WIN_SIZE.x / 2.f , WIN_SIZE.y / 2.f - 50.f }));
	circle2->getPhysics().mass = (1.f * WORLD_DIMENSIONS);
	circle2->getPhysics().restitution = 0.5f;
	circle2->getPhysics().isTrigger = true;

	std::vector<std::unique_ptr<Object>> objects;
	objects.push_back(std::move(circle));
	objects.push_back(std::move(circle2));
	
	// Create window
	sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(WIN_SIZE), "Helo", sf::Style::Close);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	
	loop(win, objects);

	return 0;
}