#include "Snake.h"

void Snake::Reset()
{
	Snake::length = 4; snake[0].x = w/2; snake[0].y = h/2;
	for(int i = 1; i < Snake::length; ++i){
		snake[i].x = snake[i-1].x-1;
		snake[i].y = snake[i-1].y;
	}
	dir = 0;
	return;
}
void Snake::Move()
{
	if(dir == 0){return;}
	for(int i = length; i > 0; --i){
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	switch(dir){
		case 1: 
		{
			snake[0].y += 1; // Down
			directed = Direction::Down;
		} break;		
		case 2:
		{
			snake[0].y -= 1; // Up
			directed = Direction::Up;
		} break;
		case 3:
		{
			snake[0].x -= 1; // Right
			directed = Direction::Right;
		} break;
		case 4:
		{
			snake[0].x += 1; // Left	
			directed = Direction::Left;
		} break;
	}
	
	if(snake[0].x == fruit.x && snake[0].y == fruit.y){
		++length;
		fruit.x = rand() % w;
		fruit.y = rand() % h;
	}
	for(int i = 1; i < length; ++i){
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){
			length = 4;
		}
	}
	if((snake[0].x < 0) || (snake[0].y < 0) || (snake[0].x > w) || (snake[0].y > h)){
		current_state = States::game_over;
	}
	/*if(snake[0].x < 0){ Reset(); }
	if(snake[0].y < 0){ Reset(); }
	if(snake[0].x > w){ Reset(); }
	if(snake[0].y > h){ Reset(); }*/
}