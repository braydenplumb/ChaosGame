#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Chaos Game");

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

    vector<Vector2f> vertices;

    // Generate Random Points - for testing
    srand(time(NULL));
    for (int i = 0; i < 400; i++)
    {
        int rand_x = rand() % 1280;
        int rand_y = rand() % 720;
        vertices.push_back(Vector2f(rand_x, rand_y));
    }

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
                window.close();
            
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter)
                    showText = !showText;
            }
        }

        /*
        ##############################
        Update the Scene
        ##############################
        */


        /*
        ##############################
        Draw the Scene
        ##############################
        */

        window.clear();

        // Draws the Points
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rectPoint;
            rectPoint.setSize(Vector2f(1, 1));
            rectPoint.setPosition(vertices.at(i));
            window.draw(rectPoint);
        }

        if (showText)
        {
            window.draw(rect);
            window.draw(titleText);
            window.draw(instructionText);
        }

        window.display();
    }

    return 0;
}