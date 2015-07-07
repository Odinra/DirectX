#ifndef _BASE_H
#define _BASE_H

#include <d3dx9.h>

namespace d3d
{
	bool InitD3D(HINSTANCE hInstance, int width, int height, bool windowed, D3DDEVTYPE deviceType, IDirect3DDevice9** device);

	int EnterMsgLoop(bool(*ptr_display)());

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void Game_Main(void *parms);
}


#endif