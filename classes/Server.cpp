#include "Server.h"


bool Server::init()		//���init����False����return�˳�����
{
	//num_Clients = 0;
	// ��������ʼ��winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return FALSE;
	}
	//�����׽���
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		closesocket(sServer);
		WSACleanup();
		return FALSE;
	}

	//�����׽��ַ�����ģʽ 
	unsigned long ul = 1;
	if (SOCKET_ERROR == ioctlsocket(sServer, FIONBIO, (unsigned long*)&ul))
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	// ׼��ͨ�ŵ�ַ
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = INADDR_ANY; //����������������ַ

	if (SOCKET_ERROR == ::bind(sServer, (const sockaddr*)&addrServer, sizeof(SOCKADDR_IN)))		//ʹ��::bind����������ͻ
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	//listen
	if (SOCKET_ERROR == listen(sServer, SOMAXCONN))
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	//�ȴ��ͻ�������
	return TRUE;
}

BOOL Server::AcceptClients()
{
	sockaddr_in addrClient;
	int addrClientLen = sizeof(addrClient);

	sClient = accept(sServer, (sockaddr *)&addrClient, &addrClientLen);
	if (INVALID_SOCKET == sClient)
	{
		cout << WSAGetLastError() << endl;
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return FALSE;
	}
	//++num_Clients;
	return TRUE;
}

BOOL Server::recv_Ser()
{
	char* recvBuf = const_cast<char*>(information.getRecvBuf().c_str());
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sClient, recvBuf, sizeof(recvBuf), 0))
	{
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return FALSE;
	}

	information.setSendAndRecv(recvBuf);
	return TRUE;
}

//��������
BOOL Server::send_Ser()
{
	char* sendBuf = const_cast<char*>(information.getSendBuf().c_str());
	if (SOCKET_ERROR == send(sClient, sendBuf, sizeof(sendBuf), 0))
	{
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}

Server::~Server()
{
	closesocket(sServer);
	closesocket(sClient);
	WSACleanup();
}