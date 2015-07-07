////#define INITGUID
////#define WIN32_LEAN_AND_MEAN
////#include <Windows.h>
////#include <WinSock2.h>
//
//#ifndef CSOCKET_H
//#define CSOCKET_H
//
////define error codes
//#ifndef ENUM_ERRORCODES
//#define ERROR_CODES
//enum ERRORCODES
//{
//	SUCCESS		= 800,
//	FAIL		= 801,
//	INITNETFAIL	= 802,
//	INITNETSUCC	= 803,
//};
//#endif
//
////define socket type (server, client)
//#ifndef ENUM_SOCKETTYPE
//#define ENUM_SOCKETTYPE
//enum SOCKETTYPE
//{
//	SERVER,
//	CLIENT,
//};
//#endif
//
////custom message for WSAAsyncSelect()
//#define ASYNC_MSG	5000
//
////socket class
//class CSOCKET {
//
//public:
//
//	CSOCKET(int Port = 2081);
//
//	int  Connect(HWND hWnd, char* ServerIP);
//	int  Bind(HWND hWnd, char* ServerIP);
//	int  Send(char* cMessage, int sendLen);
//	int  Recv(char* cMessage, int sendLen);
//	int  Accept();
//	void  Listen();
//	void Disconnect();
//
//	SOCKET skSocket;
//	SOCKET ckSocket;
//	sockaddr_in addrSock;
//	sockaddr_in addrSock2;
//	int iPort;
//	char RecvData[40];
//
//
//};
//
//
//
//
////
////default constructor
////
//CSOCKET::CSOCKET(int Port) : iPort(Port)
//{
//	
//	WSADATA wsData;
//	WORD Version = MAKEWORD(2, 0);
//	skSocket = INVALID_SOCKET;
//
//	WSAStartup(Version, &wsData);
//	iPort = Port;
//}
//
////
////connect function (CLIENT)
////
//int CSOCKET::Connect(HWND hWnd, char* ServerIP)
//{
//	//set up socket information
//	memset(&addrSock, 0, sizeof(sockaddr_in));
//	addrSock.sin_family = AF_INET;
//	addrSock.sin_addr.s_addr = inet_addr(ServerIP);		//address
//	addrSock.sin_port = htons(iPort);					//port 
//
//	skSocket = socket(AF_INET, SOCK_STREAM, 0);	
//	if(skSocket == INVALID_SOCKET)
//	{
//		return INITNETFAIL;
//	}
//
//	//asycronous funtion
//	int nRet = WSAAsyncSelect(skSocket, hWnd, ASYNC_MSG, FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE);
//
//	if(nRet == SOCKET_ERROR)
//	{
//		return INITNETFAIL;
//	}     
//
//	//connect
//	nRet = connect(skSocket, (sockaddr*)&addrSock, sizeof(sockaddr_in));
//
//	if(nRet == SOCKET_ERROR)
//	{
//		return INITNETFAIL;
//	}
//
//	return SUCCESS;
//}
//
////
////Bind function (SERVER)
////
//int CSOCKET::Bind(HWND hWnd, char* ServerIP)
//{
//
//	skSocket = socket(AF_INET, SOCK_STREAM, 0);
//	
//	if(skSocket == INVALID_SOCKET)
//	{
//		MessageBox(NULL, "socket fail", ":WinSock", MB_OK);
//		return false;
//	}
//
//	//server information
//	
//	addrSock.sin_family = AF_INET;
//	addrSock.sin_addr.s_addr = inet_addr(ServerIP);		//address
//	addrSock.sin_port = htons(1080);					//port 
//
//	
//
//	//asyncronous function
//	WSAAsyncSelect(skSocket, hWnd, ASYNC_MSG, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);
//
//	//bind to client
//	if( bind(skSocket, (sockaddr*) &addrSock, sizeof(sockaddr)) == SOCKET_ERROR)
//	{
//		MessageBox(NULL, "Binding.. fail", ":WinSock", MB_OK);
//		Disconnect();
//		return FAIL;
//	}
//	else 
//	{
//		MessageBox(NULL, "Waiting for player 2...", "Player 1", MB_OK);
//		Listen();
//		return SUCCESS;
//	}
//}
//
//
////
////listen function
////
//void CSOCKET::Listen()
//{
//	int iresult = listen(skSocket, SOMAXCONN);
//	if(iresult == SOCKET_ERROR)
//		WSACleanup();
//}
//
//
////
////disconnect funtion
////
//void CSOCKET::Disconnect()
//{
//	closesocket(skSocket);
//	closesocket(ckSocket);
//}
//
//
////
////accept function 
////
//int CSOCKET::Accept()
//{
//	MessageBox(NULL, "Connected", "Server", MB_OK);
//	int clientSize = sizeof(sockaddr_in);
//
//	ckSocket = accept(skSocket, (struct sockaddr*)&ckSocket, &clientSize);
//	if(ckSocket == INVALID_SOCKET)
//	{
//		return FAIL;
//	}
//	else
//	{
//		return SUCCESS;
//	}
//}
//
//
////
////Send function
////
//int CSOCKET::Send(char* cMessage, int sendLen)
//{
//	return send(ckSocket, cMessage, sendLen, NULL);
//}
//
//
////
////recive function
////
//int CSOCKET::Recv(char* cMessage, int sendLen)
//{
//	return recv(ckSocket, cMessage, sendLen, NULL);
//}
//
//#endif
//
