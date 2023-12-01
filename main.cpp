#include <SFML/Graphics.hpp>

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(750, 500), "Quixo window");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
