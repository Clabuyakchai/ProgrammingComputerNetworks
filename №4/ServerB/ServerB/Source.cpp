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

bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen);

bool PutAnswerToClient(char* name, struct sockaddr* clientParameters, int *lengthOfClientParameters);

void FindTheSameServer(char* name);

SOCKET serverSocket;
SOCKADDR_IN serverParameters;

int main()
{

	WSADATA wsaData;
	SOCKADDR_IN clientParameters;
	int sizeOfClientParameters = sizeof(clientParameters);
	short port = 2000;
	char* serverName = "Hello";

	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("WSAStartup: ", WSAGetLastError());

		FindTheSameServer(serverName);

		if ((serverSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket: ", WSAGetLastError());

		serverParameters.sin_family = AF_INET;
		serverParameters.sin_port = htons(port);
		serverParameters.sin_addr.s_addr = INADDR_ANY;


		if (bind(serverSocket, (LPSOCKADDR)&serverParameters, sizeof(serverParameters)) == SOCKET_ERROR)
			throw SetErrorMsgText("bind: ", WSAGetLastError());

		while (true) {
			while (!GetRequestFromClient(serverName, port, (sockaddr*)&clientParameters, &sizeOfClientParameters)) {}
			PutAnswerToClient(serverName, (sockaddr*)&clientParameters, &sizeOfClientParameters);

			hostent* hst = gethostbyaddr((const char FAR *)&clientParameters.sin_addr.s_addr, 4, AF_INET);;

			cout << "Name Client: " << hst->h_name << endl;

			cout << "IP-address of client: " << inet_ntoa(clientParameters.sin_addr) << endl;
			cout << "Port: " << clientParameters.sin_port << endl;
			cout << endl;
		}

		if (closesocket(serverSocket) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("WSACleanup: ", WSAGetLastError());
	}

	catch (string message) {
		cout << message << endl;
	}
	system("pause");

	return 0;
}


bool GetRequestFromClient(char* name, short port, struct sockaddr* clientParameters, int* lengthOfClientParameters)
{
	char messageFromClient[100];
	int countOfRecievedBytes = 0;

	memset(&messageFromClient, 0, sizeof(messageFromClient));

	if (countOfRecievedBytes = recvfrom(serverSocket, messageFromClient, sizeof(messageFromClient), NULL, clientParameters, lengthOfClientParameters) == SOCKET_ERROR)
		throw SetErrorMsgText("recvfrom: ", WSAGetLastError());

	return strcmp(name, messageFromClient) == 0;
}

bool PutAnswerToClient(char* name, struct sockaddr* clientParameters, int *lengthOfClientParameters)
{
	int countOfSendedBytes = 0;

	if ((countOfSendedBytes = sendto(serverSocket, name, strlen(name), NULL, clientParameters, *lengthOfClientParameters)) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto: ", WSAGetLastError());

	return countOfSendedBytes > 0;
}

void FindTheSameServer(char* name)
{
	SOCKET broadcastSocket;
	SOCKADDR_IN broadcastParameters;
	SOCKADDR_IN sameServerParameters;

	if ((broadcastSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw SetErrorMsgText("socket: ", WSAGetLastError());

	int optval = 1;
	if (setsockopt(broadcastSocket, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
		throw SetErrorMsgText("setsockopt: ", WSAGetLastError());

	int timeout = 15000;
	if (setsockopt(broadcastSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
		throw SetErrorMsgText("setsockopt: ", WSAGetLastError());

	broadcastParameters.sin_family = AF_INET;
	broadcastParameters.sin_port = htons(2000);
	broadcastParameters.sin_addr.s_addr = INADDR_BROADCAST;

	int countOfSendedBytes = 0;
	int countOfReceivedBytes = 0;
	char messageFromServer[100];
	memset(&messageFromServer, 0, sizeof(messageFromServer));

	if ((countOfSendedBytes = sendto(broadcastSocket, name, strlen(name), NULL, (sockaddr*)&broadcastParameters, sizeof(broadcastParameters))) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto: ", WSAGetLastError());

	int sameServerParametersSizeOf = sizeof(sameServerParameters);

	if ((countOfReceivedBytes = recvfrom(broadcastSocket, messageFromServer, sizeof(messageFromServer), NULL, (sockaddr*)&sameServerParameters, &sameServerParametersSizeOf)) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT) {
			return;
		}
		throw SetErrorMsgText("recvfrom: ", WSAGetLastError());
	}

	if (strcmp(messageFromServer, name) == 0) {
		cout << "TRUE!" << endl;
		cout << "IP-address: " << inet_ntoa(sameServerParameters.sin_addr) << endl;
		cout << endl;
	}
	else {
		cout << "FALSE" << endl;
		cout << endl;
	}

	if (closesocket(broadcastSocket) == SOCKET_ERROR)
		throw SetErrorMsgText("closesocket: ", WSAGetLastError());
}