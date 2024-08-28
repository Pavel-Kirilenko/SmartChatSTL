#pragma once
#include <string>

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

// 29.08.2024 by Pavel Kirilenko



