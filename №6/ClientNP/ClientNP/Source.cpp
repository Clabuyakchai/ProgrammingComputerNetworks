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

string SetPipeError(string msgText, int code)
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

int main()
{
	HANDLE cH;
	string hello = "Hello from Client ";
	DWORD dwWrite;
	DWORD dwRead;

	if((cH = CreateFile(TEXT("\\\\Clabuyakchai\\pipe\\NONAME"), GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw SetPipeError("createfile:", WSAGetLastError());
			
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

		if (!(WriteFile(cH, mass, strlen(mass), &dwWrite, NULL)))
			throw SetPipeError("write: ", WSAGetLastError());

		messageCliet = "";

		if (!(ReadFile(cH, messageServer, sizeof(messageServer), &dwRead, NULL)))
			throw SetPipeError("read: ", WSAGetLastError());

		prepareString(messageCliet, i + 1, hello);

		char *mass1 = new char[messageCliet.length() + 1];
		strcpy(mass1, messageCliet.c_str());

		if (!(WriteFile(cH, mass1, strlen(mass1), &dwWrite, NULL)))
			throw SetPipeError("write: ", WSAGetLastError());

		delete[] mass;
		delete[] mass1;
	}
	CloseHandle(cH);

	return 0;
}