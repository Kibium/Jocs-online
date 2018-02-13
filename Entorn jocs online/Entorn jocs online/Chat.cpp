// Entornjocsonline.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>

using namespace std;

int asd() {

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType, mode;
	char buffer[2000];
	size_t received;
	string text = "Coneected to: ";


	cout << "Enter 's' for Server, Enter 'c' for client" << endl;
	cin >> connectionType;

	if (connectionType == 's') {
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		text += "Server";
		mode = 's';

	}

	else if (connectionType == 'c') {
		socket.connect(ip, 2000); // si canviam ip per sa ip que volem, sempre q tengui es programa obert, anira be
		text += "Client";
		mode = 'c';
	}
	
	
	socket.send(text.c_str(), text.length() + 1);

	socket.receive(buffer, sizeof(buffer), received);

	cout << buffer << endl;

	system("pause");
}
