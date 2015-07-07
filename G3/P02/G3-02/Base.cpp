/*Function definitions/supporting code, template classes, init/shutdown/WinProc(possibly) and main loop
go in here*/
#include "base.h"
#include <string>
using namespace std;

/////////////////////Global Handles for the Window and Edit/List Boxes/////////////////////////////////
HWND g_hwnd, g_hListBoxLoadXFiles, 
	g_hEditBoxSave1Init, g_hEditBoxSave2Init, g_hEditBoxSave3Init, g_hEditBoxSave4Init, g_hEditBoxSave5Init,
	g_hEditBoxSave6Init, g_hEditBoxSave7Init, g_hEditBoxSave8Init, g_hEditBoxSave9Init, g_hEditBoxSave10Init,

	g_hEditBoxSave1Date, g_hEditBoxSave2Date, g_hEditBoxSave3Date, g_hEditBoxSave4Date, g_hEditBoxSave5Date,
	g_hEditBoxSave6Date, g_hEditBoxSave7Date, g_hEditBoxSave8Date, g_hEditBoxSave9Date, g_hEditBoxSave10Date,

	g_hEditBoxSave1Score, g_hEditBoxSave2Score, g_hEditBoxSave3Score, g_hEditBoxSave4Score, g_hEditBoxSave5Score,
	g_hEditBoxSave6Score, g_hEditBoxSave7Score, g_hEditBoxSave8Score, g_hEditBoxSave9Score, g_hEditBoxSave10Score;



bool basewin::BuildWindow(HINSTANCE hInstance, int iXPos, int iYPos, int iHeight, int iWidth)
{
	//Windows class Variable and handles to the window and controls
	WNDCLASSEX wc;
	HWND hwnd = NULL, hListBoxLoadXFiles = NULL, 
		hEditBoxSave1Init = NULL, hEditBoxSave2Init = NULL, hEditBoxSave3Init = NULL, 
		hEditBoxSave4Init = NULL, hEditBoxSave5Init = NULL,
		hEditBoxSave6Init = NULL, hEditBoxSave7Init = NULL, hEditBoxSave8Init = NULL,
		hEditBoxSave9Init = NULL, hEditBoxSave10Init = NULL,

		hEditBoxSave1Date = NULL, hEditBoxSave2Date = NULL, hEditBoxSave3Date = NULL,
		hEditBoxSave4Date = NULL, hEditBoxSave5Date = NULL,
		hEditBoxSave6Date = NULL, hEditBoxSave7Date = NULL, hEditBoxSave8Date = NULL,
		hEditBoxSave9Date = NULL, hEditBoxSave10Date = NULL,

		hEditBoxSave1Score = NULL, hEditBoxSave2Score = NULL, hEditBoxSave3Score = NULL,
		hEditBoxSave4Score = NULL, hEditBoxSave5Score = NULL,
		hEditBoxSave6Score = NULL, hEditBoxSave7Score = NULL, hEditBoxSave8Score = NULL,
		hEditBoxSave9Score = NULL, hEditBoxSave10Score = NULL;

	//define the windows class and params	
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)basewin::WinProc;
	wc.lpszClassName = "WC_Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

	//Register the Windows Class
	if(!::RegisterClassEx(&wc))
	{
		::MessageBox(hwnd, "Failed to register class", "ERROR", MB_OK);
		return (0);
	}

	//Create the main Window
	if(!(hwnd = ::CreateWindowEx(NULL, "WC_Main", "CK's XFILES FINALLY WORK", WS_OVERLAPPEDWINDOW | WS_VISIBLE, iXPos,
		iYPos, iWidth, iHeight, NULL, NULL, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create window", "Build Window", MB_OK);
		return (0);
	}

	/********************************************************************************************
	List box to display the loaded data
	********************************************************************************************/
	if(!(hListBoxLoadXFiles = ::CreateWindowEx(NULL, "LISTBOX", NULL, 
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY, 750, 50, 300, 482,
		hwnd, (HMENU)BOX_ListBoxLoadXFiles, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create Message List Box", "Build Window", MB_OK);
		return (0);
	}

	/********************************************************************************************
	Edit boxes to get  Initials
	********************************************************************************************/

	if(!(hEditBoxSave1Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 50, 50, 25,
		hwnd, (HMENU)BOX_Save1Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save1Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave2Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 100, 50, 25,
		hwnd, (HMENU)BOX_Save2Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save2Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave3Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 150, 50, 25,
		hwnd, (HMENU)BOX_Save3Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save3Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave4Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 200, 50, 25,
		hwnd, (HMENU)BOX_Save4Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save4Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave5Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 250, 50, 25,
		hwnd, (HMENU)BOX_Save5Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save5Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave6Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 300, 50, 25,
		hwnd, (HMENU)BOX_Save6Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save6Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave7Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 350, 50, 25,
		hwnd, (HMENU)BOX_Save7Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save7Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave8Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 400, 50, 25,
		hwnd, (HMENU)BOX_Save8Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save8Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave9Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 450, 50, 25,
		hwnd, (HMENU)BOX_Save9Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save9Init", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave10Init = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 75, 500, 50, 25,
		hwnd, (HMENU)BOX_Save10Init, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save10Init", "Build Window", MB_OK);
		return (0);
	}


	/********************************************************************************************
	Edit boxes to get  Date
	********************************************************************************************/

	if(!(hEditBoxSave1Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 50, 215, 25,
		hwnd, (HMENU)BOX_Save1Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save1Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave2Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 100, 215, 25,
		hwnd, (HMENU)BOX_Save2Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save2Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave3Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 150, 215, 25,
		hwnd, (HMENU)BOX_Save3Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save3Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave4Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 200, 215, 25,
		hwnd, (HMENU)BOX_Save4Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save4Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave5Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 250, 215, 25,
		hwnd, (HMENU)BOX_Save5Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save5Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave6Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 300, 215, 25,
		hwnd, (HMENU)BOX_Save6Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save6Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave7Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 350, 215, 25,
		hwnd, (HMENU)BOX_Save7Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save7Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave8Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 400, 215, 25,
		hwnd, (HMENU)BOX_Save8Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save8Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave9Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 450, 215, 25,
		hwnd, (HMENU)BOX_Save9Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save9Date", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave10Date = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 175, 500, 215, 25,
		hwnd, (HMENU)BOX_Save10Date, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save10Date", "Build Window", MB_OK);
		return (0);
	}


	/********************************************************************************************
	Edit boxes to get  Score
	********************************************************************************************/

	if(!(hEditBoxSave1Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 50, 150, 25,
		hwnd, (HMENU)BOX_Save1Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save1Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave2Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 100, 150, 25,
		hwnd, (HMENU)BOX_Save2Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save2Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave3Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 150, 150, 25,
		hwnd, (HMENU)BOX_Save3Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save3Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave4Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 200, 150, 25,
		hwnd, (HMENU)BOX_Save4Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save4Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave5Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 250, 150, 25,
		hwnd, (HMENU)BOX_Save5Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save5Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave6Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 300, 150, 25,
		hwnd, (HMENU)BOX_Save6Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save6Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave7Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 350, 150, 25,
		hwnd, (HMENU)BOX_Save7Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save7Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave8Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 400, 150, 25,
		hwnd, (HMENU)BOX_Save8Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save8Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave9Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 450, 150, 25,
		hwnd, (HMENU)BOX_Save9Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save9Score", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSave10Score = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 450, 500, 150, 25,
		hwnd, (HMENU)BOX_Save10Score, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Save10Score", "Build Window", MB_OK);
		return (0);
	}

	CreateWindowEx(NULL, "button", "Save Data", WS_CHILD | WS_VISIBLE | BS_CENTER, 75, 550, 525, 25, 
		hwnd, (HMENU)BUT_Save1, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player2", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 100, 100, 25, 
	//	hwnd, (HMENU)BUT_Save2, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player3", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 150, 100, 25, 
	//	hwnd, (HMENU)BUT_Save3, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player4", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 200, 100, 25, 
	//	hwnd, (HMENU)BUT_Save4, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player5", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 250, 100, 25, 
	//	hwnd, (HMENU)BUT_Save5, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player6", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 300, 100, 25, 
	//	hwnd, (HMENU)BUT_Save6, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player7", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 350, 100, 25, 
	//	hwnd, (HMENU)BUT_Save7, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player8", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 400, 100, 25, 
	//	hwnd, (HMENU)BUT_Save8, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player9", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 450, 100, 25, 
	//	hwnd, (HMENU)BUT_Save9, hInstance, NULL);

	//CreateWindowEx(NULL, "button", "Save Player10", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 500, 100, 25, 
	//	hwnd, (HMENU)BUT_Save10, hInstance, NULL);

	CreateWindowEx(NULL, "button", "Load Data", WS_CHILD | WS_VISIBLE | BS_CENTER, 750, 550, 300, 25, 
		hwnd, (HMENU)BUT_LoadXFiles, hInstance, NULL);

	//Store the handles in global versions for use elsewhere
	g_hwnd = hwnd;
	g_hListBoxLoadXFiles = hListBoxLoadXFiles;
	g_hEditBoxSave1Date = hEditBoxSave1Date;
	g_hEditBoxSave1Init = hEditBoxSave1Init;
	g_hEditBoxSave1Score = hEditBoxSave1Score;
		
	g_hEditBoxSave2Date = hEditBoxSave2Date;
	g_hEditBoxSave2Init = hEditBoxSave2Init;
	g_hEditBoxSave2Score = hEditBoxSave2Score;
		
	g_hEditBoxSave3Date = hEditBoxSave3Date;
	g_hEditBoxSave3Init = hEditBoxSave3Init;
	g_hEditBoxSave3Score = hEditBoxSave3Score;
		
	g_hEditBoxSave4Date = hEditBoxSave4Date;
	g_hEditBoxSave4Init = hEditBoxSave4Init;
	g_hEditBoxSave4Score = hEditBoxSave4Score;
		
	g_hEditBoxSave5Date = hEditBoxSave5Date;
	g_hEditBoxSave5Init = hEditBoxSave5Init;
	g_hEditBoxSave5Score = hEditBoxSave5Score;
		
	g_hEditBoxSave6Date = hEditBoxSave6Date;
	g_hEditBoxSave6Init = hEditBoxSave6Init;
	g_hEditBoxSave6Score = hEditBoxSave6Score;
		
	g_hEditBoxSave7Date = hEditBoxSave7Date;
	g_hEditBoxSave7Init = hEditBoxSave7Init;
	g_hEditBoxSave7Score = hEditBoxSave7Score;
		
	g_hEditBoxSave8Date = hEditBoxSave8Date;
	g_hEditBoxSave8Init = hEditBoxSave8Init;
	g_hEditBoxSave8Score = hEditBoxSave8Score;
	
	g_hEditBoxSave9Date = hEditBoxSave9Date;
	g_hEditBoxSave9Init = hEditBoxSave9Init;
	g_hEditBoxSave9Score = hEditBoxSave9Score;

	g_hEditBoxSave10Date = hEditBoxSave10Date;
	g_hEditBoxSave10Init = hEditBoxSave10Init;
	g_hEditBoxSave10Score = hEditBoxSave10Score;

	LoadXFile();

	char buffer[80];
	SetWindowText(g_hEditBoxSave1Init, scoreDataReturn[0].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[0].highScore);
	SetWindowText(g_hEditBoxSave1Score, buffer);
	SetWindowText(g_hEditBoxSave1Date, scoreDataReturn[0].dateAccomplished);

	SetWindowText(g_hEditBoxSave2Init, scoreDataReturn[1].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[1].highScore);
	SetWindowText(g_hEditBoxSave2Score, buffer);
	SetWindowText(g_hEditBoxSave2Date, scoreDataReturn[1].dateAccomplished);

	SetWindowText(g_hEditBoxSave3Init, scoreDataReturn[2].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[2].highScore);
	SetWindowText(g_hEditBoxSave3Score, buffer);
	SetWindowText(g_hEditBoxSave3Date, scoreDataReturn[2].dateAccomplished);

	SetWindowText(g_hEditBoxSave4Init, scoreDataReturn[3].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[3].highScore);
	SetWindowText(g_hEditBoxSave4Score, buffer);
	SetWindowText(g_hEditBoxSave4Date, scoreDataReturn[3].dateAccomplished);

	SetWindowText(g_hEditBoxSave5Init, scoreDataReturn[4].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[4].highScore);
	SetWindowText(g_hEditBoxSave5Score, buffer);
	SetWindowText(g_hEditBoxSave5Date, scoreDataReturn[4].dateAccomplished);

	SetWindowText(g_hEditBoxSave6Init, scoreDataReturn[5].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[5].highScore);
	SetWindowText(g_hEditBoxSave6Score, buffer);
	SetWindowText(g_hEditBoxSave6Date, scoreDataReturn[5].dateAccomplished);

	SetWindowText(g_hEditBoxSave7Init, scoreDataReturn[6].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[6].highScore);
	SetWindowText(g_hEditBoxSave7Score, buffer);
	SetWindowText(g_hEditBoxSave7Date, scoreDataReturn[6].dateAccomplished);

	SetWindowText(g_hEditBoxSave8Init, scoreDataReturn[7].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[7].highScore);
	SetWindowText(g_hEditBoxSave8Score, buffer);
	SetWindowText(g_hEditBoxSave8Date, scoreDataReturn[7].dateAccomplished);

	SetWindowText(g_hEditBoxSave9Init, scoreDataReturn[8].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[8].highScore);
	SetWindowText(g_hEditBoxSave9Score, buffer);
	SetWindowText(g_hEditBoxSave9Date, scoreDataReturn[8].dateAccomplished);

	SetWindowText(g_hEditBoxSave10Init, scoreDataReturn[9].userInitial);
	sprintf(buffer, "%i", scoreDataReturn[9].highScore);
	SetWindowText(g_hEditBoxSave10Score, buffer);
	SetWindowText(g_hEditBoxSave10Date, scoreDataReturn[9].dateAccomplished);

	return true;

}
extern int b;
/************************************************************************************************
Function definition for WinProc, handles messages generated by the program / windows
************************************************************************************************/
LRESULT CALLBACK basewin::WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//local variables used in WinProc
	PAINTSTRUCT ps;
	HDC hdc;

	switch(msg)
	{
	case WM_CREATE:
		{
			return(0);
		}break;

	case WM_PAINT:
		{
			//Create the labels for the different sections of the window

			HPEN blackpen = NULL;
			blackpen= ::CreatePen(PS_SOLID, 1, RGB(255,255,255));


			//Variables containing the text for labels
			char chResultWindowLabel[20] = "Loaded Data";
			char chSaveData[20] = "Save Data";
			char chInit[20] = "Initials";
			char chDate[20] = "Date MM/DD/YYYY";
			char chScore[20] = "Score";




			//Draw the labels
			hdc = ::BeginPaint(hwnd, &ps);
			hdc = ::GetDC(hwnd);

			::SelectObject(hdc, blackpen);
			::TextOut(hdc, 867, 25, chResultWindowLabel, (int)strlen(chResultWindowLabel));
			//::TextOut(hdc, 50, 25, chSaveData, (int)strlen(chSaveData));
			::TextOut(hdc, 78, 25, chInit, (int)strlen(chInit));
			::TextOut(hdc, 225, 25, chDate, (int)strlen(chDate));
			::TextOut(hdc, 512, 25, chScore, (int)strlen(chScore));




			::ReleaseDC(hwnd, hdc);
			::EndPaint(hwnd, &ps);
			return(0);
		}break;

	case WM_COMMAND:
		{
			char chTempInit[4], chTempDate[11], chTempScore[10];
			int dScore;
			/*****************************************************************
			Button 
			*****************************************************************/
			switch(LOWORD(wparam))
			{

			case BUT_LoadXFiles:
				{
					char Buffer[80];
					LoadXFile();
					basewin::vShowText(g_hListBoxLoadXFiles, "X Files Loaded");
					sprintf(Buffer, "");
					basewin::vShowText(g_hListBoxLoadXFiles, Buffer);
					sprintf(Buffer, "Initials      Score         Date");
					basewin::vShowText(g_hListBoxLoadXFiles, Buffer);
					sprintf(Buffer, "---------------------------------------------------");
					basewin::vShowText(g_hListBoxLoadXFiles, Buffer);
					sprintf(Buffer, "");
					basewin::vShowText(g_hListBoxLoadXFiles, Buffer);
					for(int i = 0; i < 10; i++)
					{
						sprintf(Buffer, "%s          %i             %s", scoreDataReturn[i].userInitial, scoreDataReturn[i].highScore, scoreDataReturn[i].dateAccomplished);
						basewin::vShowText(g_hListBoxLoadXFiles, Buffer);
						sprintf(Buffer, "");
						basewin::vShowText(g_hListBoxLoadXFiles, Buffer);
					}

					sprintf(Buffer, "");
					basewin::vShowText(g_hListBoxLoadXFiles, Buffer);
				}break;

			case BUT_Save1:
				{
					GetDlgItemText(g_hwnd, BOX_Save1Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save1Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save1Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 1);
					/*saveXFile("CLK", 150, "03/19/13", 1);*/
				}
			case BUT_Save2:
				{
					GetDlgItemText(g_hwnd, BOX_Save2Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save2Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save2Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 2);
				}
			case BUT_Save3:
				{
					GetDlgItemText(g_hwnd, BOX_Save3Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save3Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save3Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 3);
				}
			case BUT_Save4:
				{
					GetDlgItemText(g_hwnd, BOX_Save4Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save4Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save4Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 4);
				}
			case BUT_Save5:
				{
					GetDlgItemText(g_hwnd, BOX_Save5Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save5Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save5Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 5);
				}
			case BUT_Save6:
				{
					GetDlgItemText(g_hwnd, BOX_Save6Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save6Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save6Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 6);
				}
			case BUT_Save7:
				{
					GetDlgItemText(g_hwnd, BOX_Save7Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save7Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save7Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 7);
				}
			case BUT_Save8:
				{
					GetDlgItemText(g_hwnd, BOX_Save8Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save8Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save8Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 8);
				}
			case BUT_Save9:
				{
					GetDlgItemText(g_hwnd, BOX_Save9Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save9Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save9Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 9);
				}
			case BUT_Save10:
				{
					GetDlgItemText(g_hwnd, BOX_Save10Date, chTempDate, sizeof(chTempDate));
					GetDlgItemText(g_hwnd, BOX_Save10Init, chTempInit, sizeof(chTempInit));
					GetDlgItemText(g_hwnd, BOX_Save10Score, chTempScore, sizeof(chTempScore));
					dScore = strtod(chTempScore, NULL);
					saveXFile(chTempInit, dScore, chTempDate, 10);
				}b = 0;break;


			default:break;
			}				
		}break;

		//Close window
	case WM_DESTROY:
		{
			::PostQuitMessage(0);
			return (0);
		}break;

	default:break;
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

//Main loop, executed until WM_QUIT is generated
int basewin::EnterMainLoop()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	while(true)
	{
		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if(KEYDOWN(VK_ESCAPE))
		{
			::SendMessage(g_hwnd, WM_DESTROY, 0, 0);
		}
	}

	return (int)msg.wParam;
}

//Send text to a control such as a listbox
//Requires the control handle and the text to be displayed (one line at a time)
void basewin::vShowText(HWND hChildHandle, char *chText)
{
	int iLine;
	::SendMessage(hChildHandle, LB_ADDSTRING, 0, (LPARAM)chText);

	iLine = (int)::SendMessage(hChildHandle, LB_GETCOUNT, 0, 0);
	::SendMessage(hChildHandle, LB_SETCURSEL, iLine - 1, 0);
	::SendMessage(hChildHandle, LB_SETCURSEL, -1, 0);
}


