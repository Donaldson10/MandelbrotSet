#include "ComplexPlane.h"
#include <iostream>	
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <complex>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

// done for easy of use
using namespace std;
using namespace sf;


int main() {
	//font attempt
	Font font;
	try {
		if (!font.loadFromFile("arial.ttf")) {
			throw runtime_error("Font Failed to load!");
		}
	}
	catch (const runtime_error& e) { cout << e.what() << endl; }
	//text 
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);



	// starters
	int desktopWid, desktopHei;
	desktopWid = sf::VideoMode::getDesktopMode().width;
	desktopHei = sf::VideoMode::getDesktopMode().height;
	ComplexPlane Complex1(desktopWid / 2, desktopHei / 2);
	VideoMode vm(desktopWid / 2, desktopHei / 2);
	RenderWindow window(vm, "Mondalbrot set!", Style::Default);
	Vector2i mouseloc;



	// event handler
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				
				if (event.mouseButton.button == Mouse::Left)
				{
					Complex1.zoomIn();
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					Complex1.zoomOut();
				}
			}
			if (event.type == Event::MouseMoved)
			{
				mouseloc.x = event.mouseButton.x;
				mouseloc.y = event.mouseButton.y;
				Complex1.setMouseLocation(mouseloc);
			}
			if (event.type == Keyboard::Escape)
			{
				window.close();
			}
		}
		
		Complex1.loadText(text);
		Complex1.updateRender();

		window.clear();
		window.draw(Complex1);
		window.draw(text);
		window.display();
	}

	return 0;
}