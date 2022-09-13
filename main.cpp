#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
//#include <SFML/Mouse.hpp>

using namespace std;
using namespace sf;

int main()
{
    // Create and open a window for the game
    RenderWindow window(VideoMode(1920, 1080), "Chaos Game", Style::Default);
    RectangleShape rect(Vector2f{50, 50});

    // First three points stored in here
    vector<Vector2f> vertices;
    // the rest of the points after the fourth input from user
    vector<Vector2f> points;

    Vector2f clicked;
    Vector2f fourthClick;

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
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "!left mouse button pressed!" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;

                    clicked.x = event.mouseButton.x;
                    clicked.y = event.mouseButton.y;

                    vertices.push_back({clicked.x, clicked.y});
                    
                    

                }
            }
        }
        

        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

        /*
        ##############################
        Update the Window Draw
        ##############################
        */
        rect.setPosition(clicked.x, clicked.y);
        rect.setFillColor(Color::Magenta);

        /*
        ##############################
        Draw the Window Draw
        ##############################
        */
        window.clear();

        window.draw(rect);
        // loop through your vectors and draw each coordinate
        // window.draw();

        window.display();

    }

    return 0;
}