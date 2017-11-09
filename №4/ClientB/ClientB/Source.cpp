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

bool GetServer(char* serverName, short serverPort, struct sockaddr* from, int* flen);

SOCKET clientSocket;
SOCKADDR_IN serversParameters;

int main()
{
	
	char* serverName = "Hello";
	WSADATA wsaData;
	SOCKADDR_IN serverParameters;
	int sizeOfServerParameters = sizeof(serverParameters);
	short serverPort = 2000;

	try 
	{
		
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("WSAStartup: ", WSAGetLastError());

		if ((clientSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket: ", WSAGetLastError());

		int optval = 1;
		if (setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throw SetErrorMsgText("setsockopt: ", WSAGetLastError());

		serversParameters.sin_family = AF_INET;
		serversParameters.sin_port = htons(2000);
		serversParameters.sin_addr.s_addr = INADDR_BROADCAST;


		bool connectedWithServer = GetServer(serverName, serverPort, (sockaddr*)&serverParameters, &sizeOfServerParameters);

		if (connectedWithServer) {
			cout << "IP-address of server: " << inet_ntoa(serverParameters.sin_addr) << endl;
			cout << "Port: " << serverParameters.sin_port << endl;
		}

		if (closesocket(clientSocket) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("WSACleanup: ", WSAGetLastError());
	}
	catch (std::string errorMessage) {
		cout << SetErrorMsgText << endl;
	}
	system("pause");

	return 0;
}

bool GetServer(char* serverName, short serverPort, struct sockaddr* from, int* flen)
{
	int countOfSendedBytes = 0;
	int countOfReceivedBytes = 0;
	char messageFromServer[100];
	memset(&messageFromServer, 0, sizeof(messageFromServer));

	if ((countOfSendedBytes = sendto(clientSocket, serverName, strlen(serverName), NULL, (sockaddr*)&serversParameters, sizeof(serversParameters))) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto: ", WSAGetLastError());

	if ((countOfReceivedBytes = recvfrom(clientSocket, messageFromServer, sizeof(messageFromServer), NULL, from, flen)) == SOCKET_ERROR)
		throw SetErrorMsgText("recvfrom: ", WSAGetLastError());

	return strcmp(serverName, messageFromServer) == 0;
}