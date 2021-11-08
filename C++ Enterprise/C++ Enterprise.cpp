#include <iostream>
#include <SFML/Graphics.hpp>

void ShipMovement(sf::CircleShape& ship, float deltaTime);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Enterprise");
    window.setVerticalSyncEnabled(true);

    sf::CircleShape ship(30.0f,30);
    ship.setPosition(sf::Vector2f(400.0f, 300.0f));

    sf::Clock clock;
    
    while (window.isOpen()) {
        // Inputs
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            // Process any input event here
            switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				default:
					break;
			}
        }

        // Logique
        sf::Time elapsedTime = clock.restart();
        ShipMovement(ship, elapsedTime.asSeconds());

        // Rendu
        window.clear();

        window.draw(ship);

        window.display();
    }
}

void ShipMovement(sf::CircleShape& ship, float deltaTime)
{
    float speed = 300.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		ship.move(sf::Vector2f(0.f, -speed * deltaTime));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		ship.move(sf::Vector2f(0.f, speed * deltaTime));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		ship.move(sf::Vector2f(-speed * deltaTime, 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		ship.move(sf::Vector2f(speed * deltaTime, 0.f));
}