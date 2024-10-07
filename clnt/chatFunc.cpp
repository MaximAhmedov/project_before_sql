#include "chatFunc.h"

chatFunc::chatFunc()
{
}

chatFunc::~chatFunc()
{
    this->serv.stopServer();
}

bool chatFunc::start(const char *x)
{
    return this->serv.startServer(x);
}

std::string chatFunc::showMainMenu()
{
    return "\t1 - Sign in\n \t2 - Registration\n \t3 - Exit\n";
}

bool chatFunc::signIn()
{
    clear_screen();
    std::string tmpLogin;
    std::string tmpPass;
    std::string signcom;
    std::cout << "Enter 0 to return or follow the commands:\nEnter login\n";
    std::cin >> this->_login;
    if (this->_login[0] == '0' && this->_login.size() == 1)
		    return false;
    std::cout << "Enter pasword\n";
    std::cin >> tmpPass;
    if (tmpPass[0] == '0' && tmpPass.size() == 1)
		    return false;
    signcom = "SIGNIN%" + this->_login + '%' + tmpPass;
    this->serv.sendTo(signcom);
    return this->checkAuth(this->serv.recFrom());
}

bool chatFunc::registration()
{
    clear_screen();
    std::string tmpName;
    std::string tmpLogin;
    std::string tmpPass;
    std::string tmpPass2;
    std::string regcom;
    while(true){
        std::cout << "Enter 0 to return or follow the commands:\nEnter name\n";
        std::cin >> tmpName;
        if (tmpName[0] == '0' && tmpName.size() == 1)
		    return false;
        std::cout << "Enter login\n";
        std::cin >> this->_login;
        if (this->_login[0] == '0' && this->_login.size() == 1)
		    return false;
        std::cout << "Enter password\n";
        std::cin >> tmpPass;
        if (tmpPass[0] == '0' && tmpPass.size() == 1)
		    return false;
        std::cout << "Repeat password\n";
        std::cin >> tmpPass2;
        if (tmpPass2[0] == '0' && tmpPass2.size() == 1)
		    return false;
        if(tmpPass == tmpPass2){
            regcom = "REGIS%" + this->_login + '%' + tmpName + '%' + tmpPass + '%' + tmpPass2;
            this->serv.sendTo(regcom);
            return this->checkAuth(this->serv.recFrom());
        }
        else{
            clear_screen();
            std::cout << "Incorrect re-password entry!\n";
        }
    }
}

bool chatFunc::checkAuth(std::string &checkstr)
{
    if(checkstr == "succes")
        return true;
    else{
        std::cout << checkstr << '\n';
        return false;}
}

std::string chatFunc::showSecondMenu()
{
    return "\t1 - All users\n \t2 - My messages\n \t3 - Sign out\n";
}

void chatFunc::chatting(int x, std::string& wayOfChoose)
{
    std::string text;
    std::string str = std::to_string(x);
    std::string tmpstr = "CHATW%" + wayOfChoose + this->_login + '%' + str;
    std::cin.ignore();
    while(true){
        clear_screen();
        this->serv.sendTo(tmpstr);
        text.clear();
        text = this->serv.recFrom();

        std::cout << text << "\nEnter your message and press Enter to send, to return send 0\n";
        text.clear();
        std::getline(std::cin, text, '\n');
        
        if (text[0] == '0' && text.size() == 1){
            clear_screen();
            break;
        }
        else{
            std::string tmpstr2 = "ADDMES%" + wayOfChoose + this->_login + '%' + str + '%' + text;
            this->serv.sendTo(tmpstr2);
        }
    }
}

void chatFunc::showAllUsers()
{
    clear_screen();
    int x = 0;
    std::string tmpstr = "ALLUSER%" + this->_login;
    this->serv.sendTo(tmpstr);
    tmpstr.clear();
    tmpstr = this->serv.recFrom();
    int amountOfUsers = std::stoi(parsedPart(tmpstr));
    tmpstr += "\nSelect a user or enter 0 to return\n";
    while(true){
    std::cout << tmpstr;
    this->inputCommand(x, tmpstr);
    if(x >= 1 && x <= amountOfUsers){
        std::string wayOfChoose = "userway%";
        this->chatting(x, wayOfChoose);
    }
    else if(x >= 1 && x > amountOfUsers){
        clear_screen();
        std::cout << "Non-existent user number!!!\n";
        continue;
    }
    else
        return;
    }
}

void chatFunc::showAllChats()
{
    clear_screen();
    int x = 0;
    std::string tmpstr = "ALLCHATS%" + this->_login;
    this->serv.sendTo(tmpstr);
    tmpstr.clear();
    tmpstr = this->serv.recFrom();
    int amountOfChats = std::stoi(parsedPart(tmpstr));
    tmpstr += "\nSelect the dialog number or 0 to return\n";
    while(true){
    std::cout << tmpstr;
    this->inputCommand(x, tmpstr);
    if(x >= 1 && x <=amountOfChats){
        std::string wayOfChoose = "chatway%";
        this->chatting(x, wayOfChoose);
    }
    else if(x >= 1 && x > amountOfChats){
        clear_screen();
        std::cout << "Non-existent dialogue number!!!\n";
        continue;
    }
    else
        return;
    }
}

void chatFunc::signOut()
{
    this->_login.clear();
}

int chatFunc::inputCommand(int& x, std::string interfaceLine)
{
    while(!(std::cin >> x))
    {
        clear_screen();
        std::cout << "Incorrect input!!!\n\n";
        std::cout << interfaceLine;
        std::cin.clear();
        std::cin.ignore(max_size, '\n');   
    }
    return x;
}

std::string chatFunc::parsedPart(std::string &stringLine)
{
    std::string parsedPart = stringLine.substr(0,stringLine.find(delim));
	stringLine.erase(0,stringLine.find(delim) + 1);
    return parsedPart;
}
