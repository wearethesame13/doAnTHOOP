#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class pauseMessage
{
public:
	sf::Text message;
	sf::Font font;

	pauseMessage()
	{
		font.loadFromFile("resources/sansation.ttf");
		this->message.setFont(font);
		this->message.setCharacterSize(50);
		this->message.setPosition(170.f, 150.f);
		this->message.setFillColor(sf::Color::White);
	}
};

