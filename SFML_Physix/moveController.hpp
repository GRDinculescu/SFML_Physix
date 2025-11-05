#include <SFML/Graphics.hpp>
#ifndef MOVE_CONTROLLER_HPP
#define MOVE_CONTROLLER_HPP

class MoveController {
public:
	static MoveController& getInstance() {
		static MoveController instance;
		return instance;
	}

	sf::Vector2f getDirections() const {
		sf::Vector2f directions = {};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) directions.y += -1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) directions.y += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) directions.x += -1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) directions.x += 1.f;
		return directions;
	}

private:
	MoveController() = default;
	MoveController(const MoveController&) = delete;
	MoveController& operator=(const MoveController&) = delete;
};

#endif // !MOVE_CONTROLLER_HPP
