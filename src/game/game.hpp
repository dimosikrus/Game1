#pragma once

#include <SFML/Graphics.hpp>

#include "engine/logger.hpp"
#include "animations.hpp"

class Game {
	sf::RenderWindow& window;
    sf::Vector2f mousePosition{ 0.f, 0.f };

public:
    Game(sf::RenderWindow& window) : window(window) {
        //
	}

	void render() {
        //
    }

	void update(float dt) {
        //
    }

	void handleEvents(std::optional<sf::Event> event) {
        sf::Mouse::Button mButton;
        float scrolled;

        if (event->is<sf::Event::Closed>()) window.close();

        if (event->is<sf::Event::MouseButtonPressed>()) {
            mButton = event->getIf<sf::Event::MouseButtonPressed>()->button;
            switch (mButton) {
            case sf::Mouse::Button::Left:
                break;
            case sf::Mouse::Button::Right:
                break;
            default: break;
            }
        }

        if (event->is<sf::Event::MouseMoved>()) {
            mousePosition = sf::Vector2f(event->getIf<sf::Event::MouseMoved>()->position);
        }

        if (event->is<sf::Event::MouseWheelScrolled>()) {
            scrolled = event->getIf<sf::Event::MouseWheelScrolled>()->delta;
        }

        if (event->is<sf::Event::KeyPressed>()) {
            sf::Keyboard::Key code = event->getIf<sf::Event::KeyPressed>()->code;
            switch (code) {
            case sf::Keyboard::Key::W:
                break;
            default: break;
            }
        }

        if (event->is<sf::Event::KeyReleased>()) {
            sf::Keyboard::Key code = event->getIf<sf::Event::KeyReleased>()->code;
            switch (code) {
            case sf::Keyboard::Key::W:
                break;
            default: break;
            }
        }
	}
};