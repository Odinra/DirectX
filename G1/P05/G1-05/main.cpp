#include "base.h"

IDirect3DDevice9* Device = 0;

const int win_x = 800;
const int win_y = 600;

DWORD starttime = 0;

bool Setup()
{

	return true;
}

void Cleanup()
{

}

bool Display()
{
	Device->Present(0,0,0,0);
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);
	case WM_RBUTTONDOWN:
			::DestroyWindow(hwnd);
		break;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, PSTR cmdLine, int showCmd)
{

	if(!d3d::InitD3D(hinstance, win_x, win_y, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
	}

	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
	}

	d3d::EnterMsgLoop(Display);
	Cleanup();
	Device->Release();
	return 0;
}