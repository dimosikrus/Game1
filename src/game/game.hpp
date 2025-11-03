#pragma once

#include <SFML/Graphics.hpp>

class Game {
	sf::RenderWindow& window;
    sf::Vector2f mousePosition{ 0.f, 0.f };
    sf::RectangleShape rect1;
    sf::RectangleShape rect2;
    sf::RectangleShape rect3;
    sf::RectangleShape rect4;
    sf::RectangleShape rect5;
    sf::RectangleShape rect6;
    sf::Angle rot = sf::degrees(0);
public:
	Game(sf::RenderWindow& window) : window(window),
          rect1({ 200.f, 50.f }), rect2({ 200.f, 50.f }),
          rect3({ 200.f, 50.f }), rect4({ 200.f, 50.f }),
          rect5({ 200.f, 50.f }), rect6({ 200.f, 50.f }) {
        rect1.setFillColor({ 200, 155, 67 });
        rect2.setFillColor({ 155, 200, 67 });
        rect3.setFillColor({ 155, 67, 200 });
        rect4.setFillColor({ 200, 67, 155 });
        rect5.setFillColor({ 155, 155, 67 });
        rect6.setFillColor({ 155, 155, 200 });
        rect1.setPosition({ 140.f, 150.f });
        rect2.setPosition({ 140.f, 150.f });
        rect3.setPosition({ 140.f, 150.f });
        rect4.setPosition({ 140.f, 150.f });
        rect5.setPosition({ 140.f, 150.f });
        rect6.setPosition({ 140.f, 150.f });
        rect1.setOrigin({ 100.f, 25.f });
        rect2.setOrigin({ 100.f, 25.f });
        rect3.setOrigin({ 100.f, 25.f });
        rect4.setOrigin({ 100.f, 25.f });
        rect5.setOrigin({ 100.f, 25.f });
        rect6.setOrigin({ 100.f, 25.f });
	}

	void render() {
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        window.draw(rect4);
        window.draw(rect5);
        window.draw(rect6);
    }

	void update() {
        rot += sf::degrees(1.f);
        if (rot.asDegrees() >= 360) {
            rot = sf::degrees(0);
        }
        rect1.setRotation(rot + sf::degrees(30.f));
        rect2.setRotation(rot + sf::degrees(60.f));
        rect3.setRotation(rot + sf::degrees(90.f));
        rect4.setRotation(rot + sf::degrees(120.f));
        rect5.setRotation(rot + sf::degrees(150.f));
        rect6.setRotation(rot + sf::degrees(180.f));
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