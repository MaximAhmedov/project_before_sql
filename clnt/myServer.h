#pragma once
#include <iostream>
#include <string.h>

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#define WIN(exp) exp
#define NIX(exp)
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)

extern WSADATA wsaData;


#elif defined(__linux__)
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define WIN(exp)
#define NIX(exp) exp

#endif

#define PORT 7777
#define Buff 1024


class myServer{

public:

myServer();
~myServer();
bool startServer(const char* x);
std::string& recFrom();
void sendTo(std::string& strToServ);
void stopServer();
bool checkEnd();


private:

WIN(SOCKET ListenSocket = INVALID_SOCKET;);
WIN(SOCKET ClientSocket = INVALID_SOCKET;);

NIX(int ListenSocket;);
NIX(int ClientSocket;);
NIX(int SOCKET_ERROR = -1;);
NIX(int INVALID_SOCKET = -1;);

struct sockaddr_in serveraddress;
struct sockaddr_in client;
int iResult;
int recvBuffLen = Buff;
char recvBuff[Buff];
std::string message;
bool stopSlovo = false;
};