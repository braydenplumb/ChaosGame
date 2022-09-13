#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Chaos Game");

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
        window.display();
    }

    return 0;
}