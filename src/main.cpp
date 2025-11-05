#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/logger.hpp"
#include "engine/audio/audio.hpp"
#include "engine/filesystem/filesystem.hpp"
#include "game/game.hpp"

static bool spriteCollision(const sf::Sprite& sprite, const sf::Vector2f position) {
    return sprite.getGlobalBounds().contains(position);
};

float avg(const float arr[], int size) {
    if (size <= 0) {
        return 0.0f;
    }

    float sum = 0.0f;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }

    return sum / static_cast<float>(size);
}
void pushValueFpS(float arr[], int size, float val) {
    for (int i = size-2; i >= 0; i--) {
        arr[i + 1] = arr[i];
        //std::cout << i << "\t";
    }
    //std::cout << '\n';
    *arr = val;
    //for (int i = 0; i < size; i++) {
    //    std::cout << arr[i] << "\t";
    //}
    //std::cout << '\n';
}

int main() {
    Logger::log(LogLevel::INFO, "INFO Logger");
    Logger::log(LogLevel::WARN, "WARNING Logger");
    Logger::log(LogLevel::ERR, "ERROR Logger");
    Logger::log(LogLevel::DEBUG, "DEBUG Logger");

    Audio audio;
    audio.setSoundsVolume(0.4f);

    Logger::log(LogLevel::DEBUG, "AUDIO INITIALIZED");

    sf::VideoMode video_mode({ 1366,768 });
    constexpr auto window_style = sf::Style::Titlebar | sf::Style::Close;
    sf::RenderWindow window(video_mode, "Game", window_style);
    sf::Vector2f windowFSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});
    sf::Clock clock;
    Logger::log(LogLevel::DEBUG, "WINDOW INITIALIZED");
    window.setFramerateLimit(240);

    Game game(window);

    sf::Font BASICFONT(get_executable_path() / "assets\\arial.ttf");
    sf::Vector2f mousePosition = { 0.f, 0.f };

    float fps = 0;
    float dt = 1;
    int fpsDelayCounter = 0;

    sf::Text fpsText(BASICFONT, "FPS: 0");
    fpsText.setPosition({ 5.f, 5.f });
    fpsText.setCharacterSize(14u);
    float fpss[10];
    for (int i = 0; i < 10; i++) { // fill array
        fpss[i] = 0;
    }

    Logger::log(LogLevel::DEBUG, "Window events handler running...");

    while (window.isOpen()) {
        clock.start();
        while (std::optional<sf::Event> event = window.pollEvent()) game.handleEvents(event);
        window.clear(sf::Color::Black);

        pushValueFpS(fpss, 10, fps);
        if (fpsDelayCounter > 150) {
            std::ostringstream oss;
            oss << "FPS: " << avg(fpss, 10);
            fpsText.setString(oss.str());
            fpsDelayCounter = 0;
            //Logger::log(LogLevel::INFO, oss.str(), Ansi::Color::BRIGHT_GREEN);
            //Logger::log(LogLevel::INFO, std::to_string(dt), Ansi::Color::BRIGHT_GREEN);
        }

        fpsDelayCounter++;
        window.draw(fpsText);
        //
        game.update(dt);
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

