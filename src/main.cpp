using fn = int;

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/audio/audio.hpp"
#include "engine/filesystem/filesystem.hpp"
#include "engine/logger.hpp"
#include "game/game.hpp"

static bool spriteCollision(const sf::Sprite& sprite, const sf::Vector2f position) {
    return sprite.getGlobalBounds().contains(position);
};

fn main() {
    Logger logger;

    logger.log(LogLevel::INFO, "INFO Logger");
    logger.log(LogLevel::WARN, "WARNING Logger");
    logger.log(LogLevel::ERR, "ERROR Logger");
    logger.log(LogLevel::DEBUG, "DEBUG Logger");

    Audio audio;
    audio.setSoundsVolume(0.4f);

    logger.log(LogLevel::DEBUG, "AUDIO INITIALIZED");

    sf::VideoMode video_mode({ 1366,768 });
    constexpr auto window_style = sf::Style::Titlebar | sf::Style::Close;
    sf::RenderWindow window(video_mode, "Game", window_style);
    sf::Vector2f windowFSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});
    sf::Clock clock;
    logger.log(LogLevel::DEBUG, "WINDOW INITIALIZED");
    window.setFramerateLimit(240);

    Game game(window);

    sf::Font BASICFONT(get_executable_path() / "assets\\arial.ttf");
    sf::Vector2f mousePosition = { 0.f, 0.f };

    float fps = 0;
    float dt = 1;
    int fpsDelayCounter = 0;

    sf::Text fpsText(BASICFONT, "FPS: 0");
    fpsText.setPosition({ 15.f, 15.f });

    logger.log(LogLevel::DEBUG, "Window events handler running...");

    while (window.isOpen()) {
        clock.start();
        while (std::optional<sf::Event> event = window.pollEvent()) game.handleEvents(event);//events(event, window, mousePosition);
        window.clear(sf::Color::Black);

        //if (fpsDelayCounter > 500) {
            std::ostringstream oss;
            oss << "FPS: " << fps;
            fpsText.setString(oss.str());
            fpsDelayCounter = 0;
        //}

        fpsDelayCounter++;
        window.draw(fpsText);
        //
        game.update();
        game.render();
        //
        window.display();
        dt = static_cast<float>(clock.getElapsedTime().asMicroseconds())/1000;
        fps = 1000 / (dt > 0 ? dt : 1);
        clock.reset();
    }

    window.close();
    return 0;
};

