// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1080, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    Font font;

    if (!font.loadFromFile("SuperShiny-0v0rG.ttf"))
    {
        return -1;
    }

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    int unsigned timesClicked = 0;

    sf::Text text;
    text.setFont(font);
    text.setString("Create your vertices by clicking \n five points in this window");
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);
    text.setPosition(120, 60);

    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator

    sf::Text frames;
    frames.setFont(font);
    frames.setCharacterSize(60);
    frames.setFillColor(sf::Color::Blue);
    frames.setStyle(sf::Text::Bold);
    frames.setPosition(120, 60);
   

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */

        frames.setString(std::to_string(points.size()));

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

                    timesClicked++;

                    if (vertices.size() < 5)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        /// After the fifth click, start the algorithm with the initial point
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
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
            /// Generate more point(s)
            Vector2f new_point = Vector2f(0.0, 0.0);
            /// Select random vertex
            Vector2f rand_vertex = vertices.at(rand() % 5);
            /// Calculate midpoint between random vertex and the last point in the vector
            new_point.x = (points.back().x + rand_vertex.x)  * 0.3;
            new_point.y = (points.back().y + rand_vertex.y) * 0.3;
            /// Push back the newly generated coord.
            points.push_back(new_point);
        }

        

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();
        if (timesClicked == 0 || timesClicked == 5) {
            if (timesClicked == 5)
            {
                text.setString("Click on a point to start the algorithm");
            }
            window.draw(text);
        }

        window.draw(frames);
        

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(5, 5));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape dot(Vector2f(1, 1));
            dot.setPosition(Vector2f(points[i].x, points[i].y));
            dot.setFillColor(Color::White);
            window.draw(dot);
        }

        window.display();
    }
}
