#pragma once
#include <iostream>
#include <string>
#include "MessageHT.h"
#include "Sha1.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

class User {
public:
	User(std::string& login, uint* pass);
	User(std::string& name, std::string& login, uint* pass);
	~User();
	void setName(std::string& name);

	std::string getName()const;
	std::string getLog()const;
	bool checkPass(uint* pass) const;

	std::string getFriendLogInChat(int number);

	void sendMes(std::string& text, User* sender, User* receiver);
	std::string showOneChat(User* mate)const;
	std::string showAllChats()const;

	bool isEmptyMes();
	int getCountOfChats() const;

private:
	HashTable* _myMes;
	std::string _name;
	std::string _login;
	uint* _pass;

};