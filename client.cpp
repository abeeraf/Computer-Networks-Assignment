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
	
	int select;
	char buf[1000];
	
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));

	cout<<endl<<"Select Number"<<endl;
	cout<<"(1)Add Record"<<endl;
	cout<<"(2)Delete Record"<<endl;
	cout<<"(3)Read Invoice"<<endl;
	cout<<"(4)Ask For Access Log"<<endl;
	cout<<"(5)End Program"<<endl;
	cin>>select;

	char record[256];
	if (select == 1)
	{
		cout<<"Enter Record to Add in format -->(Invoice no)(Description)(Quantity)(Price in $)(Customer id)(Country)"<<endl;
		cin.ignore();
		cin.getline(record,256);
		send(sock, record, sizeof(record), 0);
	}
	else if (select == 2)
	{ 
		cout<<"Enter Record to Delete in format -->D(Invoice no)(Description)(Quantity)(Price in $)(Customer id)(Country)"<<endl;
		cin.ignore();
		cin.getline(record,256);
		send(sock, record, sizeof(record), 0);
	}
	else if (select == 3)
	{
		cout<<"Enter Invoice Number for Server to fetch in format--> I(Invoice Number): ";
		for(int x = 0 ; x < 7 ; x++)
		cin>>record[x];
		send(sock, record, sizeof(record), 0);
	}
	else if (select == 4)
	{
		send(sock, "Log", sizeof("Log"), 0);
	}
	else if (select == 5)
	{
		record[0]='N'; //terminat program
	}	
	recv(sock, &buf, sizeof(buf), 0);
	cout<<buf<<endl; 

	close(sock);

	return 0;
}
