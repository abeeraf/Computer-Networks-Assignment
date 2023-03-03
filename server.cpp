#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
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

int main() {

	char buf[200];
	char buff[200];
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
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	
	string str;
	fstream obj;
	
	recv(client_socket, &buf, sizeof(buf), 0);
	cout<<buf<<endl;	
	obj.open("Log.txt", std::ios_base::app);// add to log
	obj<<SetTime()<<endl;
	obj.close();
	
	str="";//making it Null
	if (buf[0]=='L')// fetch log of server access 
	{
		obj.open("Log.txt");
		string str2;
		while(getline(obj,str2))
		str+=str2+"\n";
		obj.close();
	}
	else if (buf[0]=='I')// fetch invoice 
	{	
		obj.open("Assignment 1.txt");
		string str2;
		int x=1;
		while(getline(obj,str2))
		{
			if (str2[0]==buf[1] && str2[1]==buf[2] && str2[2]==buf[3] && str2[3]==buf[4] && str2[4]==buf[5] && str2[5]==buf[6])
			str+=to_string(x++)+" "+str2+"\n";
		}
		obj.close();
	}
	else if (buf[0]=='N')// Exit Program
	{	
		str="Program Ended";
	}	
	else if (buf[0]=='D')// Delete Record 
	{	
		obj.open("Assignment 1.txt");
		string str2;
		int x=0;
		while(getline(obj,str2))
		{	
			if ("D"+str2==buf)
			getline(obj,str2);//skip that line
	
			str+=str2+"\n";
		}
		obj.close();

		std::ofstream ofs;
		ofs.open("Assignment 1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs<<str;
		ofs.close();

		str="Record deleted";
	}		
	else // add record to invoice
	{
		obj.open("Assignment 1.txt");
		string str2;
		str="";
		int x=0;
		while(getline(obj,str2))
		{	
			
			if (!x && (str2[0]==buf[0] && str2[1]==buf[1] && str2[2]==buf[2] && str2[3]==buf[3] && str2[4]==buf[4] && str2[5]==buf[5])){
			str=str+buf+"\n";//add the line above 
			x=1;}
	
			str+=str2+"\n";
		}
		obj.close();

		obj.open("Assignment 1.txt");//rewrite file with it
		obj<<str;
		obj.close();
		str="Record Added";
	}
	char server_message2[str.length()+1];
	strcpy(server_message2, str.c_str());
	send(client_socket, server_message2, sizeof(server_message2), 0); //sending Log or Innvoice
	

	// close the socket
	close(server_socket);
	
	return 0;
}

