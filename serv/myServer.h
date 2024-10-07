#pragma once
#include <iostream>
#include <string.h>
#include "Chat.h"

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#define WIN(exp) exp
#define NIX(exp)
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)



#elif defined(__linux__)
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define WIN(exp)
#define NIX(exp) exp
#endif

#define PORT 7777
#define Buff 1024


class myServer{

public:

myServer();
~myServer();
void startToListen();

void fdStart();
int selectFunc();
void mainFunc(int i);

void accepting();
void getAndCheckRecv();
char* getMes();

void stopServer();

private:
WIN(WSADATA wsaData;);
WIN(SOCKET ListenSocket = INVALID_SOCKET;);
WIN(SOCKET ClientSocket = INVALID_SOCKET;);
WIN(SOCKET selectClSocket = INVALID_SOCKET;);
WIN(SOCKET selectSock = INVALID_SOCKET;);

NIX(int ListenSocket;);
NIX(int ClientSocket;);
NIX(int selectClSocket;);
NIX(int selectSock;);
NIX(int SOCKET_ERROR = -1;);
NIX(int INVALID_SOCKET = -1;);

struct sockaddr_in serveraddress;
struct sockaddr_in client;


fd_set master;
fd_set copy;
int iResult;
int recvBuffLen = Buff;
char recvBuff[Buff];

char hostbuffer[256];
struct hostent *host_entry;
int hostname;
struct in_addr **addr_list;

Chat chat;
};