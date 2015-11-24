#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
 * Compile line: g++ -std=c++11 main.cpp -o main.out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network

 * g++ -std=c++11 -c main.cpp -I/home/agil5393/SFML/include
 * g++ -std=c++11 main.o -o arkanoid.out -L/home/agil5393/SFML/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network
 */

// 'constexpr' define um valor imutável em tempo de compilação
constexpr int windowWidth{800}, windowHeight{600};
constexpr float ballRadius{10.f}, ballVelocity{8.f};
constexpr float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{6.f};

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
	void update () { 
		shape.move (velocity); 

		// Pra manter a bola dentro da tela, precisamos testar se está nas 
		// extremidades da tela e inverter sua velocidade
		if (left() < 0 || right() > windowWidth) velocity.x *= -1;
		if (top() < 0 || bottom() > windowHeight) velocity.y *= -1;
	}

	// (0,0) é no topo da esquerda
	float x()				{ return shape.getPosition().x; }
	float y() 			{	return shape.getPosition().y; }
	float left() 		{ return x() - shape.getRadius();	}
	float right() 	{ return x() + shape.getRadius();	}
	float top() 		{	return y() - shape.getRadius();	}
	float bottom () {	return y() + shape.getRadius();	}
};

class Paddle {
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;

	Paddle(float mX, float mY) {
		shape.setPosition(mX, mY);
		shape.setSize({paddleWidth, paddleHeight});
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(paddleWidth /2.f, paddleHeight /2.f );
	}

	void update () {
		shape.move(velocity);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
					&& left() > 0) velocity.x = -paddleVelocity;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
					&& right() < windowWidth) velocity.x = paddleVelocity;
		
		else 
			velocity.x = 0;
	}

	float x()				{ return shape.getPosition().x; }
	float y() 			{	return shape.getPosition().y; }
	float left() 		{ return x() - shape.getSize().x / 2.f;	}
	float right() 	{ return x() + shape.getSize().x / 2.f;	}
	float top() 		{	return y() - shape.getSize().y / 2.f;	}
	float bottom () {	return y() + shape.getSize().y / 2.f;	}
};

// Checa se dois objetos estão se sobrepondo
template <class T1, class T2> bool isIntersecing (T1& mA, T2& mB) {
	return  mA.right() >= mB.left() && mA.left() <= mB.right()
					&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall) {
	if (!isIntersecing(mPaddle, mBall)) return;

	mBall.velocity.y = -ballVelocity;

	if (mBall.x() < mPaddle.x()) 
		mBall.velocity.x = -ballVelocity;
	else 
		mBall.velocity.x = ballVelocity;
}

int main () {
	Ball ball{windowWidth / 2, windowHeight /2 };
	Paddle paddle {windowWidth / 2, windowHeight - 50};

	sf::RenderWindow window({windowWidth,windowHeight}, "Arkanoid - 5");
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
		paddle.update();

		// testa colisão a cada ciclo
		testCollision(paddle, ball);

		window.draw(ball.shape);
		window.draw(paddle.shape);

		// Exibe os conteúdos da tela
		window.display();
	}

	return EXIT_SUCCESS;
}
