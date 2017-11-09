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
	case WSAEINTR: msgText = "������ ������� ��������";
		break;
	case WSAEACCES: msgText = "���������� ����������";
		break;
	case WSAEFAULT: msgText = "��������� �����";
		break;
	case WSAEINVAL: msgText = "������ � ���������";
		break;
	case WSAEMFILE: msgText = "������� ����� ������ �������";
		break;
	case WSAEWOULDBLOCK: msgText = "������ �������� ����������";
		break;
	case WSAEINPROGRESS: msgText = "�������� � �������� ��������";
		break;
	case WSAEALREADY: msgText = "�������� ��� �����������";
		break;
	case WSAENOTSOCK: msgText = "����� ����� �����������";
		break;
	case WSAEDESTADDRREQ: msgText = "��������� ����� ������������";
		break;
	case WSAEMSGSIZE: msgText = "��������� ������� �������";
		break;
	case WSAEPROTOTYPE: msgText = "������������ ��� ��������� ��� ������";
		break;
	case WSAENOPROTOOPT: msgText = "������ � ����� ���������";
		break;
	case WSAEPROTONOSUPPORT: msgText = "�������� �� ��������������";
		break;
	case WSAESOCKTNOSUPPORT: msgText = "��� ������ �� ��������������";
		break;
	case WSAEOPNOTSUPP: msgText = "�������� �� ��������������";
		break;
	case WSAEPFNOSUPPORT: msgText = "��� ���������� �� ��������������";
		break;
	case WSAEAFNOSUPPORT: msgText = "��� ������� �� �������������� ����������";
		break;
	case WSAEADDRINUSE: msgText = "����� ��� ������������";
		break;
	case WSAEADDRNOTAVAIL: msgText = "����������� ����� �� ����� ���� �����������";
		break;
	case WSAENETDOWN: msgText = "���� ���������";
		break;
	case WSAENETUNREACH: msgText = "���� �� ���������";
		break;
	case WSAENETRESET: msgText = "���� ��������� ����������";
		break;
	case WSAECONNABORTED: msgText = "����������� ����� �����";
		break;
	case WSAECONNRESET: msgText = "����� �������������";
		break;
	case WSAENOBUFS: msgText = "�� ������� ������ ��� �������";
		break;
	case WSAEISCONN: msgText = "����� ��� ���������";
		break;
	case WSAENOTCONN: msgText = "����� �� ���������";
		break;
	case WSAESHUTDOWN: msgText = "������ ��������� send: ����� �������� ������";
		break;
	case WSAETIMEDOUT: msgText = "���������� ���������� ��������  �������";
		break;
	case WSAECONNREFUSED: msgText = "���������� ���������";
		break;
	case WSAEHOSTDOWN: msgText = "���� � ����������������� ���������";
		break;
	case WSAEHOSTUNREACH: msgText = "��� �������� ��� �����";
		break;
	case WSAEPROCLIM: msgText = "������� ����� ���������";
		break;
	case WSASYSNOTREADY: msgText = "���� �� ��������";
		break;
	case WSAVERNOTSUPPORTED: msgText = "������ ������ ����������";
		break;
	case WSANOTINITIALISED: msgText = "�� ��������� ������������� WS2_32.DLL";
		break;
	case WSAEDISCON: msgText = "����������� ����������";
		break;
	case WSATYPE_NOT_FOUND: msgText = "����� �� ������";
		break;
	case WSAHOST_NOT_FOUND: msgText = "���� �� ������";
		break;
	case WSATRY_AGAIN: msgText = "������������������ ���� �� ������";
		break;
	case WSANO_RECOVERY: msgText = "�������������� ������";
		break;
	case WSANO_DATA: msgText = "��� ������ ������������ ����";
		break;
	case WSA_INVALID_HANDLE: msgText = "��������� ���������� �������  � �������";
		break;
	case WSA_INVALID_PARAMETER: msgText = "���� ��� ����� ���������� � �������";
		break;
	case WSA_IO_INCOMPLETE: msgText = "������ �����-������ �� � ���������� ���������";
		break;
	case WSA_IO_PENDING: msgText = "�������� ���������� �����";
		break;
	case WSA_NOT_ENOUGH_MEMORY: msgText = "�� ���������� ������";
		break;
	case WSA_OPERATION_ABORTED: msgText = "�������� ����������";
		break;
	case WSAEINVALIDPROCTABLE: msgText = "��������� ������";
		break;
	case WSAEINVALIDPROVIDER: msgText = "������ � ������ �������";
		break;
	case WSAEPROVIDERFAILEDINIT: msgText = "���������� ���������������� ������";
		break;
	case WSASYSCALLFAILURE: msgText = "��������� ���������� ���������� ������";
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