#ifndef _base_H_
#define _base_H_

//#include <d3dx9.h>

namespace d3d
{
	bool InitD3D(HINSTANCE hinstance, int width,
		int height, bool windowed, D3DDEVTYPE deviceType,
		IDirect3DDevice9** device);

	int EnterMsgLoop(bool(*ptr_display)());

	LRESULT CALLBACK WndProc(
		HWND hwnd, UINT msg,
		WPARAM wparam,
		LPARAM lparam);

	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}

	const D3DXCOLOR CK(D3DCOLOR_XRGB(99, 120, 35));

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 CK_MTRL = InitMtrl(CK, CK, CK, CK, 5.0f);
}
#endif
