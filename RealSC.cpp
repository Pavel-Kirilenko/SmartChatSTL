#include"HeaderSC.h"
#include<iostream>

void userReg(string& curName, string& curPassWord)   // функция для ввода данных пользователя при регистрации или входе
{

    cout << "Введите имя: ";
    getline(cin, curName);
    cout << "Введите пароль: ";
    getline(cin, curPassWord);
}

PersMessage::PersMessage() // конструктор по умолчанию
{
	this->persName = "persName";        // от кого сообщение
	this->persDirWord = "persDirWord";  // адресат сообщения
	this->textInfo = "textInfo";        // содержание сообщения
}
string PersMessage::getCharValue(int fieldNumber) const // функция-геттер для вывода полей класса типа string
{
    switch (fieldNumber)
    {
    case 1: return this->persName; break;
    case 2: return this->persDirWord; break;
    case 3: return this->textInfo;
    }
}
void PersMessage::setValue(int numValue, string value) // функция сеттер для инициализации полей типа string
{
    (numValue == 1 ? this->persName = value : this->persDirWord = value);
}
void PersMessage::initPersMessage(string persName)  //  функция создания сообщения
{
    string _persDirWord;            // кому сообщение
    string _textInfo;               // содержание сообщения
    this->persName = persName;      // от кого сообщение
    cout << "Кому отправить сообщение (введите имя пользователя или 'всем'): ";
    getline(cin, _persDirWord);
    this->persDirWord = _persDirWord;
    cout << "Введите текст сообщения: ";
    getline(cin, _textInfo);
    this->textInfo = _textInfo;
} 

// 29.08.2024 by Pavel Kirilenko
