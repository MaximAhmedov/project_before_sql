#include <iostream>
#include <algorithm>
//#include "Chat.h"
#include "myServer.h"


#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

#define WIN(exp) exp
#define NIX(exp)

int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	myServer server;
	server.fdStart();
	while(true){
		int counter = server.selectFunc();
		for(int i = 0; i < counter; i++){
			server.mainFunc(i);
		}
	}
	return 0;
}