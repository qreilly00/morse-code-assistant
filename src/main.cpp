//include classes and headers
#include "../inc/common.hpp"
#include "TimeUtil.hpp"

int getRandomInt(int x, int y);

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);

    TimeUtil tu;
    int totalTime = 0;
    tu.setTime();

    int currentLetter = 0;
    bool response = 1;

    sf::Sound sound;
    sf::SoundBuffer buffer;

    while (window.isOpen()) {
        tu.setTime();
        totalTime += tu.getTime();

        if(totalTime >= 2000) {
            if(response == 1) {
                currentLetter = getRandomInt(1, 26);

                char bffrTmp = (char)currentLetter + '`';
                std::ostringstream out;
                out << "../aux/morsecode-snips-2/" << bffrTmp << ".wav";

                std::cout << out.str() << std::endl;

                if (!buffer.loadFromFile(out.str()))
                    return -1;

                sound.setBuffer(buffer);
                sound.play();

                shape.setFillColor(sf::Color::Yellow);

                response = 0;
            }

            totalTime = 0;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::TextEntered) {
                //bool correctAnswer = 0;
                if(event.text.unicode == currentLetter + 96) {
                    response = 1;
                    shape.setFillColor(sf::Color::Green);
                } else {
                    shape.setFillColor(sf::Color::Red);
                }

                tu.setTime();
                totalTime = 0;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }

    // Exit program.
    return 0;
}

int getRandomInt(int x, int y) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(x, y);

    return distribution(generator);
}
