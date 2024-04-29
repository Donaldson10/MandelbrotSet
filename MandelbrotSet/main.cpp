#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;

int main() {
    // font attempt
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    Text text("", font, 16);
    text.setFillColor(Color::White);

    // video window 
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(VideoMode(desktopMode.width / 2, desktopMode.height / 2), "Mandelbrot Set");

    ComplexPlane complexPlane(window.getSize().x, window.getSize().y);




    // event hanlders
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Right) {
                    complexPlane.zoomOut();
                    complexPlane.setCenter(Mouse::getPosition(window));
                }
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    complexPlane.zoomIn();
                    complexPlane.setCenter(Mouse::getPosition(window));
                }
            }
            else if (event.type == Event::MouseMoved) {
                complexPlane.setMouseLocation(Mouse::getPosition(window));
            }

            if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }


        // last handle for render
        complexPlane.updateRender();
        complexPlane.loadText(text);

        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}

	return 0;
}
