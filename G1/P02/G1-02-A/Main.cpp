#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include<WindowsX.h>

#define WINDOW_CLASS_NAME "WINCLASS1"

int iFlag = 0;



LRESULT CALLBACK WinProc(HWND hwnd,
			UINT msg,
			WPARAM wparam,
			LPARAM lparam)
{
	PAINTSTRUCT ps;//used in PAINT
	HDC hdc; //handle to a device context

	switch(msg)
	{
		case WM_CREATE:
		{
			return(0);
		}break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			return (0);
		}break;
		case WM_DESTROY:
		{
			iFlag++;

			if (iFlag == 5)
			{
				PostQuitMessage(0);
			}

			return(0);
		}break;
		default:break;
	}
	return(DefWindowProc(hwnd, msg, wparam, lparam));
}

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hprevinstance,
	LPSTR lpcmdline,
	int ncmdshow)
{

	WNDCLASSEX winclass; //structure that holds the clas
	HWND hwnd; //windows handles
	MSG msg; //message id
	
	winclass.cbSize = sizeof(WNDCLASSEX); //size of structure
	winclass.style = CS_HREDRAW | CS_VREDRAW| CS_OWNDC | CS_DBLCLKS;
	winclass.lpfnWndProc = WinProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_HAND);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	//register the class
	if(!RegisterClassEx(&winclass))
		return (0);


	if(!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"I want to play Diablo! III",
		WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE,
		0,0,
		500,500,
		NULL,
		NULL,
		hinstance,
		NULL))) 
		return (0);

	if(!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"I Really want to play Diablo! III",
		WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE,
		500,0,
		500,500,
		NULL,
		NULL,
		hinstance,
		NULL))) 
		return (0);

	if(!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"I Really Really want to play Diablo! III",
		WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE,
		750,250,
		500,500,
		NULL,
		NULL,
		hinstance,
		NULL))) 
		return (0);

	if(!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"I REALLY REALLY REALLY want to play Diablo! III",
		WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE,
		0,500,
		500,500,
		NULL,
		NULL,
		hinstance,
		NULL))) 
		return (0);
					
	if(!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"I REALLY REALLY REALLY REALLY REALLY REALLY want to play Diablo! III",
		WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE,
		500,500,
		500,500,
		NULL,
		NULL,
		hinstance,
		NULL))) 
		return (0);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return(msg.wParam);
}