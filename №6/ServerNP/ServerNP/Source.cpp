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

int main()
{
	HANDLE sH;
	DWORD dwRead;
	DWORD dwWrite;

	if ((sH = CreateNamedPipe(TEXT("\\\\.\\pipe\\NONAME"),
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_WAIT | PIPE_READMODE_MESSAGE,
			1, NULL, NULL, INFINITE, NULL)) == INVALID_HANDLE_VALUE)
				throw SetPipeError("create: ", WSAGetLastError());

	if(!ConnectNamedPipe(sH, NULL))
		throw SetPipeError("connect: ", WSAGetLastError());

	do
	{
		char messageClient[50];

		memset(&messageClient, 0, sizeof(messageClient));

		if (!(ReadFile(sH, messageClient, sizeof(messageClient), &dwRead, NULL)))
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_BROKEN_PIPE)
				break;
			throw SetPipeError("read: ", WSAGetLastError());
		}	

		cout << messageClient << endl;

		if (!(WriteFile(sH, messageClient, strlen(messageClient), &dwWrite, NULL)))
			throw SetPipeError("write: ", WSAGetLastError());

		memset(&messageClient, 0, sizeof(messageClient));

		if (!(ReadFile(sH, messageClient, sizeof(messageClient), &dwRead, NULL)))
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_BROKEN_PIPE)
				break;
			throw SetPipeError("read: ", WSAGetLastError());
		}

		cout << messageClient << endl;

	} while (dwRead > 0);

	

	DisconnectNamedPipe(sH);

	CloseHandle(sH);
	return 0;
}