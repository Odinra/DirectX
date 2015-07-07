#ifndef __base_H_
	#define __base_H_
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <windowsx.h>
	#include <stdlib.h>
	#include <string>
	#include <stdio.h>
	#include "LoadXFile.h"
	#include "SaveXFile.h"
	using namespace std;
	
	//Constants to be used for key or button presses, calculations, or to represent GUI items
	#define PI					3.14159265
	#define DEGTORAD			0.0174532925
	#define RADTODEG			57.2957795
	#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
	#define BOX_ListBoxLoadXFiles	1100

	#define BOX_Save1Init			1201
	#define BOX_Save2Init			1202
	#define BOX_Save3Init			1203
	#define BOX_Save4Init			1204
	#define BOX_Save5Init			1205
	#define BOX_Save6Init			1206
	#define BOX_Save7Init			1207
	#define BOX_Save8Init			1208
	#define BOX_Save9Init			1209
	#define BOX_Save10Init			1210

	#define BOX_Save1Date			1501
	#define BOX_Save2Date			1502
	#define BOX_Save3Date			1503
	#define BOX_Save4Date			1504
	#define BOX_Save5Date			1505
	#define BOX_Save6Date			1506
	#define BOX_Save7Date			1507
	#define BOX_Save8Date			1508
	#define BOX_Save9Date			1509
	#define BOX_Save10Date			1510

	#define BOX_Save1Score			1601
	#define BOX_Save2Score			1602
	#define BOX_Save3Score			1603
	#define BOX_Save4Score			1604
	#define BOX_Save5Score			1605
	#define BOX_Save6Score			1606
	#define BOX_Save7Score			1607
	#define BOX_Save8Score			1608
	#define BOX_Save9Score			1609
	#define BOX_Save10Score			1610

	#define BUT_Save1				1301
	#define BUT_Save2				1302
	#define BUT_Save3				1303
	#define BUT_Save4				1304
	#define BUT_Save5				1305
	#define BUT_Save6				1306
	#define BUT_Save7				1307
	#define BUT_Save8				1308
	#define BUT_Save9				1309
	#define BUT_Save10				1310

	#define BUT_LoadXFiles			1400


	extern high_score_return scoreDataReturn[11];



	/*********************************************************************************************
		GLOBALS NEEDED FOR WINSOCK, WINDOWS / BOXES
	*********************************************************************************************/
	extern HWND g_hwnd, g_hListBoxLoadXFiles, 
		g_hEditBoxSave1Init, g_hEditBoxSave2Init, g_hEditBoxSave3Init, g_hEditBoxSave4Init, g_hEditBoxSave5Init,
		g_hEditBoxSave6Init, g_hEditBoxSave7Init, g_hEditBoxSave8Init, g_hEditBoxSave9Init, g_hEditBoxSave10Init,

		g_hEditBoxSave1Date, g_hEditBoxSave2Date, g_hEditBoxSave3Date, g_hEditBoxSave4Date, g_hEditBoxSave5Date,
		g_hEditBoxSave6Date, g_hEditBoxSave7Date, g_hEditBoxSave8Date, g_hEditBoxSave9Date, g_hEditBoxSave10Date,

		g_hEditBoxSave1Score, g_hEditBoxSave2Score, g_hEditBoxSave3Score, g_hEditBoxSave4Score, g_hEditBoxSave5Score,
		g_hEditBoxSave6Score, g_hEditBoxSave7Score, g_hEditBoxSave8Score, g_hEditBoxSave9Score, g_hEditBoxSave10Score;


	
	//Variables created in main, but needed in base
	extern double g_dEditBoxSave1Score, g_dEditBoxSave2Score, g_dEditBoxSave3Score, g_dEditBoxSave4Score, g_dEditBoxSave5Score,
		g_dEditBoxSave6Score, g_dEditBoxSave7Score, g_dEditBoxSave8Score, g_dEditBoxSave9Score, g_dEditBoxSave10Score;

	extern char g_cEditBoxSave1Init, g_cEditBoxSave2Init, g_cEditBoxSave3Init, g_cEditBoxSave4Init, g_cEditBoxSave5Init,
		g_cEditBoxSave6Init, g_cEditBoxSave7Init, g_cEditBoxSave8Init, g_cEditBoxSave9Date, g_cEditBoxSave10Init,

		g_cEditBoxSave1Date, g_cEditBoxSave2Date, g_cEditBoxSave3Date, g_cEditBoxSave4Date, g_cEditBoxSave5Date,
		g_cEditBoxSave6Date, g_cEditBoxSave7Date, g_cEditBoxSave8Date, g_cEditBoxSave9Init, g_cEditBoxSave10Date;

	 

	//Namespace containing the main functions of the program (creates and displays the window, event handler, text display)
	namespace basewin
	{
		bool BuildWindow(HINSTANCE hInstance, int iXPos, int iYPos, int iHeight, int iWidth);
		int EnterMainLoop();
		LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		void vShowText(HWND hChildHandle, char *chText);
	}
#endif
