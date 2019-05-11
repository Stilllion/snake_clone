#ifndef Game_h
#define Game_h
#include "Snake.h"

using namespace sf;
struct Game
{
	Game();
	Snake s;
	
	void Update();
	void HandleInput();
	void Render();
	
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Font font;
	//Buttons
	sf::RectangleShape restart_btn;
	// TEXT
	sf::Text pause_text;
	sf::Text game_over_text;
	sf::Text restart_text;
	
	
	bool was_released = true;
	
	float frametime = 1.0/15.0;
	static const int tileSize = 16;
	int w = 40;
	int h = 30;
	sf::Texture backGround_texture;
	sf::Texture snakePiece_texture;
	sf::Texture apple_texture;
	
	sf::Sprite backGround;
	sf::Sprite snakePiece;
	sf::Sprite apple;
	
	
};

#endif