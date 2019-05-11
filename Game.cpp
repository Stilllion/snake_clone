#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(640, 480), "Snake!");
	srand(time(0));
	window.setVerticalSyncEnabled(true);

	snakePiece_texture.loadFromFile("green.png");
	backGround_texture.loadFromFile("white.png");
	apple_texture.loadFromFile("red.png");
	
	// Buttons
	restart_btn.setSize(sf::Vector2f(70, 20));
	
	// TEXT
	font.loadFromFile("Roboto-Regular.ttf");
	pause_text.setFont(font);
	pause_text.setCharacterSize(50);
	pause_text.setFillColor(sf::Color::Red);

	pause_text.setString("Paused");
	pause_text.setOrigin(pause_text.getLocalBounds().width/2, pause_text.getLocalBounds().height/2);
	pause_text.setPosition(640/2, 480/2-70);
	game_over_text = pause_text;
	game_over_text.setString("Game Over!");
	game_over_text.setOrigin(game_over_text.getLocalBounds().width/2, game_over_text.getLocalBounds().height/2);
	game_over_text.setPosition(640/2, 480/2-70);
	
	restart_text = pause_text;
	restart_text.setCharacterSize(15);
	restart_text.setString("Restart!");
	restart_text.setOrigin(restart_text.getLocalBounds().width/2, restart_text.getLocalBounds().height/2);
	restart_text.setPosition(640/2, 480/2-5);

	

	
	
	backGround.setTexture(backGround_texture);
	snakePiece.setTexture(snakePiece_texture);
	apple.setTexture(apple_texture);
	s.current_state = States::game_state;
	clock.restart();
}
void Game::Update()
{
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
		}
	}
	if(elapsed.asSeconds() >= frametime && s.current_state == States::game_state){
		s.Move();
		elapsed -= sf::seconds(frametime);
	}
	apple.setPosition(s.fruit.x*16, s.fruit.y*16);	
}

void Game::HandleInput()
{
	if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)){
			was_released = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)){
		if(s.current_state == States::game_state && was_released){
			s.current_state = States::pause_state;
			was_released = false;
			return;
		}
		if(s.current_state == States::pause_state && was_released){
			s.current_state = States::game_state;
			was_released = false;
			elapsed -= elapsed;
			return;
		}

	}
	// Cpntrolling snake
	if(Keyboard::isKeyPressed(Keyboard::Down) && s.directed != s.Direction::Up){s.dir = 1;}
	if(Keyboard::isKeyPressed(Keyboard::Up) && s.directed != s.Direction::Down){s.dir = 2;}
	if(Keyboard::isKeyPressed(Keyboard::Left) && s.directed != s.Direction::Left){s.dir = 3;}
	if(Keyboard::isKeyPressed(sf::Keyboard::Right) && s.directed != s.Direction::Right){s.dir = 4;}
	
	
	// Mouse input
	if(restart_btn.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){
		restart_btn.setOutlineThickness(2);
		restart_btn.setOutlineColor(sf::Color(0, 0, 0));
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && s.current_state == States::game_over){
			s.Reset();
			s.current_state = States::game_state;
		}
	} else {restart_btn.setOutlineThickness(0);}
}

void Game::Render()
{
	window.clear();

	for(int i = 0; i < w; ++i){
		for(int j = 0; j < h; ++j){
			backGround.setPosition(i*tileSize, j*tileSize);
			window.draw(backGround);
		}
	}
	for(int i = 0; i < s.length; ++i){
		snakePiece.setPosition(s.snake[i].x*tileSize, s.snake[i].y*tileSize);
		window.draw(snakePiece);	
	}
	window.draw(apple);
	if(s.current_state == States::pause_state){
		sf::RectangleShape pause_screen(sf::Vector2f(w*16, h*16));
		pause_screen.setFillColor(sf::Color(220, 220, 220, 200));
		window.draw(pause_screen);
		window.draw(pause_text);
	}
	if(s.current_state == States::game_over){
		restart_btn.setOrigin(70/2, 20/2);
		restart_btn.setPosition(640/2, 480/2);
		restart_btn.setFillColor(sf::Color(255, 255, 255));
		
		sf::RectangleShape pause_screen(sf::Vector2f(w*16, h*16));
		pause_screen.setFillColor(sf::Color(220, 220, 220, 200));
		window.draw(pause_screen);
		window.draw(restart_btn);
		window.draw(restart_text);
		window.draw(game_over_text);
	}
	window.display();
}