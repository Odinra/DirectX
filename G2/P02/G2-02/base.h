
#ifndef __base_H__
#define __base_H__

#include <d3dx9.h>
#include <string>
#include "camera.h"

namespace d3d
{
	bool InitD3D(HINSTANCE hInstance, int width, int height, bool windowed, D3DDEVTYPE deviceType, IDirect3DDevice9** device);

	int EnterMsgLoop(bool (*ptr_display)());

	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam,
		LPARAM lParam);

	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}
		
	template<class T> void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}

	//
	//COLORS
	//
	
	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );//
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );//
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );//
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );//
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );//
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );//
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );//
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );//
	const D3DXCOLOR			ME( D3DCOLOR_XRGB(150, 0,   100) );//
	const D3DXCOLOR		   WOOD(D3DCOLOR_XRGB(166, 128, 100) );//
	const D3DXCOLOR	 LIGHTBULB( D3DCOLOR_XRGB(238, 220, 130) );//
	const D3DXCOLOR BASKETBALL( D3DCOLOR_XRGB(205,  87,   0) );//
	const D3DXCOLOR	 WALLPAPER( D3DCOLOR_XRGB(154, 205,  50) );//
	const D3DXCOLOR	      PERU( D3DCOLOR_XRGB(139, 69,  19) );//


	////
	//// Materials
	////

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);//
	const D3DMATERIAL9 RED_MTRL    = InitMtrl(RED, RED, RED, BLACK, 2.0f);//
	const D3DMATERIAL9 GREEN_MTRL  = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);//
	const D3DMATERIAL9 BLUE_MTRL   = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);//
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);//
	const D3DMATERIAL9 ME_MTRL = InitMtrl(ME,ME,ME, BLACK, 5.0f);
	const D3DMATERIAL9 BLACK_MTRL = InitMtrl(BLACK, BLACK, BLACK, BLACK, 5.0f);//
	const D3DMATERIAL9 CYAN_MTRL = InitMtrl(CYAN, CYAN, CYAN, BLACK, 2.0f);//
	const D3DMATERIAL9 MAGENTA_MTRL = InitMtrl(MAGENTA, MAGENTA, MAGENTA, BLACK, 2.0f);//
	const D3DMATERIAL9 WOOD_MTRL = InitMtrl(WOOD, WOOD, WOOD, BLACK, 2.0f);//
	const D3DMATERIAL9 LIGHTBULB_MTRL = InitMtrl(LIGHTBULB, LIGHTBULB, LIGHTBULB, BLACK, 2.0f);//
	const D3DMATERIAL9 BASKETBALL_MTRL = InitMtrl(BASKETBALL, BASKETBALL, BASKETBALL, BLACK, 1.0f);//
	const D3DMATERIAL9 WALLPAPER_MTRL = InitMtrl(WALLPAPER, WALLPAPER, WALLPAPER, BLACK, 2.0f);//
	const D3DMATERIAL9 PERU_MTRL = InitMtrl(PERU, PERU, PERU, BLACK, 2.0f);//

	D3DLIGHT9 InitPointLight(D3DXCOLOR* color, D3DXVECTOR3* position);
}

#endif // __base_H__