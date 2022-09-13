#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Chaos Game");

    RectangleShape rect;
    rect.setSize(Vector2f(200, 200));
    rect.setPosition(100, 100);

    RectangleShape rect_2;
    rect_2.setSize(Vector2f(300, 300));
    rect_2.setPosition(150, 150);
    rect_2.setFillColor(Color::Green);

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
        }

        /*
        ##############################
        Update the Window Draw
        ##############################
        */

        window.clear();
        
        window.draw(rect_2);
        window.draw(rect);

        window.display();
    }

    return 0;
}