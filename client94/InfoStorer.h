 /*
 *
 * Copyright (c) 2002: The Trustees of Columbia University
 *    in the City of New York.  All Rights Reserved.
 *
 *
 */
#ifndef __INFOSTORER_H_
#define __INFOSTORER_H_

#include <fstream.h>
#include <time.h>
//forward declarations
class ClientComm;

class InfoStorer {

//this class will probably need a Mutex...
//will keep this in the back of my head for now
private:
	 
  char username[50];		//the username
  char password[50];		//the password
  char siena_location[50];	//siena location
  int siena_port;			//siena port
  int chat_port;			//chat port to use
  char ip_address[50];		//ip_address of this machine
  ClientComm *comm_object;	//communication object
  ofstream log_file;		//init the log file

  volatile HANDLE mutex;	// Create a Mutex object

public:
	
	InfoStorer();						//setup internal things
	~InfoStorer() { CloseLog(); };		//destruct this object

	//clientComm manipulation
	ClientComm* GetCommObject();					//get the client comm object
	void SetCommObject(ClientComm *comm_object);	//set the communications object
	
	void GetUsername(char *username);				//get the username
	void GetPassword(char *password);				//get the password
	const int GetChatPort();						//return the port used to send chat commands
	
	void GetSienaLocation(char *siena_location);	//get the hostname of the siena
	const int GetSienaPort();						//get the port on which Siena is listening
	void SetUsername(const char *username);			//set the username
	void SetPassword(const char *password);			//set the password

	void SetChatPort(int chat_port);				//set the port used to send chat commands
	void SetSienaLocation(const char *siena_location);	//set the hostname of the siena

	void SetSienaPort(int siena_port);				//set the port on which Siena is listening
	void SetMyIPAddress(char *ip_address);			//set my IP address
	void GetMyIPAddress(char *my_address);			//get my IP address

	char* GetLocalIP();								//get the local IP address
	void AddToLog(const char *system, const char *message);
	void CloseLog();
};

#endif