#ifndef Snake_h
#define Snake_h
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Snake.h"
#include "states.h"
#include <vector>

using namespace sf;

struct Snake
{
	States current_state;
	
	std::vector<sf::Vector2i> snake;
	int length;
	sf::Vector2i fruit;
	// Window size in Tiles
	int w = 40;
	int h = 30;
	enum Direction 
	{
	 None, Up, Down, Left, Right
	};	
	int dir = 0;
	Direction directed = Direction::None;
	Snake(){
		length = 4;
		for(int i = 0; i < 100; ++i){
			sf::Vector2i tile(i, 0);
			snake.push_back(tile);
		}
		
		snake[0].x = w/2;
		snake[0].y = h/2;
		fruit.x = rand() % w;
		fruit.y = rand() % h;
		
		for(int i = 1; i < length; ++i){
			snake[i].x = snake[i-1].x-1;
			snake[i].y = snake[i-1].y;
		}
	}
	void Move();
	void Reset();
};

#endif /* Snake_h */