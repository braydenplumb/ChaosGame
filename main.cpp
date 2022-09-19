#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // rand()
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


// Pick Random Point on screen - for testing; NO LONGER IN USE
Vector2f pickRandomPoint()
{
    int rand_x = rand() % 1280;
    int rand_y = rand() % 720;
    return Vector2f(rand_x, rand_y);
}

// Generate Random Points - for testing; NO LONGER IN USE
void generateRandomPoints(vector<Vector2f> &points)
{
    for (int i = 0; i < 400; i++)
    {
        points.push_back(pickRandomPoint());
    }
}

// finds the next midpoint between one of the vertex and a point
Vector2f nextMidPoint(vector<Vector2f> &points, vector<Vector2f> &vertices, int vertexRand)
{
    Vector2f newPoint;
    
    int newX = (points.at(points.size() - 1).x + vertices.at(vertexRand).x) / 2;
    int newY = (points.at(points.size() - 1).y + vertices.at(vertexRand).y) / 2;
    /*debugging
    cout << "midpoint_x: " << newX << endl;
    cout << "midpoint_y: " << newY << endl << endl;
    */
    newPoint.x = newX;
    newPoint.y = newY;
    
    return newPoint;
}


int main()
{
    srand(time(NULL));

    // Open a 1280 x 720 window for the game
    RenderWindow window(VideoMode(1280, 720), "Chaos Game", Style::Default);

    // 
    window.setMouseCursorVisible(false);

    // Textbox for program greeting and game instruction text
    Color darkGray(50, 50, 50, 150);
    RectangleShape rect;
    rect.setSize(Vector2f(720, 150));
    rect.setPosition(0, 0);
    rect.setFillColor(darkGray);

    // Loads a font file as set it as the "mainFont"
    Font mainFont;
    mainFont.loadFromFile("fonts/VT323-Regular.ttf");

    // Program greeting text
    Text titleText;
    titleText.setFont(mainFont);
    titleText.setString("Welcome to the Chaos Game!");
    titleText.setCharacterSize(30);
    titleText.setFillColor(Color::White);
    titleText.setPosition(Vector2f(200, 10));

    // Game instruction text
    Text instructionText;
    instructionText.setFont(mainFont);
    instructionText.setString("Step 1: Click on any three points on the screen to create the vertices for the triangle\nStep 2: Click on a fourth point to start the algorithm\nStep 3: Chaos Ensues!\nPress Enter to Close Instructions");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(Color::White);
    instructionText.setPosition(Vector2f(10, 44));
    bool showText = true;

    // Create a texture to hold an arrow cursor graphic on the GPU
    Texture cursorTexture;
    cursorTexture.loadFromFile("graphics/arrow.png");
    // Create a Sprite and scale the object
    Sprite cursorSprite;
    cursorSprite.setTexture(cursorTexture);
    cursorSprite.setScale(3, 3);

    // First three points (vertices) that will make the initial triangle stored in here
    vector<Vector2f> vertices;
    // the rest of the points after the fourth input from user
    vector<Vector2f> points;

    int maxVertices = 3;
    bool gameActive = false;

    // Coordinate points from user's mouse click
    Vector2f clicked;

    // For testing use
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
        Vertex line[2];
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
                    cout << "***mouse LEFT button pressed***" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;

                    clicked.x = event.mouseButton.x;
                    clicked.y = event.mouseButton.y;
                    
                    if (vertices.size() == maxVertices)
                    {
                        gameActive = true;
                        showText = false;
                        points.push_back({ clicked.x, clicked.y });
                        line[0].position = Vector2f(vertices.at(0).x, vertices.at(0).y);
                        line[1].position = Vector2f(vertices.at(1).x, vertices.at(1).y);
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
        if (gameActive && points.size() < 5000)
        {
            // picks a number between 0-2 for vector index
            int randomVertex = rand() % 3;
            /*debugging
            cout << "random Vertex: " << randomVertex << endl;
            cout << "points size: " << points.size() << endl;
            cout << "points.x: " << points[points.size() - 1].x << endl;
            cout << "points.y: " << points[points.size() - 1].y << endl;
            cout << "vertices.x: " << vertices[randomVertex].x << endl;
            cout << "vertices.y: " << vertices[randomVertex].y << endl;
            */
            cout << "New Point: " << points.at(points.size() - 1).x << ", " << points.at(points.size() - 1).y << endl;
            Vector2f newPoint = nextMidPoint(points, vertices, randomVertex);
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

        // Draw a line between vertices
        window.draw(line, 2, Lines);
        
        
        /*// Distance between 2 vertices
        int distance = vertices.at(i)
        RectangleShape lines;
        lines.setFillColor(Color::Green);
        lines.setSize(Vector2f(vertices.at(0), 3));
        lines.setPosition(vertices.at(i)*/
        

        // Draw the Points
        for (int i = 1; i < points.size(); i++)
        {
            CircleShape circlePoint;
            circlePoint.setRadius(1.5);
            circlePoint.setPosition(points.at(i));
            window.draw(circlePoint);
            window.draw(circlePoint);
            window.draw(circlePoint);
            window.draw(circlePoint);
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