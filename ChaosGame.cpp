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
	VideoMode vm2(540, 270);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	RenderWindow shapePromptWindow(vm2, "2nd window", Style::Default);
	
	Font font;

	if (!font.loadFromFile("SuperShiny-0v0rG.ttf"))
	{
		return -1;
	}

	vector<Vector2f> vertices;
	vector<Vector2f> points;
	
	int unsigned timesClicked = 0;

	int unsigned numVertices = 0;

	sf::Text shapePrompt;
	shapePrompt.setFont(font);
	shapePrompt.setString("Press <T> for Triangle\nor <P> for Pentagon");
	shapePrompt.setCharacterSize(48);
	shapePrompt.setFillColor(sf::Color::Cyan);
	shapePrompt.setStyle(sf::Text::Regular);
	shapePrompt.setPosition(54, 54);

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::Cyan);
	text.setStyle(sf::Text::Bold);
	text.setPosition(120, 60);

	sf::Text iterText;
	iterText.setFont(font);
	iterText.setString(to_string(points.size()));
	iterText.setCharacterSize(32);
	iterText.setFillColor(sf::Color::Cyan);
	iterText.setStyle(sf::Text::Regular);
	iterText.setPosition(32, 48);

	while (shapePromptWindow.isOpen())
	{
		// Handle input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				shapePromptWindow.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			numVertices = 3;
			text.setString("Create your vertices by clicking\nthree points in this windows");
			shapePromptWindow.close();
		}
		else if (Keyboard::isKeyPressed(Keyboard::P))
		{
			numVertices = 5;
			text.setString("Create your vertices by clicking\nfive points in this windows");
			shapePromptWindow.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			shapePromptWindow.close();
		}

		// Draw
		shapePromptWindow.draw(shapePrompt);
		shapePromptWindow.display();
	}

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

					timesClicked++;

					if (timesClicked == numVertices)
					{
						if (numVertices == 3)
						{
							text.setString("Click on a fourth point\nto start the algorithm");
						}
						else if (numVertices == 5)
						{
							text.setString("Click on a sixth point\nto start the algorithm");
						}
					}

					if(vertices.size() < numVertices)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if(points.size() == 0)
					{
					///fourth click
					///push back to points vector
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
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
			Vector2f new_point = Vector2f(0.0, 0.0);
		    ///select random vertex
			Vector2f rand_vertex = vertices.at(rand() % numVertices);
		    ///calculate midpoint between random vertex and the last point in the vector
			new_point.x = (points.back().x + rand_vertex.x) / 2;
			new_point.y = (points.back().y + rand_vertex.y) / 2;
		    ///push back the newly generated coord.
			points.push_back(new_point);
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		if (timesClicked == 0 || timesClicked == numVertices) {
			
			window.draw(text);
		}
		else if (timesClicked > numVertices)
		{
			iterText.setString(to_string(points.size()));
			window.draw(iterText);
		}

		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(5,5));
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
