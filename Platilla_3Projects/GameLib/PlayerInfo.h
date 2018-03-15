#pragma once
#include <SFML\Graphics.hpp>

#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
class PlayerInfo
{
public:
	sf::TcpSocket socket;
	std::string name;
	int turn;
	sf::Vector2i fichas[4];
	int dados[2];

	PlayerInfo();
	~PlayerInfo();
};