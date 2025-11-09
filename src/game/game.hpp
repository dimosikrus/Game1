#pragma once

#include <SFML/Graphics.hpp>

#include "engine/logger.hpp"
#include "animations.hpp"
#include <vector>

struct Fold7 {
    sf::RectangleShape rect;
    float NowTime = 0;
};

class Game {
	sf::RenderWindow& window;
    sf::Vector2f mousePosition{ 0.f, 0.f };
    std::vector<Fold7> rects;
    float MaxTime = 3000.f;

public:
    Game(sf::RenderWindow& window) : window(window) {
        for (int i = 0; i < 100; i++) {
            sf::RectangleShape rect({ 55.f, 55.f });
            rect.setFillColor(sf::Color(188-i, 130+i, 75, 88));
            rect.setPosition({ 0,0 });

            Fold7 fold7;
            fold7.rect = rect;
            fold7.NowTime = static_cast<float>(i) * 5.f;

            rects.push_back(fold7);
        }
	}

	void render() {
        for (auto& rect : rects) {
            window.draw(rect.rect);
        }
    }

	void update(float dt) {
        for (int i = 0; i < 100; i++) {
            rects.at(i).NowTime += dt;

            rects.at(i).rect.setPosition({ 80.f + static_cast<float>(i) / 100.f * 650.f, 200.f + Anim::easeOutBounce(rects.at(i).NowTime / MaxTime) * 350.f });

            if (rects.at(i).NowTime >= MaxTime) {
                rects.at(i).NowTime = 0;
            }
        }
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
                window.setSize({ 800u, 600u });
                break;
            case sf::Keyboard::Key::S:
                window.setSize({ 1366u, 768u });
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