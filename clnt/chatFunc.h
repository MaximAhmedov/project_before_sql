#pragma once
#include <iostream>
#include <string.h>
#include <limits>
#include "myServer.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

class chatFunc{
public:
    chatFunc();
    ~chatFunc();
    bool start(const char *x = "127.0.0.1");
    std::string showMainMenu();
    bool signIn();
    bool registration();
    bool checkAuth(std::string& checkstr);
    std::string showSecondMenu();
    void chatting(int x, std::string& wayOfChoose);
    void showAllUsers();
    void showAllChats();
    void signOut();
    int inputCommand(int& x, std::string interfaceLine);
    std::string parsedPart(std::string& stringLine);
private:
    myServer serv;
    std::string _login;
    std::string delim = "%";
};