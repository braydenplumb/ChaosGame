#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Vector2f pickRandomPoint()
{
    int rand_x = rand() % 1280;
    int rand_y = rand() % 720;
    return Vector2f(rand_x, rand_y);
}

// Generate Random Points - for testing
void generateRandomPoints(vector<Vector2f> &points)
{
    for (int i = 0; i < 400; i++)
    {
        points.push_back(pickRandomPoint());
    }
}

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1280, 720), "Chaos Game", Style::Default);

    window.setMouseCursorVisible(false);

    Color darkGray(50, 50, 50, 150);
    RectangleShape rect;
    rect.setSize(Vector2f(720, 150));
    rect.setPosition(0, 0);
    rect.setFillColor(darkGray);

    Font mainFont;
    mainFont.loadFromFile("fonts/VT323-Regular.ttf");

    Text titleText;
    titleText.setFont(mainFont);
    titleText.setString("Welcome to the Chaos Game!");
    titleText.setCharacterSize(30);
    titleText.setColor(Color::White);
    titleText.setPosition(Vector2f(200, 10));

    Text instructionText;
    instructionText.setFont(mainFont);
    instructionText.setString("Step 1: Click on any three points on the screen to create the vertices for the triangle\nStep 2: Click on a fourth point to start the algorithm\nStep 3: Chaos Ensues!\nPress Enter to Close Instructions");
    instructionText.setCharacterSize(20);
    instructionText.setColor(Color::White);
    instructionText.setPosition(Vector2f(10, 44));
    bool showText = true;

    Texture cursorTexture;
    cursorTexture.loadFromFile("graphics/arrow.png");

    Sprite cursorSprite;
    cursorSprite.setTexture(cursorTexture);
    cursorSprite.setScale(3, 3);

    // First three points stored in here
    vector<Vector2f> vertices;
    // the rest of the points after the fourth input from user
    vector<Vector2f> points;

    int maxVertices = 3;
    bool gameActive = false;

    Vector2f clicked;
    Vector2f fourthClick;

    //generateRandomPoints(vertices);

    // Main while-loop which loops forever until the game is exited
    while (window.isOpen())
    {
        /*
        ##############################
        Handle User Input
        ##############################
        */
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                {
                    window.close();
                }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && !gameActive)
                {
                    cout << "!left mouse button pressed!" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;

                    clicked.x = event.mouseButton.x;
                    clicked.y = event.mouseButton.y;
                    
                    if (vertices.size() == maxVertices)
                    {
                        gameActive = true;
                        showText = false;
                        points.push_back({ clicked.x, clicked.y });
                    }
                    else
                    {
                        vertices.push_back({ clicked.x, clicked.y });
                    }

                }
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter)
                    showText = !showText;
            }
        }
        

        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

        /*
        ##############################
        Update the Scene
        ##############################
        */

        // Update Cursor Graphic
        cursorSprite.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

        // Chaos Point Placing
        if (gameActive && points.size() < 2000)
        {
            cout << "New Point: " << points.at(points.size() - 1).x << ", " << points.at(points.size() - 1).y << endl;
            Vector2f newPoint = pickRandomPoint(); // Where the midpoint finder function will go. Right now I just pick random points on the screen.
            points.push_back(newPoint);
        }

        /*
        ##############################
        Draw the Scene
        ##############################
        */

        // Clear the Window
        window.clear();

        // Draw the Vertices
        for (int i = 0; i < vertices.size(); i++)
        {
            CircleShape circlePoint;
            circlePoint.setFillColor(Color::Green);
            circlePoint.setRadius(3);
            circlePoint.setOrigin(3, 3);
            circlePoint.setPosition(vertices.at(i));
            window.draw(circlePoint);
        }

        // Draw the Points
        for (int i = 1; i < points.size(); i++)
        {
            CircleShape circlePoint;
            circlePoint.setRadius(0.5);
            circlePoint.setPosition(points.at(i));
            window.draw(circlePoint);
        }

        // Draw Instruction Panel
        if (showText)
        {
            window.draw(rect);
            window.draw(titleText);
            window.draw(instructionText);
        }

        // Draw the Cursor
        window.draw(cursorSprite);

        // Display Draw Buffer
        window.display();

    }

    return 0;
}