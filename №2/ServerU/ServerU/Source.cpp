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


int main(int argc, TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	SOCKET  sS;           // ���������� ������ 
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());
		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("socket:", WSAGetLastError());

		SOCKADDR_IN serv;                     // ���������  ������ sS
		serv.sin_family = AF_INET;           // ������������ IP-���������  
		serv.sin_port = htons(2000);          // ���� 2000
		serv.sin_addr.s_addr = INADDR_ANY;   // ����� ����������� IP-����� 

		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw  SetErrorMsgText("bind:", WSAGetLastError());

		/////////////////////
		/*string start = "";
		cout << "GO/EXIT: ";
		cin >> start;

		while (start == "GO")
		{*/
			SOCKADDR_IN from;               // ���������  ������ �������
			memset(&from, 0, sizeof(from));   // �������� ������
			int lc = sizeof(from);
			

			SOCKADDR_IN to;                    // ���������  ������ �������
			to.sin_family = AF_INET;           // ������������ IP-���������  
			to.sin_port = htons(2000);                   // TCP-���� 2000
			to.sin_addr.s_addr = inet_addr("127.0.0.1");  // ����� �������

			int bufClientMessage = 0;

			do
			{
				char messageClient[50];

				memset(&messageClient, 0, sizeof(messageClient));

				if ((bufClientMessage = recvfrom(sS, messageClient, sizeof(messageClient), NULL,
					(sockaddr*)&from, &lc)) == SOCKET_ERROR)
					throw  SetErrorMsgText("recv:", WSAGetLastError());

				cout << messageClient << endl;

				if (bufClientMessage == 0)
					break;
				
				if ((sendto(sS, messageClient, strlen(messageClient) + 1, NULL,
					(sockaddr*)&from, lc)) == SOCKET_ERROR)
					throw  SetErrorMsgText("recv:", WSAGetLastError());

				memset(&messageClient, 0, sizeof(messageClient));

				if ((bufClientMessage = recvfrom(sS, messageClient, sizeof(messageClient), NULL,
					(sockaddr*)&from, &lc)) == SOCKET_ERROR)
					throw  SetErrorMsgText("recv:", WSAGetLastError());

				cout << messageClient << endl;

			} while (bufClientMessage > 0);
			
			/*cout << "GO/EXIT: ";
			cin >> start;

		}*/
		
		////////////////////////////////////////

		if (closesocket(sS) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
	}

	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}

	system("pause");

	return 0;
}