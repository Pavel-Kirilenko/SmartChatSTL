#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

void userReg(string& curName, string& curPassWord);   // функция для ввода данных пользователя при регистрации или входе

class PersMessage                                 // класс сообщений пользователей
{      
    string persName;
    string persDirWord;
    string textInfo;
public:
    PersMessage();
    string getCharValue(int fieldNumber) const;   // функция-геттер для вывода полей класса типа stringt
    void setValue(int numValue, string value);    // функция сеттер для инициализации полей типа string
    void initPersMessage(string persName);
};

class Chat
{
    map <string, string> persArray;               // массив с данными пользователей
    vector<PersMessage> messArray;                // массив с сообщениями
public:
    void entrChat(bool& persPresence, string& curName, string& curPassWord);     // войти в чат
	void regChat(bool& nameInChatAlready, bool& persPresence, string& curName, string& curPassWord);    // зарегистрироваться в чате
    bool ifEmpty();                               // если в массиве есть сообщения
    void showMess(string curName);                // показать сообщения
    void delMess();                               // удалить сообщение
    void sendMess(string curName);                // отправить сообщение
};

// 21.09.2024 by Pavel Kirilenko



