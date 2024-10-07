#include "Chat.h"
Chat::Chat()
{
	comMap["REGIS"] = COMMAND::REGIS;
	comMap["SIGNIN"] = COMMAND::SIGNIN;
	comMap["CHATW"] = COMMAND::CHATW;
	comMap["ALLUSER"] = COMMAND::ALLUSER;
	comMap["ALLCHATS"] = COMMAND::ALLCHATS;
	comMap["ADDMES"] = COMMAND::ADDMES;
}

Chat::~Chat()
{
	for (int i = 0; i < _User.size(); i++) {
		delete _User[i];
	}
}


Chat::COMMAND Chat::getCommand(std::string& commandFromUser)
{
	std::string cmdFromUSer = parsedPart(commandFromUser);
    return comMap.find(cmdFromUSer)->second;
}

std::string Chat::parsedPart(std::string& stringLine)
{
	std::string parsedPart = stringLine.substr(0,stringLine.find(delim));
	stringLine.erase(0,stringLine.find(delim) + 1);
    return parsedPart;
}

std::string Chat::regis(std::string& commandFromUser)
{
	std::string login = parsedPart(commandFromUser);
	std::string name = parsedPart(commandFromUser);
	std::string tmppasw = parsedPart(commandFromUser);
	char pasw[LOGINLENGTH];
	std::fill(pasw, pasw+LOGINLENGTH, '1');
	for(int i = 0; i < tmppasw.size(); i++){
		pasw[i] = tmppasw[i];
	}
	std::string succes = "succes";
	uint* sh1 = sha1(pasw, LOGINLENGTH);
	User* newUser = nullptr;
	if (_User.empty()) {
		newUser = new User(name, login, sh1);
		_User.push_back(newUser);
		return succes;
	}
	else {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() == login) {
				std::string notSucces = "Login is busy, try another one!\n";
				return notSucces;
			}
			else {
				newUser = new User(name, login, sh1);
				_User.push_back(newUser);
				return succes;
			}
		}
	}
	std::string ubAnswer = "Something went wrong\n";
	return ubAnswer;
}

std::string Chat::auth(std::string& commandFromUser)
{
	std::string login = parsedPart(commandFromUser);
	std::string tmppasw = parsedPart(commandFromUser);
	char pasw[LOGINLENGTH];
	std::fill(pasw, pasw+LOGINLENGTH, '1');
	for(int i = 0; i < tmppasw.size(); i++){
		pasw[i] = tmppasw[i];
	}
	uint* sh1 = sha1(pasw, LOGINLENGTH);
	std::string succes = "succes";
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			if (_User[i]->checkPass(sh1)) {
				return succes;
			}
			else {
				std::string wrongPasw = "Incorrect password!\n";
				return wrongPasw;
			}
		}
	}
	std::string nonExistUser = "There is no user with this login.!\n";
	return nonExistUser;
}

std::string Chat::chatw(std::string& commandFromUser)
{
	std::string text;
	User* tmpMe = nullptr;
	User* tmpOther = nullptr;
	std::string wayOfChoose = parsedPart(commandFromUser);
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	std::string tmpNumb = parsedPart(commandFromUser);


	if(std::stoi(tmpNumb) > _User.size() - 1)
		return "error input";


	if(wayOfChoose == "userway"){
		tmpOther = this->userChoice(std::stoi(tmpNumb),tmpMe);
	}
	else{
		tmpOther = this->chatChoice(std::stoi(tmpNumb),tmpMe);
	}
	text.clear();
	return text = tmpMe->showOneChat(tmpOther);
}

std::string Chat::addmes(std::string& commandFromUser)
{
	User* tmpMe = nullptr;
	User* tmpOther = nullptr;
	std::string wayOfChoose = parsedPart(commandFromUser);
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	std::string tmpNumb = parsedPart(commandFromUser);
	if(wayOfChoose == "userway"){
		tmpOther = this->userChoice(std::stoi(tmpNumb),tmpMe);
	}
	else{
		tmpOther = this->chatChoice(std::stoi(tmpNumb),tmpMe);
	}
	std::string text = parsedPart(commandFromUser);
	tmpMe->sendMes(text, tmpMe, tmpOther);
	text.clear();	
	return text = tmpMe->showOneChat(tmpOther);
}

std::string Chat::alluser(std::string& commandFromUser)
{
	std::string temp;
	User* tmpMe = nullptr;
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	temp += std::to_string(_User.size() - 1) + this->delim;
	int counter = 0;
	if (_User.size() > 1) {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() != tmpMe->getLog()) {
				counter++;
				temp += std::to_string(counter) + " " + _User[i]->getName() + "  |  " + _User[i]->getLog() + "\n";
			}
		}
		return temp;
	}
	else
		return temp += "You are the only user\n";
}

std::string Chat::allchats(std::string& commandFromUser)
{
	std::string temp;
	User* tmpMe = nullptr;
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	temp.clear();
	temp += std::to_string(tmpMe->getCountOfChats()) + this->delim;
	if (!tmpMe->isEmptyMes()) {
		temp += tmpMe->showAllChats();
		return temp;
	}
	else{
		return temp += "There are no dialogues yet\n";
	}
}


User *Chat::findMain(std::string login)
{
    for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			return _User[i];
		}
	}
	return nullptr;
}

User *Chat::chatChoice(int number, User *me)
{
	if (number < 1) {
		return nullptr;
	}
	std::string login = me->getFriendLogInChat(number);
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			return _User[i];
		}
	}
	return nullptr;
}

User* Chat::userChoice(int number, User* me)
{
	if (number < 1) {
		return nullptr;
	}
	int counter = 0;
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() != me->getLog()) {
			counter++;
			if (counter == number) {
				return _User[i];
				
			}
		}
	}
	std::cout << "Error!\n";
	return nullptr;
}



