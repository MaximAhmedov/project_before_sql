#pragma once
#include <iostream>
#include <cstring>
class HashTable {
public:

    HashTable();
    ~HashTable();

    void send(std::string& text, const std::string& name, const std::string& login);
    void getBy(std::string& text, const std::string& name, const std::string& login);
    std::string showMessages(const std::string& name, const std::string& login);
    std::string showMessWithAll()const;
    std::string getLogHT(int number) const;
    bool isEmpty();
    void resize();

    int getCount() const;

private:
    class Message {
    public:
        std::string _text;
        std::string _name;
        std::string _login;
        Message* next;
        bool sended;
    
        Message(std::string& text,const std::string& name, const std::string& login) : _text(text), _name(name), _login(login) {
            next = nullptr;
            sended = true;
        }
        ~Message() {
            if (next != nullptr)
                delete next;
        }
    };
    int hash_func(const std::string& login);

    Message** mess_tops;
    int mem_size;
    int count = 0;
};

