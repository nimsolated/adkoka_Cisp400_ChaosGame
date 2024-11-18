// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

bool inputVerticesIsInRange();
int keyCodeToVertices(int kc);
double getRatio(int nVertices);
void generatePoints(vector<Vector2f>& pointsVec, vector<Vector2f> verticesVec, int nVertices, double ratio);
RectangleShape basicRectShape(int w, int h, Color c);
void drawVerticesAndPoints(RenderWindow& window, vector<Vector2f> verticesVec, vector<Vector2f> pointsVec);
void handleFirstWindow(Text& verticesPromptText, unsigned int& numVertices, double& ratio);
void handleSecondWindow(Text& mainText, Text& iterText, unsigned int& timesClicked, unsigned int& numVertices, double& ratio);

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

int keyCodeToVertices(int kc)
{
	// cout << "Key Pressed: " << event.key.code << endl;

	if (kc >= 29 && kc <= 35) // if pressed Num3-Num9
	{
		return (kc - 26); // Offsets the keycode to get the correct number of Vertices
	}
	else if (kc >= 78 && kc <= 84) // if pressed Numpad3-Numpad9
	{
		return (kc - 75); // Offsets the keycode to get the correct number of Vertices
	}
	else
	{
		return -1; // For anything else, return -1
	}
}

double getRatio(int nVertices)
{
	switch (nVertices)
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

void generatePoints(vector<Vector2f>& pointsVec, vector<Vector2f> verticesVec, int nVertices, double ratio)
{
	/// Generate more point(s)
	Vector2f new_point = Vector2f();
	/// Select random vertex
	Vector2f rand_vertex = verticesVec.at(rand() % nVertices);
	/// Calculate midpoint between random vertex and the last point in the vector
	new_point.x = rand_vertex.x + ((pointsVec.back().x - rand_vertex.x) * ratio);
	new_point.y = rand_vertex.y + ((pointsVec.back().y - rand_vertex.y) * ratio);
	/// Push back the newly generated coord.
	pointsVec.push_back(new_point);
}

RectangleShape basicRectShape(int w, int h, Color c)
{
	RectangleShape rect(Vector2f(w, h));
	rect.setFillColor(c);
	return rect;
}

void drawVerticesAndPoints(RenderWindow& window, vector<Vector2f> verticesVec, vector<Vector2f> pointsVec)
{
	for (int i = 0; i < verticesVec.size(); i++)
	{
		RectangleShape rect = basicRectShape(5, 5, Color::White);
		rect.setPosition(Vector2f(verticesVec[i].x, verticesVec[i].y));
		window.draw(rect);
	}

	for (int i = 0; i < pointsVec.size(); i++)
	{
		RectangleShape rect = basicRectShape(1, 1, Color::White);
		rect.setPosition(Vector2f(pointsVec[i].x, pointsVec[i].y));
		window.draw(rect);
	}
}

void handleFirstWindow(Text& verticesPromptText, unsigned int& numVertices, double& ratio)
{
	// Create a video mode object
	VideoMode vm1(540, 270);
	// Create and open a gameWindow for the vertices prompt window
	RenderWindow verticesPromptWindow(vm1, "Vertices Prompt", Style::Default);

	// Loop while window is open
	while (verticesPromptWindow.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (verticesPromptWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				verticesPromptWindow.close();
			}

			if (event.type == Event::KeyPressed)
			{
				if (inputVerticesIsInRange())
				{
					// Assign numVertices based on which number key was pressed
					int keyCode = event.key.code;
					numVertices = keyCodeToVertices(keyCode); // Equals to -1 if there was an error in the keyCodeToVertices function

					if (numVertices == -1)
					{
						std::cout << "Error on setting # of Vertices." << std::endl;
						return;
					}

					ratio = getRatio(numVertices); // Assign ratio based on number of Vertices

					verticesPromptWindow.close();
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			verticesPromptWindow.close();
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		verticesPromptWindow.draw(verticesPromptText);
		verticesPromptWindow.display();
	}
}

void handleSecondWindow(Text& mainText, Text& iterText, unsigned int& timesClicked, unsigned int& numVertices, double& ratio)
{
	// Declaring the vectors to hold vertices and points
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	// Set mainText's string to the correct value
	mainText.setString("Create your vertices by clicking\n" + to_string(numVertices) + " points in this windows");

	// Create a video mode object
	VideoMode vm2(1080, 1080);
	// Create and open a window for the game
	RenderWindow gameWindow(vm2, "Chaos Game!! - By Armin and Daniel", Style::Default);

	// Loop while window is open
	while (gameWindow.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the game's window is closed
				gameWindow.close();
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
						mainText.setString("Click on a " + to_string(numVertices + 1) + "th point\nto start the algorithm");
					}

					if (vertices.size() < numVertices)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
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
			gameWindow.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			generatePoints(points, vertices, numVertices, ratio);
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		gameWindow.clear();

		if (timesClicked == 0 || timesClicked == numVertices) {

			gameWindow.draw(mainText);
		}
		else if (timesClicked > numVertices)
		{
			iterText.setString(to_string(points.size()));
			gameWindow.draw(iterText);
		}

		drawVerticesAndPoints(gameWindow, vertices, points);

		gameWindow.display();
	}
}

int main()
{
	// Declaring and initializing variables
	// needed for conditions and calculations
	unsigned int timesClicked = 0;
	unsigned int numVertices = 0;
	double ratio = 0.5;

	/*
	****************************************
	Set the font and text properties
	****************************************
	*/

	// For the font used for all texts
	string fontName = "SuperShiny-0v0rG.ttf";
	Font font;

	if (!font.loadFromFile(fontName))
	{
		return -1;
	}

	// For the first window's prompt
	sf::Text verticesPromptText;
	verticesPromptText.setFont(font);
	verticesPromptText.setString("Number of Vertices:\nPress a number\nin range 3 to 9\n\nBy Armin and Daniel");
	verticesPromptText.setCharacterSize(40);
	verticesPromptText.setFillColor(sf::Color::Cyan);
	verticesPromptText.setStyle(sf::Text::Style::Regular);
	verticesPromptText.setPosition(20, 20);

	// For the second window's main text
	sf::Text mainText;
	mainText.setFont(font);
	mainText.setString("");
	mainText.setCharacterSize(48);
	mainText.setFillColor(sf::Color::Cyan);
	mainText.setStyle(sf::Text::Style::Bold);
	mainText.setPosition(120, 60);

	// For the second window's # of iterations text
	sf::Text iterText;
	iterText.setFont(font);
	iterText.setString("0");
	iterText.setCharacterSize(32);
	iterText.setFillColor(sf::Color::Cyan);
	iterText.setStyle(sf::Text::Style::Regular);
	iterText.setPosition(32, 48);

	// Handle first window (# of vertices prompt window)
	handleFirstWindow(verticesPromptText, numVertices, ratio);

	// Check if numVertices was set incorrectly. If so, terminate the program.
	if (numVertices == -1) { return -1; }

	// Handle second window (game's window)
	handleSecondWindow(mainText, iterText, timesClicked, numVertices, ratio);
}
