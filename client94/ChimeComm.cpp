//*******************************************************************
//*
//* Implementation of ChimeComm communication class.
//*
//*******************************************************************

#include <stdlib.h>
#include <string.h>

#include "cssysdef.h"
#include "chimeComm.h"
#include "comm_client/ClientComm.h"


chimeComm::chimeComm()
{

}

chimeComm::chimeComm(ClientComm *client_comm, ChimeSystemDriver *System)
{

	chimeComm::System = System;
	chimeComm::client_comm = client_comm;
}

chimeComm::~chimeComm()
{

}

void chimeComm::SetChimeCom(ClientComm *client_comm, ChimeSystemDriver *System)
{
	chimeComm::System = System;
	chimeComm::client_comm = client_comm;
}

void chimeComm::UpdateChimeComm()
{
	chimeComm::client_comm = System->info->GetCommObject();
}


//Utility function to convert from float to string
char* chimeComm::ftoa(float num)
{
	int i, j, k,  dec, sign, size;
	char str[15], tempstr[15];

	strcpy(tempstr, fcvt(num, 7, &dec, &sign));
	size = strlen(tempstr);
	if (num < 0)
	{
		size++;
		str[0] = '-';
		i = 1;
	}
	else
		i = 0;

	j = 0;
	if(dec <= 0)
	{		
		str[i++] = '0'; 
		str[i++] = '.'; //put the decimal point

		for (k = 0; k < -dec; k++)
			str[i++] = '0';
	}
	else
	{
		for (k = 0; k < dec; k++)
			str[i++] = tempstr[k];
		str[i++] = '.'; //put the decimal point
		j = dec;
	}	

	for (k = j; k <= size; k++)
		str[i++] = tempstr[k];

	return strdup(str);
}


//Append given token to a string.
bool chimeComm::AppendToken(char *command, char *token)
{
	strcat(command, " ");
	strcat(command, token);

	return true;
}

//Connect to a given CHIME Server
bool chimeComm::Connect(char *server, char *username, char *password)
{
	strcpy(command, server);
	AppendToken(command, userID);
	AppendToken(command, password);

	//client_comm->
	//SendFunction(c_connect, command);
	return true;
}

//Request info about a given room
bool chimeComm::GetRoom(char *url)
{
	strcpy(command, url);

	client_comm->SendSienaFunction(c_getRoom, command, url,"HTTP");
	return true;
}


//Send updated position of a moved object
bool chimeComm::MoveObject(char *roomUrl, char *objectUrl, float x, float y, float z)
{
	strcpy(command, roomUrl);
	AppendToken(command, objectUrl);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));

	client_comm->SendSienaFunction(c_moveObject, command, roomUrl, "HTTP");
	return true;
}

//Send updated position of the user
bool chimeComm::MoveUser(char *roomUrl, char *username, char *ip_address, float x, float y, float z, const csStrVector *userList)
{

	strcpy(command, roomUrl);
	AppendToken(command, username);
	AppendToken(command, ip_address);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));

	//Send signal to all the users in this room
	for(int i = 0 ; i < userList->Length(); i++)
	{
		char temp[100];
		strcpy(temp, userList->Get(i));
		char *to_username = strtok(temp, " ");
		char *to_ip_address = strtok(NULL, " ");

		//if (to_username != NULL && to_ip_address != NULL 
		//	&& strcmp(to_ip_address, ip_address) != 0) //don't send it to yourself
			

			client_comm->SendUDPFunction(to_ip_address, c_moveUser, command);
	}
	//client_comm->SendSienaFunction(c_moveUser, command, roomUrl, "HTTP");
	return true;
}

//Broadcast entrance of a user in a given room
bool chimeComm::UserEnteredRoom(char *username, char *ip_address, char *newRoomUrl, char *shape, float x, float y, float z, const csStrVector *userList)
{

	//add user to the history window
	if (System != NULL && System->historyWindow != NULL)
		System->historyWindow->AddItem(newRoomUrl);

	strcpy(command, username);
	AppendToken(command, ip_address);
	AppendToken(command, newRoomUrl);
	AppendToken(command, shape);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));

	client_comm->SendSienaFunction(c_enteredRoom, command, newRoomUrl, "HTTP");
	MoveUser(newRoomUrl, username, ip_address, x, y, z, userList);
	return true;
}

//Broadcast that a user has lift a given room
bool chimeComm::UserLeftRoom(char *username, char *ip_address, char *oldRoomUrl, char *newRoomUrl)
{

	strcpy(command, username);
	AppendToken(command, ip_address);
	AppendToken(command, oldRoomUrl);
	AppendToken(command, newRoomUrl);

	client_comm->SendSienaFunction(c_leftRoom, command, oldRoomUrl, "HTTP");
	return true;
}

//Broadcast addition of new object in a given room
bool chimeComm::AddObject(char *roomUrl, char *objectUrl, float x, float y, float z)
{
	strcpy(command, roomUrl);
	AppendToken(command, objectUrl);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));

	client_comm->SendSienaFunction(c_addObject, command, roomUrl,"HTTP");
	return true;
}

//Broadcast deletion of new object in a given room
bool chimeComm::DeleteObject(char *roomUrl, char *objectUrl)
{
	strcpy(command, roomUrl);
	AppendToken(command, objectUrl);

	client_comm->SendSienaFunction(c_deleteObject, command, roomUrl,"HTTP");
	return true;
}

//Subscribe for events of this room
bool chimeComm::SubscribeRoom(char *roomUrl, char *username)
{
	strcpy(command, roomUrl);
	AppendToken(command, username);

	client_comm->subscribeALL(roomUrl);
	return true;
}
//Unsubscribe for events of this room
bool chimeComm::UnsubscribeRoom(char *roomUrl, char *username)
{
	strcpy(command, roomUrl);
	AppendToken(command, username);

	client_comm->unsubscribeRoom(roomUrl, EVENTS_FOR_ANYONE);
	//client_comm->SendSienaFunction(c_unsubscribeRoom, command, roomUrl,"HTTP");
	return true;
}

//Disconnect user from CHIME server
bool chimeComm::Disconnect(char *roomUrl, char *username, char *ip_address, const csStrVector *userList)
{
	strcpy(command, roomUrl);
	AppendToken(command, username);
	AppendToken(command, ip_address);

	//Send signal to all the users in this room
	for(int i = 0 ; i < userList->Length(); i++)
	{
		char temp[100];
		strcpy(temp, userList->Get(i));
		char *to_username = strtok(temp, " ");
		char *to_ip_address = strtok(NULL, " ");

		if (to_username != NULL && to_ip_address != NULL 
			&& strcmp(to_ip_address, ip_address) != 0) //don't send it to yourself
			

			client_comm->SendUDPFunction(to_ip_address, c_disconnect, command);
		}
	
	strcpy(command, username);
	AppendToken(command, ip_address);
	client_comm->SendSienaFunction(c_disconnect, command, roomUrl, "HTTP");
	return true;
}
