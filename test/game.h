#pragma once
#include <SFML\Graphics.hpp>
#include "ball.h"
#include "pauseMessage.h"
#include "paddle.h"
#include "menu.h"
#include <ctime>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace sf;

class Game
{
public:
	Ball pong;
	paddle left;
	paddle right;
	pauseMessage text;
	sf::Clock AITimer;
	sf::Clock clock;
	sf::Time AITime = sf::seconds(0.1f);
	int gameWidth = 800;
	int gameHeight = 600;
	float paddleSpeed;
	float rightPaddleSpeed;
	float ballSpeed;
	float ballAngle; 
	float pi;
	float increase;
	Menu list;
	bool isPlaying;
	bool isFirstTime;
	int mode = 0;
	Game();
	void run();
private:
	void processEvents();
	void update(int );
	void render();
private:
	sf::RenderWindow mWindow;
};
