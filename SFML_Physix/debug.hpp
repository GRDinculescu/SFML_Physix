#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <deque>
#ifndef DEBUG_HPP
#define DEBUG_HPP

class Debug {
public:
	static Debug& getInstance() {
		static Debug instance;
		return instance;
	}

	void printTexts(sf::RenderWindow& win) {
		if (texts.size() > 0) {
			for (auto& text : texts) {
				win.draw(text);
			}
		}
	}

	sf::Text& addText(std::string text = "") {
		texts.emplace_back(getText(font));
		sf::Text& sfText = texts.back();
		sfText.setString(text); // Set the text string
		sfText.setPosition({ 10.f, currentPos++ * 12 }); // Set position
		return sfText; // Return reference to the last added text
	}
private:
	std::deque<sf::Text> texts;
	float currentPos = 0;
	sf::Font font;
	sf::Text getText(sf::Font& font) {
		sf::Text text(font);
		text.setCharacterSize(10);
		text.setFillColor(sf::Color::White);

		return text;
	}

	Debug() {
		if (!font.openFromFile("Fonts/SpaceMono.ttf")) {
			std::cout << "Failed to load font!" << std::endl;
		}
	}
	Debug(const Debug&) = delete;
	Debug& operator=(const Debug&) = delete;
};

#endif // !PHYSICS_COMPONENT_HPP