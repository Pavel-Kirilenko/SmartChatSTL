#include <iostream>
#include "HeaderSC.h"
#include <map>
#include <vector>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");                         // строка для корректного отображения кириллических символов
	map <string, string> persArray;              // создание массива с данными пользователей
	vector<PersMessage> messArray;               // создание массива с сообщениями
	string curName;          //  текущее имя пользователя
	string curPassWord;      //  текущий пароль пользователя
	PersMessage curMessage;  //  текущее сообщение
	PersMessage arrMessage;  //  одно из сообщений в массиве (во внутренних циклах)
	string arrName;          //  текущее имя владельца сообщения (во внутренних циклах)
	string arrAdress;        //  текущее имя адресата сообщения (во внутренних циклах)
	string arrMessContent;   //  содержание текущего сообщения (во внутренних циклах)
	string inputMessNumber;  //  вводимый номер сообщения при удалении сообщений (тип string для устойчивости программы против некорректного ввода)
	int messNumber = 0;      //  номер текущего сообщения (сообщения нумеруются от нуля и далее в порядке создания)
	int arrNumber = 0;       //  номер текущего сообщения (во внутренних циклах)
	bool persPresence = false;       //  переменная, показывающая существование пользователя с данным именем и паролем
	bool nameInChatAlready = false;  //  переменная, которая показывает при регистрации есть ли уже в чате пользователь с таким именем

	string contProcNumber = "0";     // переменная, которая отвечает за продолжение программы, тип продиктован необходимостью устойчивости
	                                 // программы при вводе некорректных данных
	while (true)
	{
		while (persPresence == false)  // цикл продолжается пока пользователь не вошел в аккаунт или не зарегистрировался
		{
			while (contProcNumber != "1" && contProcNumber != "2" && contProcNumber != "3")  //  защита от некорректного ввода выбора дальнейших действий
			{
				cout << "Выберите действие: 1 - войти; 2 - зарегистрироваться; 3 - выход из программы." << endl;
				getline(cin, contProcNumber);
			}
			persPresence = false;
			if (contProcNumber == "1")
			{
				if (persArray.size())  // если массив пользователей не равен нулю
				{
					userReg(curName, curPassWord);   // ввод данных пользователя при входе
					map <string, string>::iterator it = persArray.find(curName);
					if (it != persArray.end() && it->second == curPassWord) persPresence = true;  // успешный вход пользователя
					if (persPresence == false)
					{
						cout << "Пользователь с такими именем и паролем не найден. Проверьте правильность ввода данных" << endl;
						contProcNumber = "0";
					}
				}
				else
				{
					cout << "В чате еще нет зарегистрированных пользователей." << endl;
					contProcNumber = "0";
				}
			}

			if (contProcNumber == "2")
			{
				userReg(curName, curPassWord);                                // ввод имени и паролья пользователя при регистрации
				map <string, string>::iterator it = persArray.find(curName);
				if (it != persArray.end() || curPassWord == "" || curName == "") nameInChatAlready = true;  // если введенное имя уже есть или введены пустой пароль либо имя
				if (nameInChatAlready)                                        // то регистрации не происходит
				{
					cout << "Пользователь с таким именем уже есть в чате либо ввод некорректен (пустое имя или пароль). Повторите ввод." << endl;
				}
				else
				{
					persArray.insert({ curName, curPassWord });               // занесение данных пользователя в массив пользователей
					cout << "Добро пожаловать в чат, " << curName << "!" << endl;
					persPresence = true;
				}
				nameInChatAlready = false;     // возвращаем переменную проверки существования имени в чате в исходное состояние
			}

			if (contProcNumber == "3") break;  //  выход из цикла
		}
		if (contProcNumber == "3") break;      //  выход из программы

		if (!messArray.empty())                //  если в массиве есть сообщения 
		{
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
		contProcNumber = "0";
		while (true) // цикл продолжается пока пользователь не захочет выйти из профиля или из программы
		{
			while (contProcNumber != "1" && contProcNumber != "2" && contProcNumber != "3")  //  защита от некорректного ввода выбора дальнейших действий
			{
				cout << "Выберите действие: 1 - отправить сообщение; 2 - удалить сообщение ; 3 - выйти из профиля." << endl;
				getline(cin, contProcNumber);
			}
			if (contProcNumber == "3") //  если выбран выход из профиля
			{
				cout << endl;          //  пустая строка для лучшего восприятия информации
				persPresence = false;  //  пользователь выходит из профиля
				break;                 //  выход из цикла
			}
			if (contProcNumber == "2") //  если выбрано удаление сообщения
			{
				inputMessNumber = "";
				while (inputMessNumber == "") //  защита от некорректного ввода
				{
					cout << "Введите номер сообщения, которое хотите удалить: ";
					getline(cin, inputMessNumber);                  //  ввод номера сообщения, которое необходимо удалить
				}
				arrNumber = stoi(inputMessNumber);                  //  преобразование номера сообщения из формата string в формат int;
				if (arrNumber > -1 && arrNumber < messArray.size()) //  если введенный номер сообщения в границах массива сообщений
				{
					vector<PersMessage>::iterator it = messArray.begin() + arrNumber;
					messArray.erase(it);  //  сообщение удаляется
					cout << "Сообщение удалено!" << endl;
				}
				else cout << "Сообщение с таким номером не найдено!" << endl;          //  иначе выводится сообщение об ошибке
				contProcNumber = "0";
			}
			if (contProcNumber == "1")          //  если выбрана отправка сообщения
			{
				cout << "Пользователи чата, доступные для общения:" << endl << "<всем> ";

				for (map<string, string>::iterator it = persArray.begin(); it != persArray.end(); ++it)
				{
					cout << "<" << it->first << "> ";      //  вывод имен других пользователей
				}
				cout << endl;                              //  переход на новую строку для лучшей читаемости информации
				curMessage.initPersMessage(curName);       //  формирование сообщения
				messArray.push_back(curMessage);
				contProcNumber = "0";
			}
		}

		contProcNumber = "0";

	}
	return 0;
}

// 29.08.2024 by Pavel Kirilenko




