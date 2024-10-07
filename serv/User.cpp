#include <iostream>
#include "User.h"

User::User(std::string& login, uint* pass) : _login(login), _pass(pass){
	_myMes = new HashTable;
}

User::User(std::string& name, std::string& login, uint* pass) : _name(name), _login (login), _pass(pass)
{
	_myMes = new HashTable;
}

User::~User()
{
	delete _myMes;
}

void User::setName(std::string& name)
{
	_name = name;
}

std::string User::getName() const
{
	return this->_name;
}

std::string User::getLog() const
{
	return this->_login;
}

bool User::checkPass(uint* pass) const
{
	if (!memcmp(pass, this->_pass, SHA1HASHLENGTHBYTES))
		return true;
	return false;
}

std::string User::getFriendLogInChat(int number)
{
	return _myMes->getLogHT(number);
}

void User::sendMes(std::string& text, User* sender, User* receiver)
{
	_myMes->send(text, receiver->getName(), receiver->getLog());
	receiver->_myMes->getBy(text, sender->getName(), sender->getLog());
}

std::string User::showOneChat(User* mate) const
{
	return _myMes->showMessages(mate->getName(), mate->getLog());
}

std::string User::showAllChats() const
{
	return _myMes->showMessWithAll();
}

bool User::isEmptyMes()
{
	return this->_myMes->isEmpty();
}

int User::getCountOfChats() const
{
    return _myMes->getCount();
}
