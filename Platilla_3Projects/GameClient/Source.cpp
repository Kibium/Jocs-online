#pragma once
#include <PlayerInfo.h>
#include <SFML\Network.hpp>
#include <iostream>
#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>
using namespace std;

#define MAX 100
size_t  sent;
size_t received;
bool endGame = false;
sf::TcpSocket socket;
sf::TcpSocket::Status status;
char buffer[MAX];
std::vector<std::string> aMensajes;

//solo blocking
mutex mut;
vector<sf::TcpSocket*>aSock;
int main()
{
	

	sf::Packet packet;
	sf::TcpSocket sock;
	
	sf::Packet p;
	PlayerInfo jugadores[3]; // per pintar ses fitxes dels altres jugadors
	PlayerInfo yo;
	sf::Socket::Status status = sock.connect(sf::IpAddress::getLocalAddress(), 50000, sf::seconds(15.f));
	if (status != sf::Socket::Done) {
		std::cout << "No se ha conectado";
	}
	else {
		std::cout << "Esperando" << std::endl;
	}
	if (status == sf::Socket::Done) {
		std::cout << "Se conecto" << std::endl;


	}
	while (!endGame)
	{
		sock.receive(buffer, 100, received);
		std::cout << buffer << std::endl;
	}





	system("pause");
}