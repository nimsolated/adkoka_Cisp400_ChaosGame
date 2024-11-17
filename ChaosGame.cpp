// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

bool inputVerticesIsInRange()
{
	return (
		Keyboard::isKeyPressed(Keyboard::Num3) ||
		Keyboard::isKeyPressed(Keyboard::Num4) ||
		Keyboard::isKeyPressed(Keyboard::Num5) ||
		Keyboard::isKeyPressed(Keyboard::Num6) ||
		Keyboard::isKeyPressed(Keyboard::Num7) ||
		Keyboard::isKeyPressed(Keyboard::Num8) ||
		Keyboard::isKeyPressed(Keyboard::Num9) ||
		Keyboard::isKeyPressed(Keyboard::Numpad3) ||
		Keyboard::isKeyPressed(Keyboard::Numpad4) ||
		Keyboard::isKeyPressed(Keyboard::Numpad5) ||
		Keyboard::isKeyPressed(Keyboard::Numpad6) ||
		Keyboard::isKeyPressed(Keyboard::Numpad7) ||
		Keyboard::isKeyPressed(Keyboard::Numpad8) ||
		Keyboard::isKeyPressed(Keyboard::Numpad9)
		);
}

double getRatio(int n)
{
	switch (n)
	{
	case 3:
	case 4:
		return 0.5;
		break;
	case 5:
		return 0.381966;
		break;
	case 6:
		return 0.333333;
		break;
	case 7:
		return 0.307979;
		break;
	case 8:
		return 0.292893;
		break;
	case 9:
		return 0.257773;
		break;
	default:
		return 0.5;
		break;
	}
}

int main()
{
	// Create a video mode object
	VideoMode vm1(540, 270);
	// Create and open a window for the vertices prompt window
	RenderWindow verticesPromptWindow(vm1, "Vertices Prompt", Style::Default);
	
	Font font;

	if (!font.loadFromFile("SuperShiny-0v0rG.ttf"))
	{
		return -1;
	}

	vector<Vector2f> vertices;
	vector<Vector2f> points;
	
	int unsigned timesClicked = 0;
	int unsigned numVertices = 0;
	double ratio = 0.0;

	sf::Text verticesPrompt;
	verticesPrompt.setFont(font);
	verticesPrompt.setString("Number of Vertices:\nPress a number\nin range 3 to 9");
	verticesPrompt.setCharacterSize(48);
	verticesPrompt.setFillColor(sf::Color::Cyan);
	verticesPrompt.setStyle(sf::Text::Regular);
	verticesPrompt.setPosition(54, 54);

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

	/*
	cout << "Num3: " << Keyboard::Num3 << endl;
	cout << "Num9: " << Keyboard::Num9 << endl;
	cout << "Numpad3: " << Keyboard::Numpad3 << endl;
	cout << "Numpad9: " << Keyboard::Numpad9 << endl;
	cout << "Num3 - 26: " << Keyboard::Num3 - 26 << endl;
	cout << "Num9 - 26: " << Keyboard::Num9 - 26 << endl;
	cout << "Numpad3 - 75: " << Keyboard::Numpad3 - 75 << endl;
	cout << "Numpad9 - 75: " << Keyboard::Numpad9 - 75 << endl;
	*/

	while (verticesPromptWindow.isOpen())
	{
		// Handle input
		Event event;
		while (verticesPromptWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				verticesPromptWindow.close();
			}

			if (event.type == Event::KeyPressed)
			{
				cout << "Key Pressed: " << event.key.code << endl;

				if (inputVerticesIsInRange())
				{
					// Assign numVertices based on which number key was pressed
					int key = event.key.code;
					if (key >= 29 && key <= 35) // if pressed Num3-Num9
					{
						numVertices = event.key.code - 26; // Offsets the keycode to get the correct number of Vertices
					}
					else if (key >= 78 && key <= 84) // if pressed Numpad3-Numpad9
					{
						numVertices = event.key.code - 75; // Offsets the keycode to get the correct number of Vertices
					}
					
					ratio = getRatio(numVertices); // Assign ratio based on number of Vertices

					text.setString("Create your vertices by clicking\n" + to_string(numVertices) + " points in this windows");
					verticesPromptWindow.close();
				}
			}
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			verticesPromptWindow.close();
		}

		// Draw
		verticesPromptWindow.draw(verticesPrompt);
		verticesPromptWindow.display();
	}

	// Create a video mode object
	VideoMode vm2(1080, 1080);
	// Create and open a window for the game
	RenderWindow window(vm2, "Chaos Game!!", Style::Default);

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
						text.setString("Click on a " + to_string(numVertices + 1) + "th point\nto start the algorithm");
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
	
		if (points.size() > 0)
		{
			/// Generate more point(s)
			Vector2f new_point = Vector2f();
			/// Select random vertex
			Vector2f rand_vertex = vertices.at(rand() % 5);
			/// Calculate midpoint between random vertex and the last point in the vector
			new_point.x = rand_vertex.x + ((points.back().x - rand_vertex.x) * ratio);
			new_point.y = rand_vertex.y + ((points.back().y - rand_vertex.y) * ratio);
			/// Push back the newly generated coord.
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
