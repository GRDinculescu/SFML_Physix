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

	bool isResetPressed() const {
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
	}

	bool toggleSelected() const {
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
	}

	bool mouseClick() const {
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}

	sf::Vector2f getMousePositionInWindow(sf::RenderWindow& window) const {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		return sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	}

private:
	MoveController() = default;
	MoveController(const MoveController&) = delete;
	MoveController& operator=(const MoveController&) = delete;
};

#endif // !MOVE_CONTROLLER_HPP
