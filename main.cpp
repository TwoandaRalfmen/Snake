#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

struct sSSegment
{
	int x;
	int y;
};

const int nScreenWidth = 1200;
const int nScreenHeight = 1200;
const int loop_pause = 100;

const int snake_size = 50;
const sf::Color snake_color = sf::Color::Color(70, 115, 232);
const sf::Color BG_color = sf::Color::Color(170, 215, 81);
std::list<sSSegment> snake = { {700, 600}, {750, 600}, {800, 600}, {850, 600}, {900, 600} };
int snake_direction = 3;
bool Dead = false;
int nScore = 0;

const sf::Color food_color = sf::Color::Color(231, 71, 29);
int nfoodX = 300;
int nfoodY = 800;

int main(){
	
	sf::RenderWindow window(sf::VideoMode(nScreenWidth, nScreenHeight), "Snake");

	//game loop
	while (window.isOpen()){
		
		//timing and event handling
		sf::sleep(sf::Time(sf::milliseconds(loop_pause)));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
			else if (event.type == sf::Event::KeyPressed) {

				if (Dead && event.key.code == sf::Keyboard::Space) {

					nScore = 0;
					nfoodX = 300;
					nfoodY = 800;
					snake_direction = 3;
					snake = { {700, 600}, {750, 600}, {800, 600}, {850, 600}, {900, 600} };
					Dead = false;
				}

				switch (event.key.code) {
				case sf::Keyboard::W:
					snake_direction = 0;
					break;
				case sf::Keyboard::A:
					snake_direction = 3;
					break;
				case sf::Keyboard::S:
					snake_direction = 2; 
					break;
				case sf::Keyboard::D:
					snake_direction = 1;
					break;
				}
			}
		}
		
	if (!Dead) {

		window.clear(BG_color);

		//game logic
		
		// update snake position

		switch (snake_direction) {
		case 0: //Up
			snake.push_front({ snake.front().x, snake.front().y - snake_size });
			break;
		case 1: //Right
			snake.push_front({ snake.front().x + snake_size, snake.front().y });
			break;
		case 2: //Down
			snake.push_front({ snake.front().x, snake.front().y + snake_size });
			break;
		case 3: //Left
			snake.push_front({ snake.front().x -snake_size, snake.front().y });
			break;
		}
		
		// collision detection

		if (snake.front().x < 0 || snake.front().y + snake_size > nScreenWidth)
			Dead = true;
		if (snake.front().y < 0 || snake.front().x + snake_size > nScreenHeight)
			Dead = true;

		bool newFoodPosFound = false;

		if (snake.front().x == nfoodX && snake.front().y == nfoodY) {

			nScore++;

			while (!newFoodPosFound) {

				nfoodX = (rand() % (nScreenWidth / 50)) * 50;
				nfoodY = (rand() % (nScreenHeight / 50)) * 50;

				if (snake.front().x != nfoodX && snake.front().y != nfoodY)
					newFoodPosFound = true;

				for (auto s : snake) {

					if (s.x != nfoodX && s.y != nfoodY && newFoodPosFound)

						newFoodPosFound = true;

					else {

						newFoodPosFound = false;
					}
				}
			}
			snake.push_back({ snake.back().x, snake.back().y });
		}

		for (std::list<sSSegment>::iterator i = snake.begin(); i != snake.end(); i++) {
			
			if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y)
				Dead = true;
		}

		//destroy tail
		snake.pop_back();

		//render and display

		//draw snake
		for (auto s : snake) {
			sf::RectangleShape part;
			part.setPosition(s.x, s.y);
			part.setSize(sf::Vector2f(snake_size, snake_size));
			part.setFillColor(snake_color);
			window.draw(part);
		}

		//draw food
		sf::RectangleShape food_shape;
		food_shape.setPosition(nfoodX, nfoodY);
		food_shape.setFillColor(food_color);
		food_shape.setSize(sf::Vector2f(snake_size, snake_size));
		window.draw(food_shape);
		
	}
	else {

		sf::Font font;
		font.loadFromFile("Fonts/Roboto-Light.ttf");
		sf::Text txt;
		txt.setString("Your Score: " + std::to_string(nScore));
		txt.setCharacterSize(84);
		txt.setFillColor(sf::Color::Black);
		txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
		txt.setPosition(nScreenWidth/2, nScreenHeight/2);
		window.draw(txt);
		std::cout << "Printed font";

		}
		window.display();
	}

	
}