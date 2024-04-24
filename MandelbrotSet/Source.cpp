// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/String.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

Vector2f midpointcalc(Vector2f first, Vector2f second) {
    Vector2f midPoint;
    midPoint.x = (first.x + second.x) / 2;
    midPoint.y = (first.y + second.y) / 2;
    return midPoint;
}

int main()
{
        Font font;
        try{
        if (!font.loadFromFile("enervate.ttf")) {
            throw runtime_error("Font Failed!");
        }
    }
        catch (const runtime_error& e) { cout << e.what() << endl; }

    

        srand(time(NULL));
        // Create a video mode object
        VideoMode vm(1920, 1080);
        // Create and open a window for the game
        RenderWindow window(vm, "Chaos Game!!", Style::Default);

        sf::Text initial;
        initial.setFont(font);
        initial.setString("Press Y to Begin or N to Exit");
        initial.setCharacterSize(100);
        initial.setFillColor(Color::Red);
        sf::FloatRect initialRect = initial.getLocalBounds();
        initial.setOrigin(initialRect.left + initialRect.width / 2.0f,
        initialRect.top + initialRect.height / 2.0f);
        initial.setPosition(window.getView().getCenter());

        Text prompt;
        prompt.setFont(font);
        prompt.setCharacterSize(80);
        prompt.setString("Click On Any Three Points On The Screen...\nIf You Dare...");
        prompt.setFillColor(Color::Red);
        sf::FloatRect promptRect = prompt.getLocalBounds();
        prompt.setOrigin(promptRect.left + promptRect.width / 2.0f,
        promptRect.top + promptRect.height / 2.0f);
        prompt.setPosition(window.getView().getCenter());
        prompt.move(0.f, -350.f);

        Text startProgram;
        startProgram.setFont(font);
        startProgram.setCharacterSize(80);
        startProgram.setString("Now Choose a Fourth...\nWisely...");
        startProgram.setFillColor(Color::Red);
        sf::FloatRect startProgramRect = startProgram.getLocalBounds();
        startProgram.setOrigin(startProgramRect.left + startProgramRect.width / 2.0f,
        startProgramRect.top + startProgramRect.height / 2.0f);
        startProgram.setPosition(window.getView().getCenter());
        startProgram.move(0.f, -350.f);


        vector<Vector2f> vertices;
        vector<Vector2f> points;

        while (window.isOpen())
        {
            /*
            ****************************************
            Handle the players input
            ****************************************
            */
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    // Quit the game when the window is closed
                    window.close();
                }
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            std::cout << "the left button was pressed" << std::endl;
                            std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                            std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                            if (vertices.size() < 3)
                            {
                                vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                            }
                            else if (points.size() == 0)
                            {
                                ///fourth click
                                ///push back to points vector
                                Vector2f currentpos;
                                currentpos.x = event.mouseButton.x;
                                currentpos.y = event.mouseButton.y;
                                points.push_back(currentpos);
                            }
                        }
                    }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    window.close();
                }
                /*
                ****************************************
                Update
                ****************************************
                */

                if (points.size() > 0)
                {
                    ///generate more point(s)
                    ///select random vertex
                    ///calculate midpoint between random vertex and the last point in the vector
                    ///push back the newly generated coord.
                    for (int i = 0; i < 125; i++) {
                        int chooserVar = rand() % 3;
                        Vector2f spotNew;
                        spotNew = midpointcalc(vertices[chooserVar], points[points.size() - 1]);
                        points.push_back(spotNew);
                    }
                }

                /*
                ****************************************
                Draw
                ****************************************
                */
                window.clear();

                window.draw(initial);

                if (Keyboard::isKeyPressed(Keyboard::Y)) {

                    initial.setFillColor(Color::Black);

                }
                else if (Keyboard::isKeyPressed(Keyboard::N)) { window.close(); }

                if (initial.getFillColor() == Color::Black) {window.draw(prompt);}

                if (vertices.size() >= 3) { prompt.setFillColor(Color::Black);}

                if (prompt.getFillColor() == Color::Black) { window.draw(startProgram);}

                if (points.size() >  0) { startProgram.setFillColor(Color::Black); }

                //for (int i = 0; i < 15; i++) {
                    for (int i = 0; i < vertices.size(); i++)
                    {
                        RectangleShape rect(Vector2f(1, 1));
                        rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
                        rect.setFillColor(Color::Blue);
                        window.draw(rect);
                    }
                    for (int i = 0; i < points.size(); i++) {
                        RectangleShape rect(Vector2f(1, 1));
                        rect.setPosition(Vector2f(points[i].x, points[i].y));
                        rect.setFillColor(Color::Blue);
                        window.draw(rect);
                    }
               // }
              

                window.display();
            
                
        }
    }
}