#include "game.h"

Game::Game()
	:mWindow(sf::VideoMode(gameWidth,gameHeight , 32), "PongGame", sf::Style::Titlebar | sf::Style::Close)
{
	isPlaying = false;
	AITime = sf::seconds(0.1f);
	paddleSpeed = 400.f;
	rightPaddleSpeed = 0.f;
	ballSpeed = 500.f;
	ballAngle = 0.f;
	increase = 40.f;
	pi = 3.14159f;
	isFirstTime = true;
}

void Game::run()
{
	mWindow.setVerticalSyncEnabled(true);
	isPlaying = false;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	while (mWindow.isOpen())
	{
		processEvents();
		update(mode);
		render();
	}
}
void Game::update(int mode)
{
	if (isPlaying)
	{
		if (mode == 1)
		{
			float deltaTime = clock.restart().asSeconds();

			// Move the player's paddle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				(left.Paddle.getPosition().y - paddleSize.y / 2 > 5.f))
			{
				left.Paddle.move(0.f, -paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				(left.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
			{
				left.Paddle.move(0.f, paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				(right.Paddle.getPosition().y - paddleSize.y / 2 > 5.f))
			{
				right.Paddle.move(0.f, -paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				(right.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
			{
				right.Paddle.move(0.f, paddleSpeed * deltaTime);
			}

			// Move the ball
			float factor = ballSpeed * deltaTime;
			this->pong.ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

			// Check collisions between the ball and the screen
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < 0.f)
			{
				isPlaying = false;
				text.message.setString("P2 won!!!\nPress space to restart or\nescape to exit");
				text.message.setFillColor(sf::Color::Blue);
				ballSpeed = 500.f;
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth)
			{
				isPlaying = false;
				text.message.setString("P1 won!\nPress space to restart or\nescape to exit");
				text.message.setFillColor(sf::Color::Blue);
				ballSpeed = 500.f;
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{

				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.1f);
			}
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, gameHeight - this->pong.ballRadius - 0.1f);
			}

			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < left.Paddle.getPosition().x + paddleSize.x / 2 &&
				this->pong.ball.getPosition().x - this->pong.ballRadius > left.Paddle.getPosition().x&&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= left.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y - this->pong.ballRadius <= left.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().y > this->left.Paddle.getPosition().y)
				{
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}	
				else
				{
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}
				this->pong.ball.setPosition(this->left.Paddle.getPosition().x + this->pong.ballRadius + paddleSize.x / 2 + 0.1f, this->pong.ball.getPosition().y);
			}

			// Right Paddle
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > this->right.Paddle.getPosition().x - paddleSize.x / 2 &&
				this->pong.ball.getPosition().x + this->pong.ballRadius < this->right.Paddle.getPosition().x &&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= this->right.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y - this->pong.ballRadius <= this->right.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().y > this->right.Paddle.getPosition().y)
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
				}
				else
				{
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}

				this->pong.ball.setPosition(this->right.Paddle.getPosition().x - this->pong.ballRadius - paddleSize.x / 2 - 0.1f, this->pong.ball.getPosition().y);
			}
		}
		if (mode == 0)
		{
			float deltaTime = clock.restart().asSeconds();

			// Move the player's paddle
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				(left.Paddle.getPosition().y - paddleSize.y / 2 > 5.f))
			{
				left.Paddle.move(0.f, -paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				(left.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
			{
				left.Paddle.move(0.f, paddleSpeed * deltaTime);
			}
			if (((rightPaddleSpeed < 0.f) && (right.Paddle.getPosition().y - paddleSize.y / 2 > 5.f)) ||
				((rightPaddleSpeed > 0.f) && (right.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f)))
			{
				right.Paddle.move(0.f, rightPaddleSpeed * deltaTime);
			}
			//update ai
			if (AITimer.getElapsedTime() > AITime)
			{
				AITimer.restart();
				if (pong.ball.getPosition().y + pong.ballRadius > right.Paddle.getPosition().y + paddleSize.y / 2)
					rightPaddleSpeed = paddleSpeed;
				else if (pong.ball.getPosition().y - pong.ballRadius < right.Paddle.getPosition().y - paddleSize.y / 2)
					rightPaddleSpeed = -paddleSpeed;
				else
					rightPaddleSpeed = 0.f;
			}

			// Move the ball
			float factor = ballSpeed * deltaTime;
			this->pong.ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

			// Check collisions between the ball and the screen
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < 0.f)
			{
				isPlaying = false;
				text.message.setString("You lost!\nPress space to restart or\nescape to exit");
				text.message.setFillColor(sf::Color::Blue);
				ballSpeed = 500.f;
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth)
			{
				isPlaying = false;
				text.message.setString("You won!\nPress space to restart or\nescape to exit");
				text.message.setFillColor(sf::Color::Blue);
				ballSpeed = 500.f;
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{

				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.1f);
			}
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, gameHeight - this->pong.ballRadius - 0.1f);
			}

			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < left.Paddle.getPosition().x + paddleSize.x / 2 &&
				this->pong.ball.getPosition().x - this->pong.ballRadius > left.Paddle.getPosition().x&&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= left.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y - this->pong.ballRadius <= left.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().y > this->left.Paddle.getPosition().y)
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
				}
				else
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
				}	
				this->pong.ball.setPosition(this->left.Paddle.getPosition().x + this->pong.ballRadius + paddleSize.x / 2 + 0.1f, this->pong.ball.getPosition().y);
			}

			// Right Paddle
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > this->right.Paddle.getPosition().x - paddleSize.x / 2 &&
				this->pong.ball.getPosition().x + this->pong.ballRadius < this->right.Paddle.getPosition().x &&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= this->right.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y - this->pong.ballRadius <= this->right.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().y > this->right.Paddle.getPosition().y)
				{
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}
				else
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
				}
					
				this->pong.ball.setPosition(this->right.Paddle.getPosition().x - this->pong.ballRadius - paddleSize.x / 2 - 0.1f, this->pong.ball.getPosition().y);
			}
		}
		
	}
	
}
void Game::render()
{
	mWindow.clear(sf::Color(238,232,170));
		// Draw
	if (isPlaying)
	{
		mWindow.draw(left.Paddle);
		mWindow.draw(right.Paddle);
		mWindow.draw(pong.ball);
	}
			
	else
	{
		if (isFirstTime == true)
		{
			list.draw(mWindow);
		}
			
		else
		{
			mWindow.draw(text.message);
		}
	}
	// Display things on screen
	mWindow.display();
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if ((isPlaying==false)&&isFirstTime==true)
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					list.MoveUp();
					break;
				case sf::Keyboard::Down:
					list.MoveDown();
					break;
				case sf::Keyboard::Enter:
					switch (list.getPressedItem())
					{
					case 0:
						mode = 0;
						if (!isPlaying)
						{
							isPlaying = true;
							isFirstTime = false;
							clock.restart();

							// Reset position
							left.Paddle.setPosition(10 + paddleSize.x / 2, (float)gameHeight / 2);
							right.Paddle.setPosition(gameWidth - 10 - paddleSize.x / 2, (float)gameHeight / 2);
							pong.ball.setPosition((float)gameWidth / 2, (float)gameHeight / 2);

							// Reset the ball
							do
							{
								ballAngle = (std::rand() % 360) * 2 * pi / 360;
							} while (std::abs(std::cos(ballAngle)) < 0.7f);
						}
						break;
					case 1:
						mode = 1;
						if (!isPlaying)
						{
							isPlaying = true;
							isFirstTime = false;
							clock.restart();

							// Reset position
							left.Paddle.setPosition(10 + paddleSize.x / 2, (float)gameHeight / 2);
							right.Paddle.setPosition(gameWidth - 10 - paddleSize.x / 2, (float)gameHeight / 2);
							pong.ball.setPosition((float)gameWidth / 2, (float)gameHeight / 2);

							// Reset the ball
							do
							{
								ballAngle = (std::rand() % 360) * 2 * pi / 360;
							} while (std::abs(std::cos(ballAngle)) < 0.7f);
						}
						break;
					case 2:
						mWindow.close();
						break;
					default:
						break;
					}
				default:
					break;
				}
			default:
				break;
			}
		}
		if ((isFirstTime==false)&&(isPlaying==false))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					isPlaying = true;
					clock.restart();

					// Reset the position of the paddles and ball
					left.Paddle.setPosition(10 + paddleSize.x / 2,(float) gameHeight / 2);
					right.Paddle.setPosition(gameWidth - 10 - paddleSize.x / 2,(float) gameHeight / 2);
					pong.ball.setPosition((float)gameWidth / 2, (float)gameHeight / 2);

					// Reset the ball angle
					do
					{
						// Make sure the ball initial angle is not too much vertical
						ballAngle = (std::rand() % 360) * 2 * pi / 360;
					} while (std::abs(std::cos(ballAngle)) < 0.7f);
					break;
				case sf::Keyboard::Escape:
					isFirstTime = true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
	}
}

