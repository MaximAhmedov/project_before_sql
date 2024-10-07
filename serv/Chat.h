#pragma once
#include <iostream>
#include "User.h"
#include "Sha1.h"
#include <vector>
#include <map>

#define LOGINLENGTH 10

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

class Chat {

public:
	Chat();
	~Chat();

	enum COMMAND { REGIS = 1, SIGNIN, CHATW, ADDMES, ALLUSER, ALLCHATS};	
	
	std::string parsedPart(std::string& stringLine);
	std::string regis(std::string& commandFromUser);
	std::string auth(std::string& commandFromUser);
	std::string chatw (std::string& commandFromUser);
	std::string addmes (std::string& commandFromUser);
	std::string alluser (std::string& commandFromUser);
	std::string allchats (std::string& commandFromUser);

	User* findMain(std::string login);
	User* chatChoice(int number, User* me);
	User* userChoice(int number, User* me);
	
	
	enum COMMAND getCommand(std::string& commandFromUser);

private:
	std::map<std::string, COMMAND> comMap;
	std::string delim = "%";
	std::vector<User*> _User;
};