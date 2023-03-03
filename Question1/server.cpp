#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

string SetTime()
{
	time_t now = time(0);
	string str;
	tm *ltm = localtime(&now);
	str= to_string(1 + ltm->tm_mon) +"/"+ to_string(ltm->tm_mday) +"/" +to_string((1900 + ltm->tm_year)-2000)+ " ";
	str+= to_string(ltm->tm_hour) +":"+ to_string(ltm->tm_min) +":" +to_string(ltm->tm_sec);
	return str;
}
/*
int CountSerial(string file)// don't need this becuase files have their serial numbers
{
	string str;
	int x=0;
	fstream obj;

	obj.open(file.c_str());
	while (getline(obj,str))
	x++;
	obj.close();
	return x;
}*/

void CountTotalEntries()
{
	string str;
	int x=0;
	fstream obj;

	obj.open("PF.txt");
	while (getline(obj,str))
	x++;
	obj.close();
	obj.open("DS.txt");
	while (getline(obj,str))
	x++;
	obj.close();
	obj.open("OOP.txt");
	while (getline(obj,str))
	x++;
	obj.close();
	obj.open("Cnet.txt");
	while (getline(obj,str))
	x++;
	obj.close();
	obj.open("Coal.txt");
	while (getline(obj,str))
	x++;
	obj.close();
	obj.open(".txt");
	while (getline(obj,str))
	x++;
	obj.close();
	if (x==10)
	exit(0);
	
}

int main() 
{

	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	
	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(3001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 5);

	string password="12346";
	char messageaff[256]="Authentication Passed!";
	char messagefail[256]="Authentication Failed!";	
	
	int S_PF=0;
	int S_OOP=0;
	int S_DS=0;
	int S_Algo=0;
	int S_Cnet=0;
	int S_Coal=0;

	while(1)
	{
		char buf[256];
		int client_socket;
		int status;

		client_socket = accept(server_socket, NULL, NULL);
		pid_t pid=fork();
		CountTotalEntries();
		if(!pid)//The child process
		{ 
			recv(client_socket, &buf, sizeof(buf), 0);//receiving password
			cout<<"Password Entered : "<<buf<<endl;
			if (buf==password)
			{
				send(client_socket, messageaff, sizeof(messageaff), 0);
				recv(client_socket, &buf, sizeof(buf), 0);//receiving	
				string date_time = SetTime();
				string strs="TIME IN NOTED:"+ date_time;
				
				char time_noted[strs.length() + 1];
				strcpy(time_noted, strs.c_str());
				send(client_socket, time_noted, sizeof(time_noted), 0);

				char buffer[256];
				recv(client_socket, &buffer, sizeof(buffer), 0);//receiving CONTROL BACK

				//FILE HANDLING

				int x;
				for( x = 0 ; buf[x]!=' '; x++);
				x++;
				for(	; buf[x]!=' '; x++);
				x++; //after this is the dept

				// Department names PF, OOP, Data Structure, Algo, CNET, COAL
				if (buf[x]== 'P')
				{
					ofstream obj;
					obj.open("PF.txt", std::ios_base::app);
					
					obj<</*CountSerial("PF.txt")<<*/" "<<"PF"<<" "<<date_time<<" ";//add serial number + dept + date + time

					for (int y = 0 ; y < x ; y++) //add full name
					obj<<buf[y];
					obj<<endl;
					obj.close();

					CountTotalEntries();
				}
				else if (buf[x]== 'O')
				{
					ofstream obj;
					obj.open("OOP.txt", std::ios_base::app);
					
					obj<</*CountSerial("OOP.txt")<<*/" "<<"OOP"<<" "<<date_time<<" ";//add serial number + dept + date + time

					for (int y = 0 ; y < x ; y++) //add full name
					obj<<buf[y];
					obj<<endl;
					obj.close();

					CountTotalEntries();
				}
				else if (buf[x]== 'D')
				{
					ofstream obj;
					obj.open("DS.txt", std::ios_base::app);
					
					obj<</*CountSerial("DS.txt")<<*/" "<<"Data Structures"<<" "<<date_time<<" ";//add serial number + dept + date + time

					for (int y = 0 ; y < x ; y++) //add full name
					obj<<buf[y];
					obj<<endl;
					obj.close();

					CountTotalEntries();
				}
				else if (buf[x]== 'A')
				{
					ofstream obj;
					obj.open("Algo.txt", std::ios_base::app);
					
					obj<</*CountSerial("Algo.txt")<<*/" "<<"Algo"<<" "<<date_time<<" ";//add serial number + dept + date + time

					for (int y = 0 ; y < x ; y++) //add full name
					obj<<buf[y];
					obj<<endl;
					obj.close();

					CountTotalEntries();
				}
				else if (buf[x]== 'C' && buf[x+1]== 'n')
				{
					ofstream obj;
					obj.open("Cnet.txt", std::ios_base::app);
					
					obj<</*CountSerial("Cnet.txt")<<*/" "<<"Cnet"<<" "<<date_time<<" ";//add serial number + dept + date + time

					for (int y = 0 ; y < x ; y++) //add full name
					obj<<buf[y];
					obj<<endl;
					obj.close();

					CountTotalEntries();
				}
				else if (buf[x]== 'C' && buf[x+1]== 'o')
				{
					ofstream obj;
					obj.open("Coal.txt", std::ios_base::app);
					
					obj<</*CountSerial("Coal.txt")<<*/" "<<"Coal"<<" "<<date_time<<" ";//add serial number + dept + date + time

					for (int y = 0 ; y < x ; y++) //add full name
					obj<<buf[y];
					obj<<endl;
					obj.close();

					CountTotalEntries();
				}
				
			}
			else 
			{	
				send(client_socket, messagefail, sizeof(messagefail), 0);
				break;
			}
			
			// close the socket
			close(client_socket);
		}
		else
		//Parent process
		close(client_socket);
		
	}
	return 0;
}


