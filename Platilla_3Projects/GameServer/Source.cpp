#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <map>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <PlayerInfo.h>
#define MAX 100
using namespace std;
std::string mensaje;
//se usa en los 3
size_t received;
bool endGame = false;
sf::TcpSocket socket;
sf::TcpSocket::Status status;
char buffer[MAX];
std::vector<std::string> aMensajes;
//solo blocking
mutex mut;
//solo nonblocking
size_t sent;
//solo Socket selector
sf::SocketSelector selector;
bool running = true;
//Blocking
#define MAX 100
#define SIZE_TABLERO 64
#define SIZE_FILA_TABLERO 8
#define LADO_CASILLA 64
#define RADIO_AVATAR 25.f
#define OFFSET_AVATAR 5

#define SIZE_TABLERO 64
#define LADO_CASILLA 64
#define RADIO_AVATAR 25.f
#define OFFSET_AVATAR 5


enum TipoProceso { RATON, GATO, PADRE };
char tablero[SIZE_TABLERO];
sf::Vector2f TransformaCoordenadaACasilla(int _x, int _y) {
	float xCasilla = _x / LADO_CASILLA;
	float yCasilla = _y / LADO_CASILLA;
	sf::Vector2f casilla(xCasilla, yCasilla);
	return casilla;
}sf::Vector2f BoardToWindows(sf::Vector2f _position) {
	return sf::Vector2f(_position.x*LADO_CASILLA + OFFSET_AVATAR, _position.y*LADO_CASILLA + OFFSET_AVATAR);
}TipoProceso quienSoy;

class vec2 {
public:
	int x;
	int y;

	vec2(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

int main()
{
	/*
	sf::TcpListener listener;
	sf::Socket::Status status = listener.listen(50000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Error al abrir listener\n";
		exit(0);
	}
	// Create a list to store the future clients
	std::vector<PlayerInfo*> clients;
	// Create a selector
	sf::SocketSelector selector;
	// Add the listener to the selector
	selector.add(listener);

	// Endless loop that waits for new connections
	while (running)
	{
		// Make the selector wait for data on any socket
		if (selector.wait())
		{
			// Test the listener
			if (selector.isReady(listener))
			{
				// The listener is ready: there is a pending connection
				PlayerInfo* client = new PlayerInfo;
				while (clients.size() < 4) {
					if (listener.accept(client->socket) == sf::Socket::Done)
					{
						// Add the new client to the clients list
						std::cout << "Llega el cliente con puerto: " << client->socket.getRemotePort() << std::endl;
						clients.push_back(client);

						// Add the new client to the selector so that we will
						// be notified when he sends something
						selector.add(client->socket);
					}
				else
				{
					// Error, we won't get a new connection, delete the socket
					std::cout << "Error al recoger conexi�n nueva\n";
					delete client;
				}
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				for (int i = 0; i < clients.size(); i++) {
					{
						if (selector.isReady(clients[i]->socket))
						{
							sf::Socket::Status statusReceive = clients[i]->socket.receive(buffer, MAX, received);
							buffer[received] = '\0';
							mensaje = buffer;
							if (status == sf::Socket::Done)
							{
								std::cout << "He recibido " << mensaje << " del puerto " << clients[i]->socket.getRemotePort() << std::endl;

								for (int j = 0; j < clients.size(); j++) {

									status = clients[j]->socket.send(mensaje.c_str(), mensaje.length() + 1);
									if (status == sf::Socket::Done) {
										std::cout << "Se ha enviado";
									}
									else {
										std::cout << "No se ha enviado";
									}
								}
							}
							else if (status == sf::Socket::Disconnected)
							{
								selector.remove(clients[i]->socket);
								std::cout << "Elimino el socket que se ha desconectado\n";
							}
							else
							{
								std::cout << "Error al recibir de " << clients[i]->socket.getRemotePort() << std::endl;
							}

						}
					}

				}
			}
		}

	}*/
	sf::Vector2f casillaOrigen, casillaDestino;
	bool casillaMarcada = false;
	map <int, vec2> redInit, blueInit, greenInit, yellInit, tiles, redTiles, greenTiles, blueTiles, yellowTiles;

	//START RED
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			redInit.insert(pair<int, vec2>(i, vec2(120 + 34 * i, 120+34*j)));
		}
	}

	//START BLUE
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			blueInit.insert(pair<int, vec2>(i, vec2(585 + 34 * i, 120 + 34 * j)));
		}
	}

	//START GREEN
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			greenInit.insert(pair<int, vec2>(i, vec2(120 + 34 * i, 585 + 34 * j)));
		}
	}

	//START YELLOW
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			yellInit.insert(pair<int, vec2>(i, vec2(585 + 34 * i, 585 + 34 * j)));
		}
	}


	// caselles 1 - 8
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(i, vec2(477, 764-34*i)));

	// caselles 9 - 16
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(8+i, vec2(521 + 34*i, 489 )));

	// casella 17
	tiles.insert(pair<int, vec2>(16, vec2(760, 400)));

	// caselles 18 - 25
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(17+i, vec2(760- 34*i, 310)));

	// 26 - 33
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(25 + i, vec2(480, 280 - 34*i)));

	// 34
	tiles.insert(pair<int, vec2>(33, vec2(400, 36)));

	// 35 - 42
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(34 + i, vec2(310, 38 + 34 * i)));

	// 43 - 50
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(42 + i, vec2(278 - 34 * i, 324 )));

	// 51
	tiles.insert(pair<int, vec2>(50, vec2(40, 400)));

	// 52 - 59
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(51 + i, vec2(39 + 34 * i, 496)));

	// 60 - 67
	for (int i = 0; i < 8; i++)
		tiles.insert(pair<int, vec2>(59 + i, vec2(315, 515 + 34*i)));

	// 68
	tiles.insert(pair<int, vec2>(67, vec2(400, 760)));

	//META DEL RED
	for (int i = 0; i < 7; i++)
		redTiles.insert(pair<int, vec2>(i, vec2(400, 74 + 34 * i)));

	//META DEL GREEN
	for (int i = 0; i < 7; i++)
		greenTiles.insert(pair<int, vec2>(i, vec2(75 + 34*i, 400)));

	//META DEL YELLOW
	for (int i = 0; i < 7; i++)
		yellowTiles.insert(pair<int, vec2>(i, vec2(399, 727-34*i)));

	//META DEL BLUE
	for (int i = 0; i < 7; i++)
		blueTiles.insert(pair<int, vec2>(i, vec2(727 - 34*i, 400)));


	sf::RenderWindow window(sf::VideoMode(800, 800), "el parxis");
	sf::Event e;
	while (!endGame) {
		window.clear();

		sf::Texture image;
		image.loadFromFile("../parxis.jpg");

		sf::Sprite tablero;
		tablero.setScale(sf::Vector2f(0.32, 0.32));
		tablero.setTexture(image);
		window.draw(tablero);
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::MouseButtonPressed) {
				std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
			}
		}
		

		

		/*//Blaves
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sf::RectangleShape rectBlanco(sf::Vector2f(LADO_CASILLA / 2.5, LADO_CASILLA / 1.1));
				rectBlanco.setFillColor(sf::Color::Blue);

				//Posicions de les caselles
				rectBlanco.setPosition(sf::Vector2f(400 + LADO_CASILLA + i*LADO_CASILLA / 2 + i * 2, 400 - LADO_CASILLA - 20 + 2 * j*LADO_CASILLA / 2));
				window.draw(rectBlanco);

				casillas.push_back(make_pair(rectBlanco.getPosition().x, rectBlanco.getPosition().y));

			}
			
			//Vermells
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sf::RectangleShape rectBlanco(sf::Vector2f(LADO_CASILLA / 1.1, LADO_CASILLA /2.5));
					rectBlanco.setFillColor(sf::Color::Red);

					//Posicions de les caselles
					rectBlanco.setPosition(sf::Vector2f(400 - LADO_CASILLA + i*LADO_CASILLA / 2 + i * 2, 400 - LADO_CASILLA - 20 + j*LADO_CASILLA / 2));
					window.draw(rectBlanco);

				}
			}

			//Grocs
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					sf::RectangleShape rectBlanco(sf::Vector2f(LADO_CASILLA / 2.5, LADO_CASILLA / 1.1));
					rectBlanco.setFillColor(sf::Color::Yellow);

					//Posicions de les caselles
					rectBlanco.setPosition(sf::Vector2f(LADO_CASILLA + i*LADO_CASILLA / 2 + i * 2, 400 - LADO_CASILLA - 20 + 2 * j*LADO_CASILLA / 2));
					window.draw(rectBlanco);

				}
			}
			}*/
			window.display();
		}
	
		return 0;
	}
