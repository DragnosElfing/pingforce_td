#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/WindowEnums.hpp"

int main()
{
    sf::RenderWindow window {sf::VideoMode{{300, 300}}, "PingForce TD", sf::Style::Default, sf::State::Windowed};
    window.setFramerateLimit(60);

    auto const closeEvent = [&window](sf::Event::Closed const&){
        window.close();
    };

    while(window.isOpen()) {
        window.handleEvents(closeEvent);
        window.display();
    }

    return 0;
}
