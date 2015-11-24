#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
 * Compile line: g++ -std=c++14 main.cpp -o main.out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network
 */

using namespace std;
using namespace sf;

// 'constexpr' define um valor imutável em tempo de compilação
constexpr int windowWidth{800}, windowHeight{600};

int main () {

	// RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid -1");
	RenderWindow window({windowWidth,windowHeight}, "Arkanoid - 1");
	window.setFramerateLimit(60);

	// Loop do jogo
	while (window.isOpen()) {

		// Monitora os eventos e reage de acordo
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Key::Escape) {
				window.close();
			}
		}

		// Limpa a tela 
		window.clear(Color::Black);

		// Exibe os conteúdos da tela
		window.display();
	}

	return EXIT_SUCCESS;
}