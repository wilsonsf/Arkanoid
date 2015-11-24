#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
 * Compile line: g++ -std=c++14 main.cpp -o main.out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network
 */

using namespace std;
using namespace sf;

constexpr int windowWidth{800}, windowHeight{600};

int main () {

	// RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid -1");
	RenderWindow window({windowWidth,windowHeight}, "Arkanoid - 1");
	window.setFramerateLimit(60);

	while (true) {
		window.clear(Color::Black);

		if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

		window.display();
	}

	return EXIT_SUCCESS;
}