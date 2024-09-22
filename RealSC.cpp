﻿#include"HeaderSC.h"
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
void Chat::entrChat(bool& persPresence, string& curName, string& curPassWord)      // войти в чат
{
	if (persArray.size())  // если массив пользователей не равен нулю
	{
		userReg(curName, curPassWord);   // ввод данных пользователя при входе
		map <string, string>::iterator it = persArray.find(curName);
		if (it != persArray.end() && it->second == curPassWord) persPresence = true;  // успешный вход пользователя
		if (persPresence == false)
		{
			cout << "Пользователь с такими именем и паролем не найден. Проверьте правильность ввода данных" << endl;
		}
	}
	else
	{
		cout << "В чате еще нет зарегистрированных пользователей." << endl;
	}
}
void Chat::regChat(bool& nameInChatAlready, bool& persPresence, string& curName, string& curPassWord)    // зарегистрироваться в чате
{
	userReg(curName, curPassWord);                                // ввод имени и паролья пользователя при регистрации
	map <string, string>::iterator it = persArray.find(curName);
	if (it != persArray.end() || curPassWord == "" || curName == "") nameInChatAlready = true;  // если введенное имя уже есть или введены пустой пароль либо имя
	if (nameInChatAlready)                                        // то регистрации не происходит
	{
		cout << "Пользователь с таким именем уже есть в чате либо ввод некорректен (пустое имя или пароль). Повторите ввод." << endl;
		nameInChatAlready = false;     // возвращаем переменную проверки существования имени в чате в исходное состояние
	}
	else
	{
		persArray.insert({ curName, curPassWord });               // занесение данных пользователя в массив пользователей
		cout << "Добро пожаловать в чат, " << curName << "!" << endl;
		persPresence = true;
	}
}
bool Chat::ifEmpty()               // если в массиве есть сообщения
{
	return !messArray.empty();
}
void Chat::showMess(string curName)              // показать сообщения
{
	PersMessage arrMessage;  //  одно из сообщений в массиве
	string arrName;          //  текущее имя владельца сообщения
	string arrAdress;        //  текущее имя адресата сообщения
	string arrMessContent;   //  содержание текущего сообщения
	cout << "               ***               " << endl;  // обрамление сообщений для лучшего восприятия информации
	for (int i = 0; i < messArray.size(); ++i)            //  вывод на экран сообщений для конкретного пользователя
	{
		arrMessage = messArray[i];                        //  определение текущего сообщения
		arrName = arrMessage.getCharValue(1);             //  определение имени владельца сообщения
		arrAdress = arrMessage.getCharValue(2);           //  определение имени адресата сообщения
		arrMessContent = arrMessage.getCharValue(3);      //  определение содержания сообщения
		if (arrName == curName || arrAdress == curName || arrAdress == "всем")  //  если сообщение имеет отношение к текущему пользователю
		{
			cout << "Сообщение #" << i << " " << arrName << " пишет " << arrAdress << ":" << endl;  // то оно выводится на консоль
			cout << arrMessContent << endl;

		}
	}
	cout << "               ***               " << endl;   // обрамление сообщений для лучшего восприятия информации
}
void Chat::delMess()                 // удалить сообщение
{
	string inputMessNumber = "";
	int arrNumber;                //  номер удаляемого сообщения
	while (inputMessNumber == "") //  защита от некорректного ввода
	{
		cout << "Введите номер сообщения, которое хотите удалить: ";
		getline(cin, inputMessNumber);                  //  ввод номера сообщения, которое необходимо удалить
	}
	arrNumber = stoi(inputMessNumber);                  //  преобразование номера сообщения из формата string в формат int;
	if (arrNumber > -1 && arrNumber < messArray.size()) //  если введенный номер сообщения в границах массива сообщений
	{
		vector<PersMessage>::iterator it = messArray.begin() + arrNumber;
		messArray.erase(it);      //  сообщение удаляется
		cout << "Сообщение удалено!" << endl;
	}
	else cout << "Сообщение с таким номером не найдено!" << endl;          //  иначе выводится сообщение об ошибке
}
void Chat::sendMess(string curName)             // отправить сообщение
{
	PersMessage curMessage;       //  текущее сообщение
	cout << "Пользователи чата, доступные для общения:" << endl << "<всем> ";

	for (map<string, string>::iterator it = persArray.begin(); it != persArray.end(); ++it)
	{
		cout << "<" << it->first << "> ";      //  вывод имен других пользователей
	}
	cout << endl;                              //  переход на новую строку для лучшей читаемости информации
	curMessage.initPersMessage(curName);       //  формирование сообщения
	messArray.push_back(curMessage);
}

// 21.09.2024 by Pavel Kirilenko
