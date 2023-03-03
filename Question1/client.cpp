#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main() {
	
	
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	cout<<"Connection established with Server."<<endl;
	cout<<"Password: ";	

	while(1)
	{	
		char request[256];
		char buf[256];
		char login[256];		

		cin.getline(request, 256);
		send(sock, request, sizeof(request), 0);//sending password
		recv(sock, &buf, sizeof(buf), 0);//receiving authentication message
		cout<<buf<<endl;
		cout<<"Proceed to Login (format--->'TIME IN:(FIRST NAME) (LAST NAME) (SUBJECT)')"<<endl;				
		cin.getline(login, 256);		
		send(sock, login, sizeof(login), 0);
		recv(sock, &buf, sizeof(buf), 0);//receiving time in noted
		cout<<buf<<endl; //display Time In Noted
		send(sock, login, sizeof(login), 0);// just to send control back to the server
	}	
	
	close(sock);

	return 0;
}
