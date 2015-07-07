#define WIN32_LEAN_AND_MEAN


#include <Windows.h>
#include <WindowsX.h>
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include <mmsystem.h>



#define WINDOW_CLASS_NAME "WINCLASS1"
int mouse_x_down = 0;
int mouse_y_down = 0;
int mouse_x_up = 0;
int mouse_y_up = 0;
char buffer[80];
bool bE = false, bX = false, bI = false, bT = false, bEXIT = false;
HINSTANCE hinstance_app;




LRESULT CALLBACK WinProc(HWND hwnd,
	UINT msg,
	WPARAM wparam,
	LPARAM lparam)
{
	PAINTSTRUCT ps;//used in PAINT
	HDC hdc; //handle to a device context
	RECT rect;

	switch(msg)
	{
	case WM_CREATE:
		{	

			return(0);
		}break;
	case WM_COMMAND:
		{
			switch(LOWORD(wparam))
			{
			case MENU_FILE_EXIT:
				{
					PlaySound("ID_WAVE1" , hinstance_app, SND_ASYNC | SND_RESOURCE);
					Sleep(1000);
					PlaySound(NULL, hinstance_app, SND_PURGE);

					PostQuitMessage(0);
				}break;
			case MENU_COLOR_RED:
				{
					hdc = GetDC(hwnd);
					SetTextColor(hdc, RGB(255,0,0));
					SetBkMode(hdc, TRANSPARENT);
					TextOut(hdc, 76, 25, "This is Red", strlen("This is Red"));
					ReleaseDC(hwnd, hdc);
				}break;
			case MENU_COLOR_WHITE:
				{
					hdc = GetDC(hwnd);
					SetTextColor(hdc, RGB(255,255,255));
					SetBkMode(hdc, TRANSPARENT);
					TextOut(hdc, 76, 36, "This is White", strlen("This is White"));
					ReleaseDC(hwnd, hdc);
				}break;
			case MENU_COLOR_BLUE:
				{
					hdc = GetDC(hwnd);
					SetTextColor(hdc, RGB(0,0,255));
					SetBkMode(hdc, TRANSPARENT);
					TextOut(hdc, 76, 47, "This is Blue", strlen("This is Blue"));
					ReleaseDC(hwnd, hdc);
				}break;
			case MENU_COLOR_YELLOW:
				{
					hdc = GetDC(hwnd);
					SetTextColor(hdc, RGB(255,255,0));
					SetBkMode(hdc, TRANSPARENT);
					TextOut(hdc, 76, 58, "This is Yellow", strlen("This is Yellow"));
					ReleaseDC(hwnd, hdc);
				}break;
			case MENU_COLOR_GREEN:
				{
					hdc = GetDC(hwnd);
					SetTextColor(hdc, RGB(0,255,0));
					SetBkMode(hdc, TRANSPARENT);
					TextOut(hdc, 76, 69, "This is Green", strlen("This is Green"));
					ReleaseDC(hwnd, hdc);
				}break;
			case MENU_ABOUT:
				{
					hdc = GetDC(hwnd);
					MessageBox(hwnd, "Author: C.K. King\nDate Finished: 06/04/2012\n© 2012 Christopher King", 
						"KING_P03", MB_OK);
					ReleaseDC(hwnd, hdc);
				}
			default:break;
			}
			return(0);
		}break;
	case WM_LBUTTONDOWN:
		{
			hdc = GetDC(hwnd);
			//SetTextColor(hdc, RGB(0,0,0));
			//SetBkMode(hdc, TRANSPARENT);
			//sprintf(buffer, "Left Button Down at (%d, %d)",
			//	mouse_x_down, mouse_y_down);
			//TextOut(hdc, 50, 150, buffer, strlen(buffer));

			mouse_x_down = LOWORD(lparam);
			mouse_y_down = HIWORD(lparam);

			SetTextColor(hdc, RGB(255,255,255));
			SetBkMode(hdc, TRANSPARENT);
			sprintf(buffer, "Left Button Down at (%d, %d)",
				mouse_x_down, mouse_y_down);
			TextOut(hdc, 50, 150, buffer, strlen(buffer));

			ReleaseDC(hwnd,hdc);
			return(0);
		}break;
	case WM_LBUTTONUP:
		{
			hdc = GetDC(hwnd);
			SetTextColor(hdc, RGB(0,0,0));
			SetBkMode(hdc, TRANSPARENT);
			sprintf(buffer, "Left Button Up at (%d, %d)",
				mouse_x_up, mouse_y_up);
			TextOut(hdc, 50, 161, buffer, strlen(buffer));

			mouse_x_up = LOWORD(lparam);
			mouse_y_up = HIWORD(lparam);

			SetTextColor(hdc, RGB(255,255,255));
			SetBkMode(hdc, TRANSPARENT);
			sprintf(buffer, "Left Button Up at (%d, %d)",
				mouse_x_up, mouse_y_up);
			TextOut(hdc, 50, 161, buffer, strlen(buffer));

			ReleaseDC(hwnd,hdc);
			return(0);
		}break;
	case WM_SIZE:
		{

			int width = LOWORD(lparam);
			int height = HIWORD(lparam);

			hdc = GetDC(hwnd);

			SetTextColor(hdc, RGB(255,255,255));

			SetBkColor(hdc, RGB(0,0,0));

			SetBkMode(hdc, OPAQUE);

			sprintf(buffer,
				"The window is %d units wide by %d units tall", width, height);
			TextOut(hdc, 50,200, buffer, strlen(buffer));

			ReleaseDC(hwnd, hdc);
		} break;

	case WM_MOVE:
		{

			int xpos = LOWORD(lparam);
			int ypos = HIWORD(lparam);

			hdc = GetDC(hwnd);

			SetTextColor(hdc, RGB(255,255,255));

			SetBkColor(hdc, RGB(0,0,0));

			SetBkMode(hdc, OPAQUE);

			sprintf(buffer,
				"The window is at Position = (%d,%d) on the screen", xpos, ypos);
			TextOut(hdc, 50, 180, buffer, strlen(buffer));

			ReleaseDC(hwnd, hdc);
		} break;
	case WM_CHAR:
		{

			char cExit = wparam;
			hdc = GetDC(hwnd);
			switch(cExit)
			{
			case 'e':
			case 'E':
				{
					bE = true;
					break;
				}
			case 'x':
			case 'X':
				{
					bX = true;
					break;
				}
			case 'i':
			case 'I':
				{
					bI = true;
					break;
				}
			case 't':
			case 'T':
				{
					bT = true;
					break;
				}
			}

			if (bE && bX && bI && bT)
				PostQuitMessage(0);

			hdc = GetDC(hwnd);

			ReleaseDC(hwnd, hdc);
		} break;

	case WM_PAINT:
		{
			hdc = GetDC(hwnd);
			ReleaseDC(hwnd, hdc);

			GetClientRect(hwnd, &rect);

			ValidateRect(hwnd, &rect);

			return (0);
		}break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);

			PlaySound("ID_WAVE1" , hinstance_app, SND_ASYNC | SND_RESOURCE);
			Sleep(1000);
			PlaySound(NULL, hinstance_app, SND_PURGE);

			return(0);
		}break;
	default:
		{

			break;
		}
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
	hinstance_app = hinstance;
	winclass.cbSize = sizeof(WNDCLASSEX); //size of structure
	winclass.style = CS_HREDRAW | CS_VREDRAW| CS_OWNDC | CS_DBLCLKS;
	winclass.lpfnWndProc = WinProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;

	HWND hlistbox;

	winclass.hIcon = LoadIcon(hinstance, "IDI_ICON1");
	winclass.hCursor = LoadCursor(hinstance, "IDC_CURSOR1");
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = "MainMenu";
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(hinstance, "IDI_ICON1");
	PlaySound("ID_WAVE2" , hinstance_app, SND_ASYNC | SND_RESOURCE);
	Sleep(1000);
	PlaySound(NULL, hinstance_app, SND_PURGE);

	PlaySound("ID_WAVE3" , hinstance_app, SND_ASYNC | SND_RESOURCE | SND_LOOP);

	//register the class
	if(!RegisterClassEx(&winclass))
		return (0);


	if(!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"KING_P03",
		WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX,
		0,0,
		500,500,
		NULL,
		NULL,
		hinstance,
		NULL))) 
		return (0);

	    hlistbox = CreateWindowEx(WS_EX_CLIENTEDGE, 
			"LISTBOX",
			NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
			100, 100,
			300, 200,
			hwnd,
			NULL,
			hinstance,
			NULL);

		    // Adding a TextBox.
  //  hTextBox = CreateWindowEXW(WS_EX_CLIENTEDGE,
		//L"EDIT",
		//NULL, WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL,
		//62, 7,
		//245, 21,
		//hWnd,
		//NULL,
		//hInstance,
		//NULL);


	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return(msg.wParam);
}


