#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
 * Compile line: g++ -std=c++14 main.cpp -o main.out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network
 */

using namespace std;
// using namespace sf;

// 'constexpr' define um valor imutável em tempo de compilação
constexpr int windowWidth{800}, windowHeight{600};
constexpr float ballRadius{10.f}, ballVelocity{8.f};

class Ball {
public:
	sf::CircleShape shape;

	// Vetor bidimensional que armazena a velocidade.
	sf::Vector2f velocity {-ballVelocity, -ballVelocity};

	Ball(float mX, float mY) {
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(ballRadius, ballRadius);
	}

	// Atualiza o objeto movendo com a velocidade atual;
	void update () { shape.move (velocity); }
};

int main () {
	Ball ball{windowWidth / 2, windowHeight /2 };


	// RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid -1");
	sf::RenderWindow window({windowWidth,windowHeight}, "Arkanoid - 1");
	window.setFramerateLimit(60);

	// Loop do jogo
	while (window.isOpen()) {

		// Monitora os eventos e reage de acordo
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape) {
				window.close();
			}
		}

		// Limpa a tela 
		window.clear(sf::Color::Black);

		// Renderiza os objetos na tela
		ball.update();
		window.draw(ball.shape);


		// Exibe os conteúdos da tela
		window.display();
	}

	return EXIT_SUCCESS;
}