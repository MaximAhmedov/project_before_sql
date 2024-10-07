#include<iostream>
#include "MessageHT.h"

HashTable::HashTable() {
	mem_size = 8;
	mess_tops = new Message * [mem_size];
	for (int i = 0; i < mem_size; i++) {
		mess_tops[i] = nullptr;
	}
	count = 0;
}

HashTable::~HashTable() {
	for (int i = 0; i < mem_size; i++) {
		if (mess_tops[i] != nullptr) {
			delete mess_tops[i];
		}
	}
	delete[] mess_tops;
}

int HashTable::hash_func(const std::string& login) {
	int sum = 0;
	char* name = new char[login.length() + 1];
	strcpy(name, login.c_str());

	for (int i = 0; i < strlen(name); i++) {
		sum += login[i];
	}
	return std::abs(sum) % mem_size;
}

void HashTable::send(std::string& text, const std::string& name, const std::string& login) {
	int index = hash_func(login);
	if (mess_tops[index] != nullptr && mess_tops[index]->_login == login) {
		Message* lastOne = mess_tops[index];
		while (lastOne->next != nullptr) {
			lastOne = lastOne->next;
		}
		Message* newMessage = new Message(text, name, login);
		lastOne->next = newMessage;
	}

	else if (mess_tops[index] != nullptr && mess_tops[index]->_login != login) {
		for (int i = 0; i < mem_size; i++) {
			index++;
			if (index == mem_size)
				index = 0;
			if (mess_tops[index] != nullptr) {
				if (mess_tops[index]->_login == login)
					break;
			}
			else if (mess_tops[index] == nullptr){
				count++;
				break;
			}
		}
		mess_tops[index] = new Message(text, name, login);
	}
	else{
		mess_tops[index] = new Message(text, name, login);
		count++;
	}
}

void HashTable::getBy(std::string& text, const std::string& name, const std::string& login){
	int index = hash_func(login);
	if (mess_tops[index] != nullptr && mess_tops[index]->_login == login) {
		Message* lastOne = mess_tops[index];
		while (lastOne->next != nullptr) {
			lastOne = lastOne->next;
		}
		Message* newMessage = new Message(text, name, login);
		lastOne->next = newMessage;
		newMessage->sended = false;
	}
	else if (mess_tops[index] != nullptr && mess_tops[index]->_login != login) {
		for (int i = 0; i < mem_size; i++) {
			index++;
			if (index == mem_size)
				index = 0;
			if (mess_tops[index] != nullptr) {
				if (mess_tops[index]->_login == login)
					break;
			}
			else if (mess_tops[index] == nullptr){
				count++;
				break;
			}
		}
		mess_tops[index] = new Message(text, name, login);
		mess_tops[index]->sended = false;
	}
	else {
		mess_tops[index] = new Message(text, name, login);
		mess_tops[index]->sended = false;
		count++;
	}
	
}

std::string HashTable::showMessages(const std::string& name, const std::string& login)
{
	std::string temp;
	int index = hash_func(login);
	if (mess_tops[index] != nullptr && mess_tops[index]->_login != login) {
		for (int i = 0; i < mem_size; i++) {
			index++;
			if (index == mem_size)
				index = 0;
			if (mess_tops[index] != nullptr) {
				if (mess_tops[index]->_login == login)
					break;
			}
			else if (mess_tops[index] == nullptr)
				break;
		}
	}
	Message* start = mess_tops[index];
	if (start == nullptr || start->_login!=login){
		temp = "Write your first message!\n";
		return temp;
		}
	else {
		do {
			if (start->sended == true) {
				temp += std::string(3,'\t');
			}
			temp += start->_text + '\n';
			start = start->next;
		} while (start != nullptr);
		return temp;
	}
}

std::string HashTable::showMessWithAll() const
{
	std::string temp;
	temp.clear();
	int counter = 0;
		for (int i = 0; i < mem_size; i++) {
			if (mess_tops[i] != nullptr) {
				Message* last = mess_tops[i];
				while (last->next != nullptr) {
					last = last->next;
				}
				counter++;
				temp += std::to_string(counter) + " " + last->_name + '|' + last->_login + "\n\t" + last->_text + '\n';
			}
		}
		return temp;
}

std::string HashTable::getLogHT(int number) const
{
	int counter = 0;
	for (int i = 0; i < mem_size; i++) {
		if (mess_tops[i] != nullptr) {
			counter++;
			if (counter == number) {
				return mess_tops[i]->_login;
			}
		}
	}
	return "Error";
}

bool HashTable::isEmpty()
{
	for (int i = 0; i < mem_size; i++) {
		if (mess_tops[i] != nullptr) {
			return false;
		}
	}
	return true;
}

void HashTable::resize()
{
	Message** save = mess_tops;
	int save_ms = mem_size;
	mem_size *= 2;
	mess_tops = new Message * [mem_size];
	count = 0;
	for (int i = 0; i < save_ms; i++) {
		mess_tops[i] = save[i];
	}
	delete[] save;
}

int HashTable::getCount() const
{
	return this->count;
}
