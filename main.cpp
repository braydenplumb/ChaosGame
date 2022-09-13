#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Chaos Game");

    RectangleShape rect;
    rect.setSize(Vector2f(340, 200));
    rect.setPosition(0, 0);

    Font mainFont;
    mainFont.loadFromFile("fonts/VT323-Regular.ttf");

    Text instructionText;
    instructionText.setFont(mainFont);
    instructionText.setString("Welcome to the Chaos Game!");
    instructionText.setCharacterSize(30);
    instructionText.setColor(Color::Black);
    instructionText.setPosition(Vector2f(10, 10));
    bool showText = true;

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

        if (showText)
        {
            window.draw(rect);
            window.draw(instructionText);
        }

        window.display();
    }

    return 0;
}