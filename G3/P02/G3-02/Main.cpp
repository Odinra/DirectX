#include "LoadXFile.h"
#include "SaveXFile.h"
#include "base.h"
#include <stdio.h>
#include <string>
using namespace std;

/************************************************************************************************
	constant variables for window size and position
************************************************************************************************/
const int iWidth = 1100;
const int iHeight = 650;
const int iXPos = 90;
const int iYPos = 50;

int main()
{
	saveXFile("CLK", 150, "03/19/13", 1);
	saveXFile("ABC", 99, "03/19/13", 2);
	saveXFile("DEF", 98, "03/19/13", 3);
	saveXFile("GHI", 97, "03/19/13", 4);
	saveXFile("JKL", 96, "03/19/13", 5);
	saveXFile("MNO", 95, "03/19/13", 6);
	saveXFile("PQR", 94, "03/19/13", 7);
	saveXFile("STU", 93, "03/19/13", 8);
	saveXFile("VWX", 92, "03/19/13", 9);
	saveXFile("YNZ", 91, "03/19/13", 10);
	LoadXFile();
	for(int i = 0; i < 10; i++)
	{
		printf("%s\t",GetInitial(i));
		printf("%i\t",GetScore(i));
		printf("%s\n",GetDate(i));
	}

  printf("\n\n\t\tIf you see this message you are using the wrong Main.\n\t\tComment out the Main() in main.cpp and Uncomment The WinMain.\n\n");
	system("pause");
	return 0;
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//{
//	if(!basewin::BuildWindow(hInstance, iXPos, iYPos, iHeight, iWidth))
//	{
//		::MessageBox(g_hwnd, "Build Window failed", "ERROR WinMain", MB_OK);
//		return false;
//	}
//	
//	basewin::EnterMainLoop();
//
//	return (0);
//}