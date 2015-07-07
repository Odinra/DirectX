#ifndef __base_H_
	#define __base_H_
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <windowsx.h>
	#include <stdlib.h>
	#include <string>
	#include <stdio.h>
	using namespace std;
	
	//Constants to be used for key or button presses, calculations, or to represent GUI items
	#define PI					3.14159265
	#define DEGTORAD			0.0174532925
	#define RADTODEG			57.2957795
	#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
	#define BOX_ListBoxResult	1100

	#define BOX_EditBoxHexDec		1201
	#define BOX_EditBoxDegRad		1202
	#define BOX_EditBoxSide1		1203
	#define BOX_EditBoxSide2		1204
	#define BOX_EditBoxHypotenuse	1206

	#define BOX_Mat1R1C1			1300
	#define BOX_Mat1R1C2			1301
	#define BOX_Mat1R1C3			1302
	#define BOX_Mat1R1C4			1303

	#define BOX_Mat1R2C1			1304
	#define BOX_Mat1R2C2			1305
	#define BOX_Mat1R2C3			1306
	#define BOX_Mat1R2C4			1307

	#define BOX_Mat1R3C1			1308
	#define BOX_Mat1R3C2			1309
	#define BOX_Mat1R3C3			1310
	#define BOX_Mat1R3C4			1311

	#define BOX_Mat1R4C1			1312
	#define BOX_Mat1R4C2			1313
	#define BOX_Mat1R4C3			1314
	#define BOX_Mat1R4C4			1315

	#define BOX_Mat2R1C1			1320
	#define BOX_Mat2R1C2			1321
	#define BOX_Mat2R1C3			1322
	#define BOX_Mat2R1C4			1323
	
	#define BOX_Mat2R2C1			1324
	#define BOX_Mat2R2C2			1325
	#define BOX_Mat2R2C3			1326
	#define BOX_Mat2R2C4			1327
	
	#define BOX_Mat2R3C1			1328
	#define BOX_Mat2R3C2			1329
	#define BOX_Mat2R3C3			1330
	#define BOX_Mat2R3C4			1331

	#define BOX_Mat2R4C1			1332
	#define BOX_Mat2R4C2			1333
	#define BOX_Mat2R4C3			1334
	#define BOX_Mat2R4C4			1335
	
	#define BUT_DecToHex			1702
	#define BUT_HexToDec			1703

	#define BUT_RadToDeg			1704
	#define BUT_DegToRad			1705

	#define BUT_CalcTri				1706

	#define BUT_2x2Add				1720
	#define BUT_2x2Mul				1722
	#define BUT_2x2Sub				1723
		
	#define BUT_3x3Add				1730
	#define BUT_3x3Mul				1732
	#define BUT_3x3Sub				1733
		
	#define BUT_4x4Add				1740
	#define BUT_4x4Mul				1742
	#define BUT_4x4Sub				1743


	/*********************************************************************************************
		GLOBALS NEEDED FOR WINSOCK, WINDOWS / BOXES
	*********************************************************************************************/
	extern HWND g_hwnd, g_hListBoxMessage, 
		g_hEditBoxMat1R1C1, g_hEditBoxMat1R1C2, g_hEditBoxMat1R1C3, g_hEditBoxMat1R1C4, 
		g_hEditBoxMat1R2C1, g_hEditBoxMat1R2C2, g_hEditBoxMat1R2C3, g_hEditBoxMat1R2C4,
		g_hEditBoxMat1R3C1, g_hEditBoxMat1R3C2, g_hEditBoxMat1R3C3, g_hEditBoxMat1R3C4,
		g_hEditBoxMat1R4C1, g_hEditBoxMat1R4C2, g_hEditBoxMat1R4C3, g_hEditBoxMat1R4C4,
		g_hEditBoxMat2R1C1, g_hEditBoxMat2R1C2, g_hEditBoxMat2R1C3, g_hEditBoxMat2R1C4,
		g_hEditBoxMat2R2C1, g_hEditBoxMat2R2C2, g_hEditBoxMat2R2C3, g_hEditBoxMat2R2C4,
		g_hEditBoxMat2R3C1, g_hEditBoxMat2R3C2, g_hEditBoxMat2R3C3, g_hEditBoxMat2R3C4,
		g_hEditBoxMat2R4C1, g_hEditBoxMat2R4C2, g_hEditBoxMat2R4C3, g_hEditBoxMat2R4C4;

	
	//Variables created in main, but needed in base
	extern double dDegToRadResult, dRadToDegResult, dDegRad, dSideA, dSideB, dSideC,
		dMat1R1C1, dMat1R1C2, dMat1R1C3, dMat1R1C4,
		dMat1R2C1, dMat1R2C2, dMat1R2C3, dMat1R2C4,
		dMat1R3C1, dMat1R3C2, dMat1R3C3, dMat1R3C4,
		dMat1R4C1, dMat1R4C2, dMat1R4C3, dMat1R4C4,

		dMat2R1C1, dMat2R1C2, dMat2R1C3, dMat2R1C4,
		dMat2R2C1, dMat2R2C2, dMat2R2C3, dMat2R2C4,
		dMat2R3C1, dMat2R3C2, dMat2R3C3, dMat2R3C4,
		dMat2R4C1, dMat2R4C2, dMat2R4C3, dMat2R4C4,
				dResult[4][4];

	//Functions called in on .cpp but created in another
	
	extern double fpuAdd(const double dAddNumOne, const double dAddNumTwo);
	extern double fpuSub(const double dSubNumOne, const double dSubNumTwo);
	extern double fpuDiv(const double dDivNumOne, const double dDivNumTwo);
	extern double fpuMul(const double dMulNumOne, const double dMulNumTwo);
	extern double fpuModulus(const double dDivide, const double dDivideBy);
	extern double fpuSqRoot(const double dNum);

	extern void matrix2x2Add(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2);
	
	extern void matrix2x2Mul(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2);
	
	extern void matrix2x2Sub(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2);
	
	
	extern void matrix3x3Add(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3);
	
	extern void matrix3x3Mul(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3);
	
	extern void matrix3x3Sub(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3);

		
	extern void matrix4x4Add(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, const double dMat1R1C4,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, const double dMat1R2C4,
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, const double dMat1R3C4,
					  const double dMat1R4C1, const double dMat1R4C2, const double dMat1R4C3, const double dMat1R4C4,
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, const double dMat2R1C4,
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3, const double dMat2R2C4,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3, const double dMat2R3C4,
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4);
	
	extern void matrix4x4Mul(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, const double dMat1R1C4,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, const double dMat1R2C4,
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, const double dMat1R3C4,
					  const double dMat1R4C1, const double dMat1R4C2, const double dMat1R4C3, const double dMat1R4C4,
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, const double dMat2R1C4,
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3, const double dMat2R2C4,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3, const double dMat2R3C4,
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4);
	
	extern void matrix4x4Sub(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, const double dMat1R1C4,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, const double dMat1R2C4,
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, const double dMat1R3C4,
					  const double dMat1R4C1, const double dMat1R4C2, const double dMat1R4C3, const double dMat1R4C4,
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, const double dMat2R1C4,
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3, const double dMat2R2C4,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3, const double dMat2R3C4,
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4);

	

	//Namespace containing the main functions of the program (creates and displays the window, event handler, text display)
	namespace basewin
	{
		bool BuildWindow(HINSTANCE hInstance, int iXPos, int iYPos, int iHeight, int iWidth);
		int EnterMainLoop();
		LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		void vShowText(HWND hChildHandle, char *chText);
	}
#endif
