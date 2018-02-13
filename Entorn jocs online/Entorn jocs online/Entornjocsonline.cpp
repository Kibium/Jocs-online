#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#define MAX 100
using namespace std;

size_t received;
mutex mut;
bool endGame = false;
sf::TcpSocket socket;
char buffer[MAX];
std::vector<std::string> aMensajes;


void Recibir() {
	while (!endGame) {
		mut.lock(); 
		socket.receive(buffer, MAX, received);
		aMensajes.push_back(buffer);
		mut.unlock();
	}
}

int main()
{

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();


	char connectionType, mode;
	
	size_t received;

	string thetext = "Coneected to: ";


	cout << "Enter 's' for Server, Enter 'c' for client" << endl;
	cin >> connectionType;

	if (connectionType == 's') {
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		thetext += "Server";
		mode = 's';

	}

	else if (connectionType == 'c') {
		socket.connect(ip, 2000); // si canviam ip per sa ip que volem, sempre q tengui es programa obert, anira be
		thetext += "Client";
		mode = 'c';
	}

	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Chat");

	sf::Font font;
	if (!font.loadFromFile("courbd.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	std::string mensaje = " >";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	chattingText.setStyle(sf::Text::Bold);


	sf::Text text(mensaje, font, 14);
	text.setFillColor(sf::Color(0, 160, 0));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);
	//
	std::thread t(&Recibir);

	

	while (window.isOpen())
	{

		sf::Event evento;
		while (window.pollEvent(evento))
		{
			switch (evento.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape)
					window.close();
				else if (evento.key.code == sf::Keyboard::Return)
				{
					aMensajes.push_back(mensaje);
					if (aMensajes.size() > 25)
					{
						aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
						
					}

					socket.send(mensaje.c_str(), mensaje.length() + 1); //SEND
					mensaje = ">";


				}
				break;
			case sf::Event::TextEntered:

				if (evento.text.unicode >= 32 && evento.text.unicode <= 126) {
					mensaje += (char)evento.text.unicode;
					
				}
				else if (evento.text.unicode == 8 && mensaje.length() > 0)
					mensaje.erase(mensaje.length() - 1, mensaje.length());
				break;
			}

		}


		window.draw(separator);
		for (size_t i = 0; i < aMensajes.size(); i++)
		{
			std::string chatting = aMensajes[i];
			chattingText.setPosition(sf::Vector2f(0, 20 * i));
			chattingText.setString(chatting);
			window.draw(chattingText);
		}
		std::string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		window.draw(text);


		window.display();
		window.clear();
	}
	t.join();
}