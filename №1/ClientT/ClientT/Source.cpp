#include <iostream>
#include "Winsock2.h"
#include <string>
#pragma comment(lib, "WS2_32.lib")

using namespace std;

string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "Работа функции прервана";
		break;
	case WSAEACCES: msgText = "Разрешение отвергнуто";
		break;
	case WSAEFAULT: msgText = "Ошибочный адрес";
		break;
	case WSAEINVAL: msgText = "Ошибка в аргументе";
		break;
	case WSAEMFILE: msgText = "Слишком много файлов открыто";
		break;
	case WSAEWOULDBLOCK: msgText = "Ресурс временно недоступен";
		break;
	case WSAEINPROGRESS: msgText = "Операция в процессе развития";
		break;
	case WSAEALREADY: msgText = "Операция уже выполняется";
		break;
	case WSAENOTSOCK: msgText = "Сокет задан неправильно";
		break;
	case WSAEDESTADDRREQ: msgText = "Требуется адрес расположения";
		break;
	case WSAEMSGSIZE: msgText = "Сообщение слишком длинное";
		break;
	case WSAEPROTOTYPE: msgText = "Неправильный тип протокола для сокета";
		break;
	case WSAENOPROTOOPT: msgText = "Ошибка в опции протокола";
		break;
	case WSAEPROTONOSUPPORT: msgText = "Протокол не поддерживается";
		break;
	case WSAESOCKTNOSUPPORT: msgText = "Тип сокета не поддерживается";
		break;
	case WSAEOPNOTSUPP: msgText = "Операция не поддерживается";
		break;
	case WSAEPFNOSUPPORT: msgText = "Тип протоколов не поддерживается";
		break;
	case WSAEAFNOSUPPORT: msgText = "Тип адресов не поддерживается протоколом";
		break;
	case WSAEADDRINUSE: msgText = "Адрес уже используется";
		break;
	case WSAEADDRNOTAVAIL: msgText = "Запрошенный адрес не может быть использован";
		break;
	case WSAENETDOWN: msgText = "Сеть отключена";
		break;
	case WSAENETUNREACH: msgText = "Сеть не достижима";
		break;
	case WSAENETRESET: msgText = "Сеть разорвала соединение";
		break;
	case WSAECONNABORTED: msgText = "Программный отказ связи";
		break;
	case WSAECONNRESET: msgText = "Связь восстановлена";
		break;
	case WSAENOBUFS: msgText = "Не хватает памяти для буферов";
		break;
	case WSAEISCONN: msgText = "Сокет уже подключен";
		break;
	case WSAENOTCONN: msgText = "Сокет не подключен";
		break;
	case WSAESHUTDOWN: msgText = "Нельзя выполнить send: сокет завершил работу";
		break;
	case WSAETIMEDOUT: msgText = "Закончился отведенный интервал  времени";
		break;
	case WSAECONNREFUSED: msgText = "Соединение отклонено";
		break;
	case WSAEHOSTDOWN: msgText = "Хост в неработоспособном состоянии";
		break;
	case WSAEHOSTUNREACH: msgText = "Нет маршрута для хоста";
		break;
	case WSAEPROCLIM: msgText = "Слишком много процессов";
		break;
	case WSASYSNOTREADY: msgText = "Сеть не доступна";
		break;
	case WSAVERNOTSUPPORTED: msgText = "Данная версия недоступна";
		break;
	case WSANOTINITIALISED: msgText = "Не выполнена инициализация WS2_32.DLL";
		break;
	case WSAEDISCON: msgText = "Выполняется отключение";
		break;
	case WSATYPE_NOT_FOUND: msgText = "Класс не найден";
		break;
	case WSAHOST_NOT_FOUND: msgText = "Хост не найден";
		break;
	case WSATRY_AGAIN: msgText = "Неавторизированный хост не найден";
		break;
	case WSANO_RECOVERY: msgText = "Неопределенная ошибка";
		break;
	case WSANO_DATA: msgText = "Нет записи запрошенного типа";
		break;
	case WSA_INVALID_HANDLE: msgText = "Указанный дескриптор события  с ошибкой";
		break;
	case WSA_INVALID_PARAMETER: msgText = "Один или более параметров с ошибкой";
		break;
	case WSA_IO_INCOMPLETE: msgText = "Объект ввода-вывода не в сигнальном состоянии";
		break;
	case WSA_IO_PENDING: msgText = "Операция завершится позже";
		break;
	case WSA_NOT_ENOUGH_MEMORY: msgText = "Не достаточно памяти";
		break;
	case WSA_OPERATION_ABORTED: msgText = "Операция отвергнута";
		break;
	case WSAEINVALIDPROCTABLE: msgText = "Ошибочный сервис";
		break;
	case WSAEINVALIDPROVIDER: msgText = "Ошибка в версии сервиса";
		break;
	case WSAEPROVIDERFAILEDINIT: msgText = "Невозможно инициализировать сервис";
		break;
	case WSASYSCALLFAILURE: msgText = "Аварийное завершение системного вызова";
		break;
	default: msgText = "***ERROR***";
		break;

	};
	return msgText;
};

string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};

void prepareString(std::string &str, int i, std::string message)
{
	str.append(message);
	str.append(" ");

	if (i < 10) {
		str.append("00");
		str.append(std::to_string(i));
	}
	else if (i < 100) {
		str.append("0");
		str.append(std::to_string(i));
	}
	else {
		str.append(std::to_string(i));
	}
}

int main(int argc, TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	
	SOCKET  sS;           // дескриптор сокета 
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());
		SOCKET  cC;                          // серверный сокет

		if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("socket:", WSAGetLastError());

		SOCKADDR_IN serv;                    // параметры  сокета сервера
		serv.sin_family = AF_INET;           // используется IP-адресация  
		serv.sin_port = htons(2000);                   // TCP-порт 2000
		serv.sin_addr.s_addr = inet_addr("127.0.0.2");  // адрес сервера
		if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
			throw  SetErrorMsgText("connect:", WSAGetLastError());

		string hello = "Hello from Client ";
		
		int counter = 0;
		cout << "Input the number of messages: ";
		cin >> counter;

		for (int i = 1; i <= counter; i++)
		{
			char messageServer[50];
			memset(&messageServer, 0, 50);

			string messageCliet = "";

			prepareString(messageCliet, i, hello); 

			char *mass = new char[messageCliet.length() + 1];
			strcpy(mass, messageCliet.c_str());

			if ((send(cC, mass, strlen(mass), NULL)) == SOCKET_ERROR)
				throw  SetErrorMsgText("send:", WSAGetLastError());

			messageCliet = "";

			if ((recv(cC, messageServer, sizeof(messageServer), NULL)) == SOCKET_ERROR)
				throw  SetErrorMsgText("recv:", WSAGetLastError());

			prepareString(messageCliet, i + 1, hello);

			char *mass1 = new char[messageCliet.length() + 1];
			strcpy(mass1, messageCliet.c_str());

			if ((send(cC, mass1, strlen(mass1), NULL)) == SOCKET_ERROR)
				throw  SetErrorMsgText("send:", WSAGetLastError());

			delete[] mass;
			delete[] mass1;

		}

		//...........................................................
		if (closesocket(cC) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}

	return 0;
}
