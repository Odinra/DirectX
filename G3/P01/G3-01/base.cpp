/*Function definitions/supporting code, template classes, init/shutdown/WinProc(possibly) and main loop
go in here*/
#include "base.h"
#include <string>
using namespace std;

/////////////////////Global Handles for the Window and Edit/List Boxes/////////////////////////////////
HWND g_hwnd, g_hListBoxResult, g_hEditBoxHexDec, 

	g_hEditBoxMat1R1C1, g_hEditBoxMat1R1C2, g_hEditBoxMat1R1C3, g_hEditBoxMat1R1C4, 
	g_hEditBoxMat1R2C1, g_hEditBoxMat1R2C2, g_hEditBoxMat1R2C3, g_hEditBoxMat1R2C4,
	g_hEditBoxMat1R3C1, g_hEditBoxMat1R3C2, g_hEditBoxMat1R3C3, g_hEditBoxMat1R3C4,
	g_hEditBoxMat1R4C1, g_hEditBoxMat1R4C2, g_hEditBoxMat1R4C3, g_hEditBoxMat1R4C4,
	g_hEditBoxMat2R1C1, g_hEditBoxMat2R1C2, g_hEditBoxMat2R1C3, g_hEditBoxMat2R1C4,
	g_hEditBoxMat2R2C1, g_hEditBoxMat2R2C2, g_hEditBoxMat2R2C3, g_hEditBoxMat2R2C4,
	g_hEditBoxMat2R3C1, g_hEditBoxMat2R3C2, g_hEditBoxMat2R3C3, g_hEditBoxMat2R3C4,
	g_hEditBoxMat2R4C1, g_hEditBoxMat2R4C2, g_hEditBoxMat2R4C3, g_hEditBoxMat2R4C4;

/**********************************************************************************************************
			Function prototypes to retrieve the info from the Matrix 1 & 2 Edit Boxes and convert the 
			information from character array to a double data type for use
**********************************************************************************************************/


void GetAndConvert3x3Matrices();
void GetAndConvert2x2Matrices();
void GetAndConvert4x4Matrices();

/**********************************************************************************************************
			Function prototypes to display the results of the calculations for
			the Matrix math
**********************************************************************************************************/


void Display3x3Result();
void Display2x2Result();
void Display4x4Result();

bool basewin::BuildWindow(HINSTANCE hInstance, int iXPos, int iYPos, int iHeight, int iWidth)
{
	//Windows class Variable and handles to the window and controls
	WNDCLASSEX wc;
	HWND hwnd = NULL, hListBoxResult = NULL, hEditBoxHexDec = NULL,  hEditBoxDegRad = NULL, 
		hEditBoxSide1 = NULL, hEditBoxSide2 = NULL, hEditBoxHypotenuse = NULL,
		
		 hEditBoxMat1R1C1 = NULL, hEditBoxMat1R1C2 = NULL, hEditBoxMat1R1C3 = NULL, hEditBoxMat1R1C4 = NULL,
		 hEditBoxMat1R2C1 = NULL, hEditBoxMat1R2C2 = NULL, hEditBoxMat1R2C3 = NULL, hEditBoxMat1R2C4 = NULL,
		 hEditBoxMat1R3C1 = NULL, hEditBoxMat1R3C2 = NULL, hEditBoxMat1R3C3 = NULL, hEditBoxMat1R3C4 = NULL,
		 hEditBoxMat1R4C1 = NULL, hEditBoxMat1R4C2 = NULL, hEditBoxMat1R4C3 = NULL, hEditBoxMat1R4C4 = NULL,
		
		 hEditBoxMat2R1C1 = NULL, hEditBoxMat2R1C2 = NULL, hEditBoxMat2R1C3 = NULL, hEditBoxMat2R1C4 = NULL,
		 hEditBoxMat2R2C1 = NULL, hEditBoxMat2R2C2 = NULL, hEditBoxMat2R2C3 = NULL, hEditBoxMat2R2C4 = NULL,
		 hEditBoxMat2R3C1 = NULL, hEditBoxMat2R3C2 = NULL, hEditBoxMat2R3C3 = NULL, hEditBoxMat2R3C4 = NULL,
		 hEditBoxMat2R4C1 = NULL, hEditBoxMat2R4C2 = NULL, hEditBoxMat2R4C3 = NULL, hEditBoxMat2R4C4 = NULL;

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
	if(!(hwnd = ::CreateWindowEx(NULL, "WC_Main", "CK's FPU MATHAMATICAL THINGS", WS_OVERLAPPEDWINDOW | WS_VISIBLE, iXPos,
		iYPos, iWidth, iHeight, NULL, NULL, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create window", "Build Window", MB_OK);
		return (0);
	}
	
	/********************************************************************************************
			List box to display results of the calculations
	********************************************************************************************/
	if(!(hListBoxResult = ::CreateWindowEx(NULL, "LISTBOX", NULL, 
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY, 10, 255, 425, 120,
		hwnd, (HMENU)BOX_ListBoxResult, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create Message List Box", "Build Window", MB_OK);
		return (0);
	}
	
	/********************************************************************************************
		Edit boxes to get  hex / decimal
	********************************************************************************************/
	
	if(!(hEditBoxHexDec = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 495, 215, 125, 25,
		hwnd, (HMENU)BOX_EditBoxHexDec, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box HexDec", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxDegRad = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 695, 215, 125, 25,
		hwnd, (HMENU)BOX_EditBoxDegRad, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box DegRad", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSide1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 895, 215, 125, 25,
		hwnd, (HMENU)BOX_EditBoxSide1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Side1", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxSide2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 895, 285, 125, 25,
		hwnd, (HMENU)BOX_EditBoxSide2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Side2", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxHypotenuse = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 895, 355, 125, 25,
		hwnd, (HMENU)BOX_EditBoxHypotenuse, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Hypotenuse", "Build Window", MB_OK);
		return (0);
	}

	/*********************************************************************************************
				Edit Boxes to get input for 2 matrices
	*********************************************************************************************/
	/*********************************************

	//Edit Boxes for Matrix 1 Row 1-4 Columns 1-4

	*********************************************/
	if(!(hEditBoxMat1R1C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE, 10, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat1R1C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R1C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R1C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE, 60, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat1R1C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R1C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R1C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE, 110, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat1R1C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R1C3", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R1C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 160, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat1R1C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R1C4", "Build Window", MB_OK);
		return (0);
	}
	
	if(!(hEditBoxMat1R2C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 10, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat1R2C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R2C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R2C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 60, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat1R2C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R2C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R2C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 110, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat1R2C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R2C3", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxMat1R2C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 160, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat1R2C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R2C4", "Build Window", MB_OK);
		return (0);
	}
	
	if(!(hEditBoxMat1R3C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 10, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat1R3C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R3C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R3C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 60, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat1R3C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R3C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R3C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 110, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat1R3C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R3C3", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R3C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 160, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat1R3C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R3C4", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxMat1R4C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 10, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat1R4C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R4C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R4C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 60, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat1R4C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R4C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R4C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 110, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat1R4C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R4C3", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat1R4C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 160, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat1R4C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 1 R4C4", "Build Window", MB_OK);
		return (0);
	}

	/*********************************************

	//Edit Boxes for Matrix 2 Row 1-4 Columns 1-4

	*********************************************/
	if(!(hEditBoxMat2R1C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 240, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat2R1C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R1C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R1C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 290, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat2R1C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R1C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R1C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 340, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat2R1C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R1C3", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R1C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 390, 60, 45, 25,
		hwnd, (HMENU)BOX_Mat2R1C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R1C4", "Build Window", MB_OK);
		return (0);
	}
	
	if(!(hEditBoxMat2R2C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 240, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat2R2C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R2C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R2C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 290, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat2R2C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R2C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R2C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 340, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat2R2C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R2C3", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R2C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 390, 90, 45, 25,
		hwnd, (HMENU)BOX_Mat2R2C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R2C4", "Build Window", MB_OK);
		return (0);
	}
	
	if(!(hEditBoxMat2R3C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 240, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat2R3C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R3C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R3C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 290, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat2R3C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R3C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R3C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 340, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat2R3C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R3C3", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R3C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 390, 120, 45, 25,
		hwnd, (HMENU)BOX_Mat2R3C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R3C4", "Build Window", MB_OK);
		return (0);
	}

	if(!(hEditBoxMat2R4C1 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 240, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat2R4C1, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R4C1", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R4C2 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 290, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat2R4C2, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R4C2", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R4C3 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 340, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat2R4C3, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R4C3", "Build Window", MB_OK);
		return (0);
	}
	if(!(hEditBoxMat2R4C4 = ::CreateWindowEx(NULL, "EDIT", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 390, 150, 45, 25,
		hwnd, (HMENU)BOX_Mat2R4C4, hInstance, NULL)))
	{
		::MessageBox(hwnd, "Failed to create edit box Matrix 2 R4C4", "Build Window", MB_OK);
		return (0);
	}
	
	/*********************************************************************************************
				Buttons to convert from 
				hexidecimal to decimal, decimal to hexidecimal
	*********************************************************************************************/
								
	
								//Buttons for Decimal to Hex and Hex to Decimal
	CreateWindowEx(NULL, "button", "Decimal to Hexidecimal", WS_CHILD | WS_VISIBLE | BS_CENTER, 475, 255, 160, 25, 
		hwnd, (HMENU)BUT_DecToHex, hInstance, NULL);
	CreateWindowEx(NULL, "button", "Hexidecimal to Decimal", WS_CHILD | WS_VISIBLE | BS_CENTER, 475, 285, 160, 25, 
		hwnd, (HMENU)BUT_HexToDec, hInstance, NULL);

	CreateWindowEx(NULL, "button", "Degrees to Radians", WS_CHILD | WS_VISIBLE | BS_CENTER, 675, 255, 160, 25, 
		hwnd, (HMENU)BUT_DegToRad, hInstance, NULL);
	CreateWindowEx(NULL, "button", "Radians to Degrees", WS_CHILD | WS_VISIBLE | BS_CENTER, 675, 285, 160, 25, 
		hwnd, (HMENU)BUT_RadToDeg, hInstance, NULL);

	CreateWindowEx(NULL, "button", "Calculate Side", WS_CHILD | WS_VISIBLE | BS_CENTER, 675, 355, 160, 25, 
		hwnd, (HMENU)BUT_CalcTri, hInstance, NULL);
	
							
	//*****************************************************
	//Buttons for 2x2 Addition, Subtraction, Multiplication
	//*****************************************************
	CreateWindowEx(NULL, "button", "2x2 Addition", WS_CHILD | WS_VISIBLE | BS_CENTER, 475, 60, 160, 25, 
		hwnd, (HMENU)BUT_2x2Add, hInstance, NULL);

	CreateWindowEx(NULL, "button", "2x2 Subtraction", WS_CHILD | WS_VISIBLE | BS_CENTER, 475, 105, 160, 25, 
		hwnd, (HMENU)BUT_2x2Sub, hInstance, NULL);
	
	CreateWindowEx(NULL, "button", "2x2 Multiplication", WS_CHILD | WS_VISIBLE | BS_CENTER, 475, 150, 160, 25, 
		hwnd, (HMENU)BUT_2x2Mul, hInstance, NULL);

	//*****************************************************
	//Buttons for 3x3 Addition, Subtraction, Multiplication
	//*****************************************************
	CreateWindowEx(NULL, "button", "3x3 Addition", WS_CHILD | WS_VISIBLE | BS_CENTER, 675, 60, 160, 25, 
		hwnd, (HMENU)BUT_3x3Add, hInstance, NULL);

	CreateWindowEx(NULL, "button", "3x3 Subtraction", WS_CHILD | WS_VISIBLE | BS_CENTER, 675, 105, 160, 25, 
		hwnd, (HMENU)BUT_3x3Sub, hInstance, NULL);
	
	CreateWindowEx(NULL, "button", "3x3 Multiplication", WS_CHILD | WS_VISIBLE | BS_CENTER, 675, 150, 160, 25, 
		hwnd, (HMENU)BUT_3x3Mul, hInstance, NULL);

	//*****************************************************
	//Buttons for 4x4 Addition, Subtraction, Multiplication
	//*****************************************************
	CreateWindowEx(NULL, "button", "4x4 Addition", WS_CHILD | WS_VISIBLE | BS_CENTER, 875, 60, 160, 25, 
		hwnd, (HMENU)BUT_4x4Add, hInstance, NULL);

	CreateWindowEx(NULL, "button", "4x4 Subtraction", WS_CHILD | WS_VISIBLE | BS_CENTER, 875, 105, 160, 25, 
		hwnd, (HMENU)BUT_4x4Sub, hInstance, NULL);
	
	CreateWindowEx(NULL, "button", "4x4 Multiplication", WS_CHILD | WS_VISIBLE | BS_CENTER, 875, 150, 160, 25, 
		hwnd, (HMENU)BUT_4x4Mul, hInstance, NULL);
							 
	//Store the handles in global versions for use elsewhere
	g_hwnd = hwnd;
	g_hListBoxResult = hListBoxResult;
	
	g_hEditBoxHexDec = hEditBoxHexDec;

	g_hEditBoxMat1R1C1 = hEditBoxMat1R1C1;
	g_hEditBoxMat1R1C2 = hEditBoxMat1R1C2;
	g_hEditBoxMat1R1C3 = hEditBoxMat1R1C3;

	g_hEditBoxMat1R2C1 = hEditBoxMat1R2C1;
	g_hEditBoxMat1R2C2 = hEditBoxMat1R2C2;
	g_hEditBoxMat1R2C3 = hEditBoxMat1R2C3;
	
	g_hEditBoxMat1R3C1 = hEditBoxMat1R3C1;
	g_hEditBoxMat1R3C2 = hEditBoxMat1R3C2;
	g_hEditBoxMat1R3C3 = hEditBoxMat1R3C3;
	
	g_hEditBoxMat2R1C1 = hEditBoxMat2R1C1;
	g_hEditBoxMat2R1C2 = hEditBoxMat2R1C2;
	g_hEditBoxMat2R1C3 = hEditBoxMat2R1C3;
	
	g_hEditBoxMat2R2C1 = hEditBoxMat2R2C1;
	g_hEditBoxMat2R2C2 = hEditBoxMat2R2C2;
	g_hEditBoxMat2R2C3 = hEditBoxMat2R2C3;

	g_hEditBoxMat2R3C1 = hEditBoxMat2R3C1;
	g_hEditBoxMat2R3C2 = hEditBoxMat2R3C2;
	g_hEditBoxMat2R3C3 = hEditBoxMat2R3C3;

	return true;
}

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
				char chResultWindowLabel[8] = "Results";
				
				char chHexDecLabel[80] = "Hexidecimal / Decimal";
				char chDegRadLabel[80] = "Degree / Radians";
				char chSide1Label[80] = "Side 1";
				char chSide2Label[80] = "Side 2";
				char chHypotenuseLabel[80] = "Hypotenuse";
				char chMatrixOneLabel[11] = "Matrix One";
				char chMatrixTwoLabel[11] = "Matrix Two";
				
				
				//Draw the labels
				hdc = ::BeginPaint(hwnd, &ps);
					hdc = ::GetDC(hwnd);
										
					::SelectObject(hdc, blackpen);
					::TextOut(hdc, 200, 215, chResultWindowLabel, (int)strlen(chResultWindowLabel));
					
					::TextOut(hdc, 485, 195, chHexDecLabel, (int)strlen(chHexDecLabel));
					::TextOut(hdc, 705, 195, chDegRadLabel, (int)strlen(chDegRadLabel));
					::TextOut(hdc, 940, 195, chSide1Label, (int)strlen(chSide1Label));
					::TextOut(hdc, 940, 260, chSide2Label, (int)strlen(chSide2Label));
					::TextOut(hdc, 925, 325, chHypotenuseLabel, (int)strlen(chHypotenuseLabel));
					::TextOut(hdc, 80, 25, chMatrixOneLabel, (int)strlen(chMatrixOneLabel));
					::TextOut(hdc, 305, 25, chMatrixTwoLabel, (int)strlen(chMatrixTwoLabel));
				
			
					::ReleaseDC(hwnd, hdc);
				::EndPaint(hwnd, &ps);
				return(0);
			}break;

		case WM_COMMAND:
			{
				/*****************************************************************
							Button 
				*****************************************************************/
				switch(LOWORD(wparam))
				{
					
					//Pressed to Retrieve info for 3x3 Matrix Addition calculation
					
					
					case BUT_3x3Add:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert3x3Matrices();

							//Calculates 3x3 Addition and stores in dResult[][]
							matrix3x3Add(dMat1R1C1, dMat1R1C2, dMat1R1C3,
										 dMat1R2C1, dMat1R2C2, dMat1R2C3, 
										 dMat1R3C1, dMat1R3C2, dMat1R3C3, 
										 dMat2R1C1, dMat2R1C2, dMat2R1C3, 
										 dMat2R2C1, dMat2R2C2, dMat2R2C3,
										 dMat2R3C1, dMat2R3C2, dMat2R3C3);

							//Displays calculation result
							Display3x3Result();
						}break;

						//Pressed to Retrieve info for 3x3 Matrix Multiplication calculation
					case BUT_3x3Mul:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert3x3Matrices();

							//Calculates 3x3 Multiplication and stores in dResult[][]
							matrix3x3Mul(dMat1R1C1, dMat1R1C2, dMat1R1C3,
										 dMat1R2C1, dMat1R2C2, dMat1R2C3, 
										 dMat1R3C1, dMat1R3C2, dMat1R3C3, 
										 dMat2R1C1, dMat2R1C2, dMat2R1C3, 
										 dMat2R2C1, dMat2R2C2, dMat2R2C3,
										 dMat2R3C1, dMat2R3C2, dMat2R3C3);

							//Displays calculation result
							Display3x3Result();
						}break;

					case BUT_3x3Sub:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert3x3Matrices();

							//Calculates 3x3 Multiplication and stores in dResult[][]
							matrix3x3Sub(dMat1R1C1, dMat1R1C2, dMat1R1C3,
										 dMat1R2C1, dMat1R2C2, dMat1R2C3, 
										 dMat1R3C1, dMat1R3C2, dMat1R3C3, 
										 dMat2R1C1, dMat2R1C2, dMat2R1C3, 
										 dMat2R2C1, dMat2R2C2, dMat2R2C3,
										 dMat2R3C1, dMat2R3C2, dMat2R3C3);

							//Displays calculation result
							Display3x3Result();
						}break;

					
					case BUT_4x4Add:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert4x4Matrices();

							//Calculates 4x4 Addition and stores in dResult[][]
							matrix4x4Add(dMat1R1C1, dMat1R1C2, dMat1R1C3, dMat1R1C4,
										 dMat1R2C1, dMat1R2C2, dMat1R2C3, dMat1R2C4, 
										 dMat1R3C1, dMat1R3C2, dMat1R3C3, dMat1R3C4,
										 dMat1R4C1, dMat1R4C2, dMat1R4C3, dMat1R4C4, 
										 dMat2R1C1, dMat2R1C2, dMat2R1C3, dMat2R1C4, 
										 dMat2R2C1, dMat2R2C2, dMat2R2C3, dMat2R2C4,
										 dMat2R3C1, dMat2R3C2, dMat2R3C3, dMat2R3C4,
										 dMat2R4C1, dMat2R4C2, dMat2R4C3, dMat2R4C4);

							//Displays calculation result
							Display4x4Result();
						}break;

						//Pressed to Retrieve info for 3x3 Matrix Multiplication calculation
					case BUT_4x4Mul:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert4x4Matrices();

							//Calculates 4x4 Multiplication and stores in dResult[][]
							matrix4x4Mul(dMat1R1C1, dMat1R1C2, dMat1R1C3, dMat1R1C4,
										 dMat1R2C1, dMat1R2C2, dMat1R2C3, dMat1R2C4, 
										 dMat1R3C1, dMat1R3C2, dMat1R3C3, dMat1R3C4,
										 dMat1R4C1, dMat1R4C2, dMat1R4C3, dMat1R4C4, 
										 dMat2R1C1, dMat2R1C2, dMat2R1C3, dMat2R1C4, 
										 dMat2R2C1, dMat2R2C2, dMat2R2C3, dMat2R2C4,
										 dMat2R3C1, dMat2R3C2, dMat2R3C3, dMat2R3C4,
										 dMat2R4C1, dMat2R4C2, dMat2R4C3, dMat2R4C4);

							//Displays calculation result
							Display4x4Result();
						}break;

					case BUT_4x4Sub:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert4x4Matrices();

							//Calculates 4x4 Multiplication and stores in dResult[][]
							matrix4x4Sub(dMat1R1C1, dMat1R1C2, dMat1R1C3, dMat1R1C4,
										 dMat1R2C1, dMat1R2C2, dMat1R2C3, dMat1R2C4, 
										 dMat1R3C1, dMat1R3C2, dMat1R3C3, dMat1R3C4,
										 dMat1R4C1, dMat1R4C2, dMat1R4C3, dMat1R4C4, 
										 dMat2R1C1, dMat2R1C2, dMat2R1C3, dMat2R1C4, 
										 dMat2R2C1, dMat2R2C2, dMat2R2C3, dMat2R2C4,
										 dMat2R3C1, dMat2R3C2, dMat2R3C3, dMat2R3C4,
										 dMat2R4C1, dMat2R4C2, dMat2R4C3, dMat2R4C4);

							//Displays calculation result
							Display4x4Result();
						}break;


					case BUT_2x2Add:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert2x2Matrices();

							//Calculates 2x2 Addition and stores in dResult[][]
							matrix2x2Add(dMat1R1C1, dMat1R1C2,
										 dMat1R2C1, dMat1R2C2,
										 dMat2R1C1, dMat2R1C2, 
										 dMat2R2C1, dMat2R2C2);

							//Displays calculation result
							Display2x2Result();
						}break;

						//Pressed to Retrieve info for 3x3 Matrix Multiplication calculation
					case BUT_2x2Mul:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert2x2Matrices();

							//Calculates 2x2 Multiplication and stores in dResult[][]
							matrix2x2Mul(dMat1R1C1, dMat1R1C2,
										 dMat1R2C1, dMat1R2C2,  
										 dMat2R1C1, dMat2R1C2, 
										 dMat2R2C1, dMat2R2C2);

							//Displays calculation result
							Display2x2Result();
						}break;

					case BUT_2x2Sub:
						{
							//Function call to get info from dialog boxes and convert to double
							GetAndConvert2x2Matrices();

							//Calculates 2x2 Multiplication and stores in dResult[][]
							matrix2x2Sub(dMat1R1C1, dMat1R1C2,
										 dMat1R2C1, dMat1R2C2,
										 dMat2R1C1, dMat2R1C2, 
										 dMat2R2C1, dMat2R2C2);

							//Displays calculation result
							Display2x2Result();
						}break;
					
					

				
					//Pressed to retrieve info for converting a decimal to a hexadecimal value
					case BUT_DecToHex:
						{
							//Variable used to get/convert for use the variable from the screen
							char chTemp[80];
							int iDec = 0, i = 0, iHexConv = 16, iSubscript1, iSubscript2;

							//Variables used to store and display the information after calculations
							char chResult[50];
							char *chResult2 = chResult;
							char chDisplay[100];

							//variables used for temporary storage of values during conversion
							int iQuotient = 0.0, iRemainder = 0.0, iTemp = 0, iCounter = 0;
							char chTempResult[50];
							char chConvertNumToChar[50];

							//Retrieve information from the dialog boxes and convert to integer
							GetDlgItemText(g_hwnd, BOX_EditBoxHexDec, chTemp, sizeof(chTemp));
							iDec = atoi(chTemp);							

							//store the value to use for calculations
							iTemp = iDec;

							//Initialize variables to eliminate any junk in them
							//ADD HERE #1////////////////////////////
							for(int i = 0; i < 50; i = fpuAdd(1, i))
							{
								chTempResult[i] = NULL;
								chResult[i] = NULL;
							}

							
							//Loop to continue calculating until the division returns 0
							while(iTemp != 0)
							{
								//Call the fpuModulus and fpuDiv functions to perform the calculations, store the quotient
								//back in iTemp for the next pass
								//Add HERE #2 ////////////////////
								iRemainder = fpuModulus(iTemp, 16);
								iQuotient = fpuDiv(iTemp, 16);
								iTemp= iQuotient;

								//Checks the value of the remainder to see what it is and determine what value to store
								//0-9 is #, 10-15 is A-F
								if(iRemainder >= 0 && iRemainder <= 9)
								{
									//Convert the numerical value to its character equivalent
									_gcvt_s(chConvertNumToChar, sizeof(chConvertNumToChar), iRemainder, 1);
									chTempResult[iCounter] = chConvertNumToChar[0];
								}
								else if(iRemainder == 10)
								{
									chTempResult[iCounter] = 'A';
								}
								else if(iRemainder == 11)
								{
									chTempResult[iCounter] = 'B';
								}
								else if(iRemainder == 12)
								{
									chTempResult[iCounter] = 'C';
								}
								else if(iRemainder == 13)
								{
									chTempResult[iCounter] = 'D';
								}
								else if(iRemainder == 14)
								{
									chTempResult[iCounter] = 'E';
								}
								else if(iRemainder == 15)
								{
									chTempResult[iCounter] = 'F';
								}
								
								//Add #3 HERE//////////////
								iCounter = fpuAdd(iCounter, 1);

								iQuotient = 0;
								iRemainder = 0;
							}

							//Loop through to reverse the order of the values so that they are in the proper order for display							
							//#4 HERE ///////////////////
							for(int i = iCounter; i > 0; i = fpuSub(i,1))
							{
								iSubscript1 = fpuSub(i, 1);
								iSubscript2 = fpuSub(iCounter, i);
								chResult[iSubscript1] = chTempResult[iSubscript2];
							}




							chResult2 = chResult;

							//Format and display the results
							sprintf_s(chDisplay, "The Hexadecimal value is %s.", chResult2);
							basewin::vShowText(g_hListBoxResult, chDisplay);
							basewin::vShowText(g_hListBoxResult, "");

						}break;
					case BUT_HexToDec:
						{
								char chResult[80];
								int i,a[20];
								unsigned long int h=0,m=1, t=0;
								char s[20];
								GetDlgItemText(g_hwnd, BOX_EditBoxHexDec, s, sizeof(s));
								for(i=0;s[i]!=NULL;i = fpuAdd(i, 1))
									{
										switch(s[i])
										{
											case '0':
												a[i]=0;
											break;
											case '1':
												a[i]=1;
											break;
											case '2':
												a[i]=2;
											break;
											case '3':
												a[i]=3;
											break;
											case '4':
												a[i]=4;
											break;
											case '5':
												a[i]=5;
											break;
											case '6':
												a[i]=6;
											break;
											case '7':
												a[i]=7;
											break;
											case '8':
												a[i]=8;
											break;
											case '9':
												a[i]=9;
											break;
											case 'a':
											case 'A':
												a[i]=10;
											break;
											case 'b':
											case 'B':
												a[i]=11;
											break;
											case 'c':
											case 'C':
												a[i]=12;
											break;
											case 'd':
											case 'D':
												a[i]=13;
											break;
											case 'e':
											case 'E':
												a[i]=14;
											break;
											case 'f':
											case 'F':
												a[i]=15;
											break;
								
										}
									}
								i = fpuSub(i, 1);
								for(;i>=0;i = fpuSub(i, 1))
								{
									t=fpuMul(a[i], m);
									h= fpuAdd(h,t);
									m=fpuMul(m,16);
								}
								sprintf_s(chResult,"The Decimal value is %ld.",h);
								basewin::vShowText(g_hListBoxResult, chResult);
								basewin::vShowText(g_hListBoxResult, "");

						}break;
					case BUT_DegToRad:
						{
							double dDeg, dRad;
							char chTemp[80];

							GetDlgItemText(g_hwnd, BOX_EditBoxDegRad, chTemp, sizeof(chTemp));
							dDeg = atoi(chTemp);	

							dRad = fpuMul(dDeg, DEGTORAD);

							sprintf_s(chTemp, "The Radian value is %f.", dRad);
							basewin::vShowText(g_hListBoxResult, chTemp);
							basewin::vShowText(g_hListBoxResult, "");
						}break;

					case BUT_RadToDeg:
						{
							double dRad, dDeg;
							char chTemp[80];

							GetDlgItemText(g_hwnd, BOX_EditBoxDegRad, chTemp, sizeof(chTemp));
							dRad = atoi(chTemp);

							dDeg = fpuMul(dRad, RADTODEG);

							sprintf_s(chTemp, "The Degree value is %f.", dDeg);
							basewin::vShowText(g_hListBoxResult, chTemp);
							basewin::vShowText(g_hListBoxResult, "");
						}break;

					case BUT_CalcTri:
						{
							double dSide1, dSide2, dHyp;
							double temp1, temp2, temp3;
							char chTemp[80];

							GetDlgItemText(g_hwnd, BOX_EditBoxSide1, chTemp, sizeof(chTemp));
							dSide1 = atoi(chTemp);

							GetDlgItemText(g_hwnd, BOX_EditBoxSide2, chTemp, sizeof(chTemp));
							dSide2 = atoi(chTemp);

							GetDlgItemText(g_hwnd, BOX_EditBoxHypotenuse, chTemp, sizeof(chTemp));
							dHyp = atoi(chTemp);

							if (dHyp == 0)
							{
								temp1 = fpuAdd(fpuMul(dSide1, dSide1), fpuMul(dSide2, dSide2));
								temp2 = fpuSqRoot(temp1);
								sprintf_s(chTemp, "The Missing side is approx %f.", temp2);
								basewin::vShowText(g_hListBoxResult, chTemp);
								basewin::vShowText(g_hListBoxResult, "");
							}
							else if(dSide1 == 0)
							{
								temp1 = fpuSub(fpuMul(dHyp, dHyp), fpuMul(dSide2, dSide2));
								temp2 = fpuSqRoot(temp1);
								sprintf_s(chTemp, "The Missing side is approx %f.", temp2);
								basewin::vShowText(g_hListBoxResult, chTemp);
								basewin::vShowText(g_hListBoxResult, "");
							}
							else if(dSide2 == 0)
							{
								temp1 = fpuSub(fpuMul(dHyp, dHyp), fpuMul(dSide1, dSide1));
								temp2 = fpuSqRoot(temp1);	
								sprintf_s(chTemp, "The Missing side is approx %f.", temp2);
								basewin::vShowText(g_hListBoxResult, chTemp);
								basewin::vShowText(g_hListBoxResult, "");
							}
							else
							{
								sprintf_s(chTemp, "There needs to be a side missing.");
								basewin::vShowText(g_hListBoxResult, chTemp);
								basewin::vShowText(g_hListBoxResult, "");
							}

							
						}break;

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



/**********************************************************************************************************
			Function call to retrieve the info from the Matrix 1 & 2 Edit Boxes and convert the 
			information from character array to a double data type for use
**********************************************************************************************************/
void GetAndConvert3x3Matrices()
{
	//Temp variables used to retrieve data until converted to double
	char chTempMat1R1C1[80], chTempMat1R1C2[80], chTempMat1R1C3[80], 
		 chTempMat1R2C1[80], chTempMat1R2C2[80], chTempMat1R2C3[80],
		 chTempMat1R3C1[80], chTempMat1R3C2[80], chTempMat1R3C3[80],
		 chTempMat2R1C1[80], chTempMat2R1C2[80], chTempMat2R1C3[80], 
		 chTempMat2R2C1[80], chTempMat2R2C2[80], chTempMat2R2C3[80],
		 chTempMat2R3C1[80], chTempMat2R3C2[80], chTempMat2R3C3[80];

	//////////////////////////////Begin Matrix 1 Retrieval/////////////////////////////////////
		//Get Matrix 1 Row 1 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C1, chTempMat1R1C1, sizeof(chTempMat1R1C1));
			dMat1R1C1 = strtod(chTempMat1R1C1, NULL);
		//Get Matrix 1 Row 1 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C2, chTempMat1R1C2, sizeof(chTempMat1R1C2));
			dMat1R1C2 = strtod(chTempMat1R1C2, NULL);
		//Get Matrix 1 Row 1 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C3, chTempMat1R1C3, sizeof(chTempMat1R1C3));
			dMat1R1C3 = strtod(chTempMat1R1C3, NULL);

		//Get Matrix 1 Row 2 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C1, chTempMat1R2C1, sizeof(chTempMat1R2C1));
			dMat1R2C1 = strtod(chTempMat1R2C1, NULL);
		//Get Matrix 1 Row 2 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C2, chTempMat1R2C2, sizeof(chTempMat1R2C2));
			dMat1R2C2 = strtod(chTempMat1R2C2, NULL);
		//Get Matrix 1 Row 2 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C3, chTempMat1R2C3, sizeof(chTempMat1R2C3));
			dMat1R2C3 = strtod(chTempMat1R2C3, NULL);

		//Get Matrix 1 Row 3 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R3C1, chTempMat1R3C1, sizeof(chTempMat1R3C1));
			dMat1R3C1 = strtod(chTempMat1R3C1, NULL);
		//Get Matrix 1 Row 3 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R3C2, chTempMat1R3C2, sizeof(chTempMat1R3C2));
			dMat1R3C2 = strtod(chTempMat1R3C2, NULL);
		//Get Matrix 1 Row 3 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R3C3, chTempMat1R3C3, sizeof(chTempMat1R3C3));
			dMat1R3C3 = strtod(chTempMat1R3C3, NULL);
	//////////////////////////////End Matrix 1 Retrieval/////////////////////////////////////

	//////////////////////////////Begin Matrix 2 Retrieval/////////////////////////////////////
		//Get Matrix 2 Row 1 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C1, chTempMat2R1C1, sizeof(chTempMat2R1C1));
			dMat2R1C1 = strtod(chTempMat2R1C1, NULL);
		//Get Matrix 2 Row 1 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C2, chTempMat2R1C2, sizeof(chTempMat2R1C2));
			dMat2R1C2 = strtod(chTempMat2R1C2, NULL);
		//Get Matrix 2 Row 1 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C3, chTempMat2R1C3, sizeof(chTempMat2R1C3));
			dMat2R1C3 = strtod(chTempMat2R1C3, NULL);

		//Get Matrix 2 Row 2 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C1, chTempMat2R2C1, sizeof(chTempMat2R2C1));
			dMat2R2C1 = strtod(chTempMat2R2C1, NULL);
		//Get Matrix 2 Row 2 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C2, chTempMat2R2C2, sizeof(chTempMat2R2C2));
			dMat2R2C2 = strtod(chTempMat2R2C2, NULL);
		//Get Matrix 2 Row 2 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C3, chTempMat2R2C3, sizeof(chTempMat2R2C3));
			dMat2R2C3 = strtod(chTempMat2R2C3, NULL);

		//Get Matrix 2 Row 3 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R3C1, chTempMat2R3C1, sizeof(chTempMat2R3C1));
			dMat2R3C1 = strtod(chTempMat2R3C1, NULL);
		//Get Matrix 2 Row 3 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R3C2, chTempMat2R3C2, sizeof(chTempMat2R3C2));
			dMat2R3C2 = strtod(chTempMat2R3C2, NULL);
		//Get Matrix 2 Row 3 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R3C3, chTempMat2R3C3, sizeof(chTempMat2R3C3));
			dMat2R3C3 = strtod(chTempMat2R3C3, NULL);
	//////////////////////////////End Matrix 2 Retrieval/////////////////////////////////////
}

/**********************************************************************************************************
			Function call to retrieve the info from the Matrix 1 & 2 Edit Boxes and convert the 
			information from character array to a double data type for use
**********************************************************************************************************/
void GetAndConvert2x2Matrices()
{
	//Temp variables used to retrieve data until converted to double
	char chTempMat1R1C1[80], chTempMat1R1C2[80], 
		 chTempMat1R2C1[80], chTempMat1R2C2[80],
		 chTempMat2R1C1[80], chTempMat2R1C2[80], 
		 chTempMat2R2C1[80], chTempMat2R2C2[80];

	//////////////////////////////Begin Matrix 1 Retrieval/////////////////////////////////////
		//Get Matrix 1 Row 1 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C1, chTempMat1R1C1, sizeof(chTempMat1R1C1));
			dMat1R1C1 = strtod(chTempMat1R1C1, NULL);
		//Get Matrix 1 Row 1 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C2, chTempMat1R1C2, sizeof(chTempMat1R1C2));
			dMat1R1C2 = strtod(chTempMat1R1C2, NULL);

		//Get Matrix 1 Row 2 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C1, chTempMat1R2C1, sizeof(chTempMat1R2C1));
			dMat1R2C1 = strtod(chTempMat1R2C1, NULL);
		//Get Matrix 1 Row 2 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C2, chTempMat1R2C2, sizeof(chTempMat1R2C2));
			dMat1R2C2 = strtod(chTempMat1R2C2, NULL);

	//////////////////////////////End Matrix 1 Retrieval/////////////////////////////////////

	//////////////////////////////Begin Matrix 2 Retrieval/////////////////////////////////////
		//Get Matrix 2 Row 1 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C1, chTempMat2R1C1, sizeof(chTempMat2R1C1));
			dMat2R1C1 = strtod(chTempMat2R1C1, NULL);
		//Get Matrix 2 Row 1 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C2, chTempMat2R1C2, sizeof(chTempMat2R1C2));
			dMat2R1C2 = strtod(chTempMat2R1C2, NULL);

		//Get Matrix 2 Row 2 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C1, chTempMat2R2C1, sizeof(chTempMat2R2C1));
			dMat2R2C1 = strtod(chTempMat2R2C1, NULL);
		//Get Matrix 2 Row 2 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C2, chTempMat2R2C2, sizeof(chTempMat2R2C2));
			dMat2R2C2 = strtod(chTempMat2R2C2, NULL);

	//////////////////////////////End Matrix 2 Retrieval/////////////////////////////////////
}

/**********************************************************************************************************
			Function call to retrieve the info from the Matrix 1 & 2 Edit Boxes and convert the 
			information from character array to a double data type for use
**********************************************************************************************************/
void GetAndConvert4x4Matrices()
{
	//Temp variables used to retrieve data until converted to double
	char chTempMat1R1C1[80], chTempMat1R1C2[80], chTempMat1R1C3[80], chTempMat1R1C4[80],
		 chTempMat1R2C1[80], chTempMat1R2C2[80], chTempMat1R2C3[80], chTempMat1R2C4[80],
		 chTempMat1R3C1[80], chTempMat1R3C2[80], chTempMat1R3C3[80], chTempMat1R3C4[80],
		 chTempMat1R4C1[80], chTempMat1R4C2[80], chTempMat1R4C3[80], chTempMat1R4C4[80],
		 chTempMat2R1C1[80], chTempMat2R1C2[80], chTempMat2R1C3[80], chTempMat2R1C4[80], 
		 chTempMat2R2C1[80], chTempMat2R2C2[80], chTempMat2R2C3[80], chTempMat2R2C4[80],
		 chTempMat2R3C1[80], chTempMat2R3C2[80], chTempMat2R3C3[80], chTempMat2R3C4[80],
		 chTempMat2R4C1[80], chTempMat2R4C2[80], chTempMat2R4C3[80], chTempMat2R4C4[80];

	//////////////////////////////Begin Matrix 1 Retrieval/////////////////////////////////////
		//Get Matrix 1 Row 1 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C1, chTempMat1R1C1, sizeof(chTempMat1R1C1));
			dMat1R1C1 = strtod(chTempMat1R1C1, NULL);
		//Get Matrix 1 Row 1 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C2, chTempMat1R1C2, sizeof(chTempMat1R1C2));
			dMat1R1C2 = strtod(chTempMat1R1C2, NULL);
		//Get Matrix 1 Row 1 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C3, chTempMat1R1C3, sizeof(chTempMat1R1C3));
			dMat1R1C3 = strtod(chTempMat1R1C3, NULL);
		//Get Matrix 1 Row 1 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R1C4, chTempMat1R1C4, sizeof(chTempMat1R1C4));
			dMat1R1C4 = strtod(chTempMat1R1C4, NULL);

		//Get Matrix 1 Row 2 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C1, chTempMat1R2C1, sizeof(chTempMat1R2C1));
			dMat1R2C1 = strtod(chTempMat1R2C1, NULL);
		//Get Matrix 1 Row 2 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C2, chTempMat1R2C2, sizeof(chTempMat1R2C2));
			dMat1R2C2 = strtod(chTempMat1R2C2, NULL);
		//Get Matrix 1 Row 2 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C3, chTempMat1R2C3, sizeof(chTempMat1R2C3));
			dMat1R2C3 = strtod(chTempMat1R2C3, NULL);
		//Get Matrix 1 Row 2 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R2C4, chTempMat1R2C4, sizeof(chTempMat1R2C4));
			dMat1R2C4 = strtod(chTempMat1R2C4, NULL);

		//Get Matrix 1 Row 3 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R3C1, chTempMat1R3C1, sizeof(chTempMat1R3C1));
			dMat1R3C1 = strtod(chTempMat1R3C1, NULL);
		//Get Matrix 1 Row 3 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R3C2, chTempMat1R3C2, sizeof(chTempMat1R3C2));
			dMat1R3C2 = strtod(chTempMat1R3C2, NULL);
		//Get Matrix 1 Row 3 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R3C3, chTempMat1R3C3, sizeof(chTempMat1R3C3));
			dMat1R3C3 = strtod(chTempMat1R3C3, NULL);
		//Get Matrix 1 Row 3 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R3C4, chTempMat1R3C4, sizeof(chTempMat1R3C4));
			dMat1R3C4 = strtod(chTempMat1R3C4, NULL);

		//Get Matrix 1 Row 4 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R4C1, chTempMat1R4C1, sizeof(chTempMat1R4C1));
			dMat1R4C1 = strtod(chTempMat1R4C1, NULL);
		//Get Matrix 1 Row 4 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R4C2, chTempMat1R4C2, sizeof(chTempMat1R4C2));
			dMat1R4C2 = strtod(chTempMat1R4C2, NULL);
		//Get Matrix 1 Row 4 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R4C3, chTempMat1R4C3, sizeof(chTempMat1R4C3));
			dMat1R4C3 = strtod(chTempMat1R4C3, NULL);
		//Get Matrix 1 Row 4 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat1R4C4, chTempMat1R4C4, sizeof(chTempMat1R4C4));
			dMat1R4C4 = strtod(chTempMat1R4C4, NULL);
	//////////////////////////////End Matrix 1 Retrieval/////////////////////////////////////

	//////////////////////////////Begin Matrix 2 Retrieval/////////////////////////////////////
		//Get Matrix 2 Row 1 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C1, chTempMat2R1C1, sizeof(chTempMat2R1C1));
			dMat2R1C1 = strtod(chTempMat2R1C1, NULL);
		//Get Matrix 2 Row 1 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C2, chTempMat2R1C2, sizeof(chTempMat2R1C2));
			dMat2R1C2 = strtod(chTempMat2R1C2, NULL);
		//Get Matrix 2 Row 1 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C3, chTempMat2R1C3, sizeof(chTempMat2R1C3));
			dMat2R1C3 = strtod(chTempMat2R1C3, NULL);
		//Get Matrix 2 Row 1 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R1C4, chTempMat2R1C4, sizeof(chTempMat2R1C4));
			dMat2R1C4 = strtod(chTempMat2R1C4, NULL);

		//Get Matrix 2 Row 2 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C1, chTempMat2R2C1, sizeof(chTempMat2R2C1));
			dMat2R2C1 = strtod(chTempMat2R2C1, NULL);
		//Get Matrix 2 Row 2 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C2, chTempMat2R2C2, sizeof(chTempMat2R2C2));
			dMat2R2C2 = strtod(chTempMat2R2C2, NULL);
		//Get Matrix 2 Row 2 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C3, chTempMat2R2C3, sizeof(chTempMat2R2C3));
			dMat2R2C3 = strtod(chTempMat2R2C3, NULL);
		//Get Matrix 2 Row 2 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R2C4, chTempMat2R2C4, sizeof(chTempMat2R2C4));
			dMat2R2C4 = strtod(chTempMat2R2C4, NULL);

		//Get Matrix 2 Row 3 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R3C1, chTempMat2R3C1, sizeof(chTempMat2R3C1));
			dMat2R3C1 = strtod(chTempMat2R3C1, NULL);
		//Get Matrix 2 Row 3 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R3C2, chTempMat2R3C2, sizeof(chTempMat2R3C2));
			dMat2R3C2 = strtod(chTempMat2R3C2, NULL);
		//Get Matrix 2 Row 3 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R3C3, chTempMat2R3C3, sizeof(chTempMat2R3C3));
			dMat2R3C3 = strtod(chTempMat2R3C3, NULL);
		//Get Matrix 2 Row 3 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R3C4, chTempMat2R3C4, sizeof(chTempMat2R3C4));
			dMat2R3C4 = strtod(chTempMat2R3C4, NULL);

		//Get Matrix 2 Row 4 Column 1 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R4C1, chTempMat2R4C1, sizeof(chTempMat2R4C1));
			dMat2R4C1 = strtod(chTempMat2R4C1, NULL);
		//Get Matrix 2 Row 4 Column 2 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R4C2, chTempMat2R4C2, sizeof(chTempMat2R4C2));
			dMat2R4C2 = strtod(chTempMat2R4C2, NULL);
		//Get Matrix 2 Row 4 Column 3 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R4C3, chTempMat2R4C3, sizeof(chTempMat2R4C3));
			dMat2R4C3 = strtod(chTempMat2R4C3, NULL);
		//Get Matrix 2 Row 4 Column 4 input, convert to double
			GetDlgItemText(g_hwnd, BOX_Mat2R4C4, chTempMat2R4C4, sizeof(chTempMat2R4C4));
			dMat2R4C4 = strtod(chTempMat2R4C4, NULL);
	//////////////////////////////End Matrix 2 Retrieval/////////////////////////////////////
}


/**********************************************************************************************************
			Function call to display the results of the calculations for
			the Matrix math
**********************************************************************************************************/
void Display3x3Result()
{
	char chResultRow1[80], chResultRow2[80], chResultRow3[80];

	sprintf_s(chResultRow1, "[ %f, %f, %f ]", dResult[0][0], dResult[0][1], dResult[0][2]);
	sprintf_s(chResultRow2, "[ %f, %f, %f ]", dResult[1][0], dResult[1][1], dResult[1][2]);
	sprintf_s(chResultRow3, "[ %f, %f, %f ]", dResult[2][0], dResult[2][1], dResult[2][2]);
	
	basewin::vShowText(g_hListBoxResult, chResultRow1);
	basewin::vShowText(g_hListBoxResult, chResultRow2);
	basewin::vShowText(g_hListBoxResult, chResultRow3);
	basewin::vShowText(g_hListBoxResult, "");
}

/**********************************************************************************************************
			Function call to display the results of the calculations for
			the Matrix math
**********************************************************************************************************/
void Display2x2Result()
{
	char chResultRow1[80], chResultRow2[80];

	sprintf_s(chResultRow1, "[ %f, %f ]", dResult[0][0], dResult[0][1]);
	sprintf_s(chResultRow2, "[ %f, %f ]", dResult[1][0], dResult[1][1]);
	
	basewin::vShowText(g_hListBoxResult, chResultRow1);
	basewin::vShowText(g_hListBoxResult, chResultRow2);
	basewin::vShowText(g_hListBoxResult, "");
}

/**********************************************************************************************************
			Function call to display the results of the calculations for
			the Matrix math
**********************************************************************************************************/
void Display4x4Result()
{
	char chResultRow1[80], chResultRow2[80], chResultRow3[80], chResultRow4[80];

	sprintf_s(chResultRow1, "[ %f, %f, %f, %f ]", dResult[0][0], dResult[0][1], dResult[0][2], dResult[0][3]);
	sprintf_s(chResultRow2, "[ %f, %f, %f, %f ]", dResult[1][0], dResult[1][1], dResult[1][2], dResult[1][3]);
	sprintf_s(chResultRow3, "[ %f, %f, %f, %f ]", dResult[2][0], dResult[2][1], dResult[2][2], dResult[2][3]);
	sprintf_s(chResultRow4, "[ %f, %f, %f, %f ]", dResult[3][0], dResult[3][1], dResult[3][2], dResult[3][3]);
	
	basewin::vShowText(g_hListBoxResult, chResultRow1);
	basewin::vShowText(g_hListBoxResult, chResultRow2);
	basewin::vShowText(g_hListBoxResult, chResultRow3);
	basewin::vShowText(g_hListBoxResult, chResultRow4);
	basewin::vShowText(g_hListBoxResult, "");
}
